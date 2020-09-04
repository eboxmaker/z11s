/*
 * json_test.cpp
 *
 *  Created on: 2018年12月4日
 *      Author: Administrator
 */

#include "utils/log.h"
#include "json_manager.h"
#include "lib/itoa.h"
#include   <iostream>
#include "lib/base64.h"
#include "global.h"
#include "lib/fileOpt.h"

#include "security/SecurityManager.h"

#include "md5/md5.h"
#include "version.h"


static string key =  "12345678900000001234567890000000";
static string iv =  "1234567890000000";

static char buf[409600];
static int counter = 0;


bool ParseJsonString(char *str)
{
	  Json::Reader reader;

	  Json::Value root;
	  if (reader.parse(str, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  return true;
	  }
	  else
		  return false;
}
JsonCmd_t getJsonCMD(string &str)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonCmd_t cmd;

	  if (reader.parse(str, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {

		  cmd = (JsonCmd_t)root["cmd"].asInt();
	  }

	  return cmd;
}



JsonCmdManager::JsonCmdManager(){
	aes = new AesEncryptor(key,iv);

}
JsonCmdManager::~JsonCmdManager()
{

}


string JsonCmdManager::pack(string& data)
{
	string str;

	MD5 md5(data);

	str = aes->encrypt(data);
//	LOGE("data:%s",data.c_str());

	Json::Value root;
	root["sign"] = Json::Value(md5.toStr());
	root["data"] = Json::Value(str);
	Json::FastWriter fw;
	string temp =  fw.write(root);
//	LOGE("pack:%s",temp.c_str());
	return temp;

}

//string JsonCmdManager::pack(char* data)
//{
//	string str;
//	string data_ = data;
//	MD5 md5(data);
//
//	str = aes->encrypt(data_);
//
//
//	Json::Value root;
//	root["sign"] = Json::Value(md5.toStr());
//	root["data"] = Json::Value(str);
//	Json::FastWriter fw;
//	string temp =  fw.write(root);
//	LOGE("%s",temp.c_str());
//	return temp;
//
//}
char md5_buffer[1024*1024];

void printAll(string &str)
{
  memset(md5_buffer,0,1024*1024);
  memcpy(md5_buffer,str.c_str(),str.size());
  int len = str.size();
  int counter = 0;
  int rb = 0;
  int remain = 0;
  LOGD("完整字符串");
  while(1){
	  remain = len - counter;
	  if(remain >= 512)
		  rb = 512;
	  else
		  rb = remain;

	  char buf[1024] = {0};
	  memset(buf,0,1024);
	  memcpy(buf,&md5_buffer[counter],rb);
	  LOGD("%s",buf);
	  counter += rb;
	  if(counter >= len){
		  break;
	  }
  }
  LOGD("字符串长度：%d,%d",counter,str.size());



}
bool JsonCmdManager::unPack(string& package,string& js)
{
	Json::Features features;

	features.strictRoot_ = true;

	Json::Reader reader(features);

	  Json::Value root;
	  string data;
	  string md5str;
	  string temp_js = "";
	  js = "";

	  if (reader.parse(package, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  if(root.isMember("sign"))
			  md5str = root["sign"].asString();
		  else{
			  LOGE("不存在sign");
			  return false;
		  }

		  if(root.isMember("data"))
			  data = root["data"].asString();
		  else{
			  LOGE("不存在data");
			  return false;

		  }
//		  LOGD("json md5：%s",md5str.c_str());
//		  LOGD("json data：%s",data.c_str());
//		  LOGD("原文:%s",package.c_str());

	  }
	  else
	  {
		  LOGE("帧错误");
		  return false;
	  }
	  temp_js = aes->decrypt(data);

	  uint16_t index = temp_js.find_last_of('}', 0);
	  js = temp_js.substr(0,index);
//	  printAll(js);

	  MD5 md5(js);
	  string checkMD5 = md5.toStr();


	  if(checkMD5 == md5str)
	  {
//		  LOGD("解密：%s",js.c_str());
		  return true;
		  //LOGD("md5正确");
	  }
	  else
	  {
		  LOGE("MD5错误:%s",package.c_str());
		  LOGE("原文md5：%s",md5str.c_str());
		  LOGE("原始长度:%d)",data.length());
		  LOGE("原文数据：%s",data.c_str());

		  LOGE("本地计算MD5:%s",checkMD5.c_str());
		  LOGE("解密后:长度:%d,size:%d)",js.length(),js.size());
		  printAll(js);


		  return false;
	  }
	  return false;
}

bool JsonCmdManager::unPack(char* data,string& msg)
{
	return false;
}
//JsonStatus_t JsonCmdManager::parseStatus(string &js)
//{
//	  Json::Reader reader;
//	  Json::Value root;
//
//	  JsonStatus_t status;
//
//	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
//	  {
//		  return  (JsonStatus_t)root["status"].asInt();
//	  }
//	  return StatusErr;
//}
#include <sys/types.h>
#include <sys/sysinfo.h>

string JsonCmdManager::makeHeartbeat(JsonStatus_t status)
{
	struct sysinfo systemInfo;
	float memUsage;
    char tempbuf[30];
	sysinfo(&systemInfo);
    memUsage = (1 - ((float)systemInfo.freeram/(float)systemInfo.totalram))*100;
    sprintf(tempbuf,"%0.1f%%(%0.1fM/%0.1fM)",memUsage,\
    		(systemInfo.totalram - systemInfo.freeram)/1024.0/1024.0,\
			 systemInfo.totalram/1024.0/1024.0);

	  Json::Value root;
	  root["cmd"] = Json::Value(CMDHeartbeat);
	  root["value"] = Json::Value(tempbuf);
	  root["status"] = Json::Value((int)status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseHeartbeat(string &js, string &msg)
{
	  Json::Reader reader;
	  Json::Value root;
	  JsonStatus_t status = StatusErr;

	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  if(root.isMember("value")){
			  if(root["value"].type() == Json::stringValue)
				  msg = root["value"].asString();
		  }
		  if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
		  }

	  }

	  return status;
}

string JsonCmdManager::makeSetHeartbeat(int interval,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDSetHeartbeat);
	  root["heartbeatInterval"] = Json::Value(interval);
	  root["status"] = Json::Value((int)status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseSetHeartbeat(string &js, int &interval)
{
	  Json::Reader reader;
	  Json::Value root;

	  JsonStatus_t status = StatusErr;

	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  if(root.isMember("heartbeatInterval")){
			  if(root["heartbeatInterval"].type() == Json::intValue)
				  interval = root["heartbeatInterval"].asInt();
		  }
		  if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
		  }
	  }

	  return status;
}


string JsonCmdManager::makeDevID(string &id,JsonStatus_t status)
{

	  Json::Value root;
	  root["cmd"] = Json::Value(CMDDevID);
	  root["id"] = Json::Value(id);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);

}
JsonStatus_t JsonCmdManager::parseDevID(string &js)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status = StatusErr;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
		  }
	  }

	  return status;
}

string JsonCmdManager::makeOrgName(string &org,JsonStatus_t status)
{

	  Json::Value root;
	  root["cmd"] = Json::Value(CMDOrgName);
	  root["organization"] = Json::Value(org);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseOrgName(string &js,string &org)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status = StatusErr;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
		  }
		  if(status == StatusSet)
		  {
			  if(root.isMember("organization")){
				  if(root["organization"].type() == Json::stringValue)
					 org = root["organization"].asString();
			  }

		  }
	  }

	  return status;
}

string JsonCmdManager::makeDevName(string &name,JsonStatus_t status)
{

	  Json::Value root;
	  root["cmd"] = Json::Value(CMDDevName);
	  root["name"] = Json::Value(name);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseDevName(string &js,string &name)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status = StatusErr;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
		  }
		  if(status == StatusSet)
		  {
			  name = root["name"].asString();
		  }
	  }

	  return status;
}


string JsonCmdManager::makeRegister(Device &pDev,JsonStatus_t status)
{

	  Json::Value root;
	  root["cmd"] = Json::Value(CMDRegister);
	  root["id"] = Json::Value(pDev.get_id());
	  root["version"] = Json::Value(pDev.get_version());
//	  if(status == StatusAckDev2Ser)
//	  {
//		  root["organization"] = Json::Value(pDev.get_organization());
//		  root["name"] = Json::Value(pDev.get_name());
//		  root["interval"] = Json::Value(pDev.get_heartbeatInterval());
//	  }
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  LOGD("注册包：%s",temp.c_str());
	  return pack(temp);

}
JsonStatus_t JsonCmdManager::parseRegister(string &js,DevicePara_t &para,string &timeString)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status = StatusErr;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
		  }
		  if(status == StatusOK)
		  {
			  para.organization = root["organization"].asString();
			  para.name = root["name"].asString();
			  para.id = root["id"].asString();
			  timeString = root["dateTime"].asString();
		  }

	  }

	  return status;
}

string JsonCmdManager::makeSyncDateTime(string &msg,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDSyncDateTime);
	  root["dateTime"] = Json::Value(msg);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseSyncDateTime(string &js,string &msg)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status = StatusErr;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
		  }
		  msg = root["dateTime"].asString();
	  }

	  return status;
}


string JsonCmdManager::makeLocalPwd(string &pwd,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDLocalPassword);
	  root["password"] = Json::Value(pwd);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseLocalPwd(string &js,string &pwd)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status = StatusErr;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
		  }
		  if(status == StatusSet)
		  {
			  pwd = root["password"].asString();
		  }
	  }

	  return status;
}


string  JsonCmdManager::makeDoorPwd(string &pwd,JsonStatus_t status)
{

	  Json::Value root;
	  root["cmd"] = Json::Value(CMDDoorPassword);
	  root["password"] = Json::Value(pwd);
	  root["status"] = Json::Value((int)status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t  JsonCmdManager::parseDoorPwd(string &js,string &pwd)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status = StatusErr;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {

		  if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
		  }
		  pwd =  root["password"].asString();
	  }

	  return status;
}

string JsonCmdManager::makeFingerKey(PersonInfo_t &key,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDFingerKey);
	  root["id"] = Json::Value(key.id);

	  root["name"] = Json::Value(key.name);
	  if(key.level < -1 || key.level > 10)
		  key.level = -1;
	  root["level"] = Json::Value(key.level);

	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);

	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseFingerKey(string &js)
{
	  Json::Reader reader;
	  Json::Value root;

	  JsonStatus_t status = StatusErr;
	  string str;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
		  }
	  }

	  return status;
}

string JsonCmdManager::makeDoorCtr(DoorLockState_t &door,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDDoorLockControl);

		switch(door)
		{
		case Lock: root["doorControl"] = Json::Value("lock");break;
		case Unlock: root["doorControl"] = Json::Value("unlock");break;
		}

	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseDoorCtr(string &js,DoorLockState_t &door)
{
	  Json::Reader reader;
	  Json::Value root;

	  JsonStatus_t status = StatusErr;
	  string str;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {

		  if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
		  }
		  str = root["doorControl"].asString();

		  if(str == "unlock")
		  {
			  door = Unlock;
		  }
		  else if(str == "lock")
		  {
			  door = Lock;
		  }
		  else
		  {
			  door = Lock;
		  }
	  }

	  return status;
}
string JsonCmdManager::makeDoorState(DoorState_t &door,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDDoorState);

		switch(door)
		{
		case LockClose: root["doorState"] = Json::Value("lockClose");break;
		case LockOpen: root["doorState"] = Json::Value("lockOpen");break;
		case UnlockClose: root["doorState"] = Json::Value("unlockClose");break;
		case UnlockOpen: root["doorState"] = Json::Value("unlockOpen");break;
		}

	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseDoorState(string &js)
{
	  Json::Reader reader;
	  Json::Value root;

	  JsonStatus_t status = StatusErr;
	  string str;
	  if (reader.parse(js, root)){  // reader将Json字符串解析到root，root将包含Json里所有子元素
		  if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
		  }
	  }

	  return status;
}

string  JsonCmdManager::makeCourseInfo(CourseInfo_t &info,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDCourseInfo);
	  root["name"] = Json::Value(info.name);
	  root["class"] = Json::Value(info.class_);
	  root["num"] = Json::Value(info.num);
	  root["course"] = Json::Value(info.course);
	  root["picture_name"] = Json::Value(info.picture.name);
	  root["picture_dataLength"] = Json::Value((int)info.picture.dataLength);

	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  LOGD("CMD:CMDCourseInfo=%s",temp.c_str());
	  return pack(temp);
}
JsonStatus_t  JsonCmdManager::parseCourseInfo(string &js,CourseInfo_t &info)
{
	JsonStatus_t status = StatusErr;
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		if(root.isMember("status")){
		  if(root["status"].type() == Json::intValue)
			  status = (JsonStatus_t)root["status"].asInt();
		}
		if(status == StatusSet )
		{
			info.name = root["name"].asString();
			info.class_ = root["class"].asString();
			info.num = root["num"].asString();
			info.course = root["course"].asString();


			info.picture.name = root["picture_name"].asString();  // 访问节点，upload_id = "UP000000"
			LOGD("info->picture_name:%s",info.picture.name.c_str());

			info.picture.data = root["picture_data"].asString();    // 访问节点，code = 100
			LOGD("info->picture_data:%s",info.picture.data.c_str());

			info.picture.dataLength = root["picture_dataLength"].asLargestUInt();
			LOGD("info->picture_dataLength:%d",info.picture.dataLength);



			if(info.picture.dataLength != info.picture.data.length())
			{
				LOGE("头像长度不匹配");
				return StatusErr;
			}
			string picBuf;
			picBuf = info.picture.data;
			info.picture.data = "";
			if(Base64::Decode(picBuf,&info.picture.data))
			{

			}
		}

	}

	  return status;
}

string JsonCmdManager::makePlan(JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDPlan);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parsePlan(string &js, Plan &plan)
{
	  JsonStatus_t status = StatusErr;
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		if(root.isMember("status")){
		  if(root["status"].type() == Json::intValue)
			  status = (JsonStatus_t)root["status"].asInt();
		}

		Json::Value course = root["plan"];
		int course_size =  root["plan"].size();
		if(status == StatusOK || status == StatusSet)
		{
			plan.clear();
			LOGE("SIZE course_size = %d",course_size);
			for(int i = 0; i < course_size; i++)
			{
				Plan::PlanRow_t row;

				row.unit	 	= course[i]["unit"].asString();
				row.startTime 	= course[i]["startTime"].asString();
				row.endTime 	= course[i]["endTime"].asString();
				row.teacher 	= course[i]["teacher"].asString();
				row.class_ 		= course[i]["class_"].asString();
				row.course	 	= course[i]["course"].asString();
				gPlan.add(row);
			}
		}

	}

	  return status;
}

string JsonCmdManager::makeBroadcast(string &msg,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDBroadcast);
	  root["data"] = Json::Value(msg);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseBroadcast(string &js,string &msg)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status = StatusErr;

	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
			if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
			}
		  msg = root["data"].asString();
	  }

	  return status;
}


//广告的增删改查
string JsonCmdManager::makeQRCodeAck(string &fullname,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDQRCode);
	  root["name"] = Json::Value(fullname);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
string JsonCmdManager::makeAdAdd(string &fullname,JsonStatus_t status)
{
	  Json::Value root;
	  uint64_t size = get_file_size(fullname.c_str());
	  root["cmd"] = Json::Value(CMDAdAdd);
	  root["name"] = Json::Value(fullname);
	  root["size"] = Json::Value(size);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}

string JsonCmdManager::makeAdRead(Advertisement &ad, JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDAdRead);


	  if(ad.getNum() > 0)
	  {
		  Json::Value adv;
		  Json::Value item;
		  for(int i = 0; i < ad.getNum(); i++)
		  {
			  item["name"] = ad.dbList[i].fileName;
			  item["displayTime"] = ad.dbList[i].displayTime;
			  adv.append(item);
		  }
		  root["adv"] = Json::Value(adv);

	  }
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
string JsonCmdManager::makeAdDelet(string fileName,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDAdDel);
	  root["name"] = Json::Value(fileName);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
string JsonCmdManager::makeAdClear(JsonStatus_t status){
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDAdClear);
	  root["status"] = Json::Value(status);

//	  string temp =  root.asCString();

	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}

JsonStatus_t JsonCmdManager::parseAdAdd(string js,string &fileName){
	  Json::Reader reader;
	  Json::Value root;

	  JsonStatus_t status = StatusErr;

	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
			if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
			}
			return  (JsonStatus_t)root["status"].asInt();
	  }
	  return StatusErr;
}
JsonStatus_t JsonCmdManager::parseAdRead(string js)
{
	  Json::Reader reader;
	  Json::Value root;

	  JsonStatus_t status = StatusErr;

	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
			if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
			}

		  return  status;
	  }
	  return StatusErr;
}

JsonStatus_t JsonCmdManager::parseAdDelet(string js, string &fileName)
{
	Json::Reader reader;
	Json::Value root;
	  JsonStatus_t status = StatusErr;

	if (reader.parse(js, root)){  // reader将Json字符串解析到root，root将包含Json里所有子元素
		if(root.isMember("status")){
		  if(root["status"].type() == Json::intValue)
			  status = (JsonStatus_t)root["status"].asInt();
		}
		if(status == StatusSet)	{
			fileName = root["name"].asString();  // 访问节点，upload_id = "UP000000"
		}
		else{
			fileName = "";
		}
	}
	return status;
}
JsonStatus_t JsonCmdManager::parseAdClear(string &js){
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status = StatusErr;
	  std::string val_str;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
			if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
			}
	  }

	  return status;
}
JsonStatus_t JsonCmdManager::parseFile(string js, char* directory, string &fullName,string &dataout)
{
	Json::Reader reader;
	Json::Value root;
	string fileName;
	string data;
	unsigned long length;
	  JsonStatus_t status = StatusErr;
	if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{

		fileName = root["name"].asString();  // 访问节点，upload_id = "UP000000"
		data = root["data"].asString();    // 访问节点，code = 100
		length = root["dataLength"].asLargestUInt();
		//LOGE("len err:%ul ? %ul",length,data.length());


		if(length != data.length())
		{
			LOGE("接收长度不匹配");
			return StatusErr;
		}
		fullName = directory ;
		fullName +=  fileName;
	}
	Base64::Decode(data, &dataout);
	return StatusSet;
}


string JsonCmdManager::makeDeleteFile(string &fileName,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDAdDel);
	  root["name"] = Json::Value(fileName);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseDeleteFile(string js, char* directory, string &fileName, string &fullName)
{
	Json::Reader reader;
	Json::Value root;
	  JsonStatus_t status = StatusErr;

	if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{

		fileName = root["name"].asString();  // 访问节点，upload_id = "UP000000"
		status = (JsonStatus_t)root["status"].asInt();
		//LOGE("len err:%ul ? %ul",length,data.length());
		fullName = directory ;
		fullName +=  fileName;
		LOGE("%s",fullName.c_str());
	}


	return status;
}


string JsonCmdManager::makeAdSet(Advertisement &set,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDAdSet);
	  root["enable"] = Json::Value(set.get_enable());
	  root["idleTime"] = Json::Value(set.get_idleTime());
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseAdSet(string &js,Advertisement &set)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status = StatusErr;
	  std::string val_str;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
			if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
			}
		  if(status == StatusOK)
		  {
		  }
		  else if(status == StatusSet)
		  {
			  int idleTime = root["idleTime"].asInt();
			  bool state = root["enable"].asBool();
//			  LOGD("广告设置：idletime:%d,state:%d",idleTime,state);
			  set.set_idleTime(idleTime);
			  set.set_enable(state);
		  }
	  }

	  return status;
}


string JsonCmdManager::makePersonAdd(PersonTrans_t &person,JsonStatus_t status)
{
	  PersonInfo_t tempPerson;
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDPersonAdd);
	  root["id"] = Json::Value(person.id);

	  root["name"] = Json::Value(person.name);
	  if(person.level < -1 || person.level > 10)
		  person.level = -1;
	  root["level"] = Json::Value(person.level);
	  gPerson.get_person_by_uid(person.id, &tempPerson);
	  root["fingerNums"] = Json::Value(tempPerson.finger_id.size());


	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);

	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parsePersonAdd(string &js,PersonTrans_t &person)
{
	  JsonStatus_t status = StatusErr;
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		if(root.isMember("status")){
		  if(root["status"].type() == Json::intValue)
			  status = (JsonStatus_t)root["status"].asInt();
		}
		if(status == StatusOK || status == StatusSet)
		{
			person.id = root["id"].asString();
			person.name = root["name"].asString();
			person.level = root["level"].asInt();
			LOGD("FingerGet->id:%s,name:%s",person.id.c_str(),person.name.c_str());
			Json::Value fingers = root["fingers"];
			int fingers_size =  root["fingers"].size();
			person.fingers.clear();
			for(int i = 0; i < fingers_size; i++)
			{
				person.fingers.push_back(fingers[i]["finger"].asString());
				LOGD("finger:%s",person.fingers[i].c_str());
			}


//			person.picture.name = root["picture_name"].asString();  // 访问节点，upload_id = "UP000000"
//			person.picture.data = root["picture_data"].asString();    // 访问节点，code = 100
//			person.picture.dataLength = root["picture_dataLength"].asLargestUInt();
//
//
//			if(person.picture.dataLength != person.picture.data.length())
//			{
//				LOGE("头像长度不匹配");
//				return StatusErr;
//			}
//			string picBuf;
//			picBuf = person.picture.data;
//			person.picture.data = "";
//			if(Base64::Decode(picBuf,&person.picture.data))
//			{
//
//			}
		}

	}
	  return status;
}
string JsonCmdManager::makePersonDel(JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDPersonDel);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parsePersonDel(string &js)
{
	JsonStatus_t status = StatusErr;
	Json::Reader reader;
	Json::Value root;

	if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		if(root.isMember("status")){
		  if(root["status"].type() == Json::intValue)
			  status = (JsonStatus_t)root["status"].asInt();
		}
		if(status == StatusOK || status == StatusSet)
		{
			Json::Value ids = root["ids"];
			int ids_size =  root["ids"].size();
			for(int i = 0; i < ids_size; i++)
			{
				gPerson.delete_uid(ids[i]["id"].asString());
			}

		}

	}

}
string JsonCmdManager::makePersonGetByLevel(int level, int num, JsonStatus_t status)
{
	  PersonInfo_t tempPerson;
	  Json::Value root;
	  if(level < -1 || level > 10)
		  level = -1;
	  root["cmd"] = Json::Value(CMDPersonByLevel);
	  root["level"] = Json::Value(level);
	  root["num"] = Json::Value(num);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parsePersonGetByLevel(string &js, int *level, int *num)
{
	JsonStatus_t status = StatusErr;
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		if(root.isMember("status")){
		  if(root["status"].type() == Json::intValue)
			  status = (JsonStatus_t)root["status"].asInt();
		}
		if(status == StatusOK || status == StatusSet)
		{
			*num = root["num"].asInt();
			*level = root["level"].asInt();
		}
	}
	return status;
}

string JsonCmdManager::makeFingerGet(PersonTrans_t &person,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDFingerGet);
	  root["id"] = Json::Value(person.id);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);

	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseFingerGet(string &js,PersonTrans_t &person)
{
	  JsonStatus_t status = StatusErr;
	Json::Reader reader;
	Json::Value root;
	LOGD("开始解析:FingerGet");
	if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		LOGD("解析成功:FingerGet");
		if(root.isMember("status")){
		  if(root["status"].type() == Json::intValue)
			  status = (JsonStatus_t)root["status"].asInt();
		}
		if(status == StatusOK || status == StatusSet)
		{
			person.id = root["id"].asString();
			person.name = root["name"].asString();
			person.level = root["level"].asInt();
			LOGD("FingerGet->id:%s,name:%s",person.id.c_str(),person.name.c_str());
			int fingers_size =  root["fingers"].size();
			if(fingers_size > 0 )
			{
				Json::Value fingers = root["fingers"];
				string temp ;
				person.fingers.clear();
				for(int i = 0; i < fingers_size; i++)
				{
					temp = fingers[i]["finger"].asString();
					if(temp != ""){
						person.fingers.push_back(fingers[i]["finger"].asString());
						LOGD("finger:%s",person.fingers[i].c_str());
					}
					else{
						LOGD("jm收到空指纹：直接删除");
					}
				}
				LOGD("FingerGet->fingers:OK;%d个指纹",person.fingers.size());
			}else
			{
				LOGD("FingerGet->fingers:没有解析到指纹信息;");

			}


			person.picture.name = root["picture_name"].asString();
			LOGD("FingerGet->picture_name:%s",person.picture.name.c_str());

			person.picture.dataLength = (long)root["picture_dataLength"].asLargestUInt();
			LOGD("FingerGet->picture_dataLength:%d",person.picture.dataLength);

			person.picture.data = root["picture_data"].asString();
			LOGD("FingerGet->picture_data:%s",person.picture.data.c_str());


			if(person.picture.dataLength != person.picture.data.length())
			{
				LOGE("头像长度不匹配");

				return StatusErr;
			}
			string picBuf;
			picBuf = person.picture.data;
			person.picture.data = "";
			if(Base64::Decode(picBuf,&person.picture.data))
			{
			}
			else
			{
				LOGE("错误：base64解码 ");
			}
		}
		else{
			LOGE("异常status :%d",status);

		}

	}
	else{
		LOGE("解析失败");
	}

	  return status;
}

string JsonCmdManager::makeFingerSet(PersonTrans_t &person,JsonStatus_t status)
{
	  Json::Value root;
	  Json::Value fingers;
	  root["cmd"] = Json::Value(CMDFingerSet);
	  root["id"] = Json::Value(person.id);

	  root["name"] = Json::Value(person.name);
	  if(person.level < -1 || person.level > 10)
		  person.level = -1;
	  root["level"] = Json::Value(person.level);

	  if(person.fingers.size() > 0)
	  {
		  Json::Value finger;
		  for(int i = 0; i < person.fingers.size(); i++)
		  {
			  finger["finger"] = person.fingers[i];
			  fingers.append(finger);
		  }
		  root["fingers"] = Json::Value(fingers);
	  }
	  else
	  {
		  root["fingers"] = Json::Value(fingers);
	  }

	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  LOGD("%s",temp.c_str());
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseFingerSet(string &js,int *fingers_size)
{
	JsonStatus_t status = StatusErr;
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		if(root.isMember("status")){
		  if(root["status"].type() == Json::intValue)
			  status = (JsonStatus_t)root["status"].asInt();
		}
		*fingers_size =(long)root["fingersSize"].asInt();
	}

	  return status;
}
string JsonCmdManager::makeVersion(JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDVersion);
	  root["version"] = Json::Value(VERSION);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseVersion(string &js)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status = StatusErr;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
			if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
			}
	  }

	  return status;
}

string JsonCmdManager::makeUpdate(HttpInfo_t &info, JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDUpdate);
	  root["url"] = Json::Value(info.url);
	  root["port"] = Json::Value(info.port);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  LOGD("更新系统：%s",temp.c_str());
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseUpdate(string &js,HttpInfo_t &info)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status = StatusErr;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
			if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
			}
		  if(status == StatusSet || status == StatusOK)
		  {
			  info.url = root["url"].asString();
			  info.port = root["port"].asInt();
		  }
	  }

	  return status;
}

string JsonCmdManager::makeReboot(JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDReboot);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseReboot(string &js)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status = StatusErr;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
			if(root.isMember("status")){
			  if(root["status"].type() == Json::intValue)
				  status = (JsonStatus_t)root["status"].asInt();
			}
	  }

	  return status;
}







string JsonCmdManager::getID()
{
	XdataULong_t id;
	char buf1[32];
	char buf2[32];

	bool ret = SECURITYMANAGER->getDevID(id.bytes);

	ultoa(id.value,buf1,10);
	ultoa(id.value>>32,buf2,10);
	string str = buf2;
	str += buf1;
	return str;
}



/*
//定义文件指针
FILE *openfile(uint32_t *len)
{
	char chFileIn3[100];
	FILE *fp;


	string chFileIn1 = "/mnt/extsd/recv.jpg";
   strcpy(chFileIn3, chFileIn1.c_str());


   fp = fopen(chFileIn3, "rb");

	if (fp == NULL )

	{

		printf("打开读取文件失败");

		  return	NULL;

	}
	fseek(fp,0L,SEEK_END);
	*len=ftell(fp);
	fclose(fp);

	fp = fopen(chFileIn3, "rb");

	printf("打开读取文件成功");
	return fp;
}
*/

JsonCmdManager jm;
