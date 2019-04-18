/*
 * json_test.cpp
 *
 *  Created on: 2018年12月4日
 *      Author: Administrator
 */

#include "json_test.h"
#include "lib/itoa.h"
#include "globalVar.h"
#include   <iostream>
#include "base64.h"

#include "security/SecurityManager.h"

#include "readdir.h"
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
	str = aes->encrypt(data);

	MD5 md5(str);
	Json::Value root;
	root["sign"] = Json::Value(md5.toStr());
	root["data"] = Json::Value(str);
	Json::FastWriter fw;
	string temp =  fw.write(root);
	//LOGE("pack:%s",temp.c_str());
	return temp;

}

string JsonCmdManager::pack(char* data)
{
	string str;
	string data_ = data;

	str = aes->encrypt(data_);


	MD5 md5(str);
	Json::Value root;
	root["sign"] = Json::Value(md5.toStr());
	root["data"] = Json::Value(str);
	Json::FastWriter fw;
	string temp =  fw.write(root);
	LOGE("%s",temp.c_str());
	return temp;

}
bool JsonCmdManager::unPack(string& package,string& msg)
{
	  Json::Reader reader;

	  Json::Value root;
	  string data;
	  string md5str;
	  msg = "";
	  if (reader.parse(package, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  md5str = root["sign"].asString();
		  data = root["data"].asString();
	  }
	  else
	  {
		  LOGE("%s:帧错误",__FILE__);
		  return false;
	  }

	  MD5 md5(data);
	  string checkMD5 = md5.toStr();
	  if(checkMD5 == md5str)
	  {
		  msg = aes->decrypt(data);
		  //LOGE("md5正确");
		  //LOGE("解密：%s",msg.c_str());
	  }
	  else
	  {
		  LOGE("md5错误");
		  return false;
	  }
	  return true;
}

bool JsonCmdManager::unPack(char* data,string& msg)
{

}

string JsonCmdManager::makeHeartbeat(JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDHeartbeat);
	  root["value"] = Json::Value("hello");
	  root["status"] = Json::Value((int)status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseHeartbeat(string &js, string &msg)
{
	  Json::Reader reader;
	  Json::Value root;

	  JsonStatus_t status;

	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {

		  msg = root["value"].asString();
		  status = (JsonStatus_t)root["status"].asInt();
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

	  JsonStatus_t status;

	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {

		  interval = root["heartbeatInterval"].asInt();
		  status = (JsonStatus_t)root["status"].asInt();
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
	  JsonStatus_t status;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  status = root["status"].asInt();
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
	  JsonStatus_t status;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  status = root["status"].asInt();
		  if(status == StatusSet)
		  {
			  org = root["organization"].asString();
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
	  JsonStatus_t status;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  status = root["status"].asInt();
		  if(status == StatusSet)
		  {
			  name = root["name"].asString();
		  }
	  }

	  return status;
}


string JsonCmdManager::makeConfirm(Device_t &dev_,JsonConfirmStatus_t status)
{

	//UTF8String u8 = L"UNICODE字符串";
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDConfirm);
	  root["id"] = Json::Value(dev_.id);
	  if(status == StatusAckDev2Ser)
	  {
		  root["organization"] = Json::Value(dev_.organization);
		  root["name"] = Json::Value(dev_.name);
		  root["interval"] = Json::Value(dev_.heartbeatInterval);
	  }
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);

}
JsonStatus_t JsonCmdManager::parseConfirm(string &js,Device_t &dev_,string &timeString)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  status = root["status"].asInt();
		  if(status == StatusParaSer2Dev)
		  {
			  dev_.heartbeatInterval = root["heartbeatInterval"].asInt();
			  dev_.organization = root["organization"].asString();
			  dev_.name = root["name"].asString();
			  dev_.id = root["id"].asString();
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
	  JsonStatus_t status;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  status = root["status"].asInt();
		  msg = root["dateTime"].asString();
	  }

	  return status;
}


string JsonCmdManager::makeAdminPwd(string &pwd,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDAdminPwd);
	  root["pwd"] = Json::Value(pwd);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseAdminPwd(string &js,string &adminPwd)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  status = root["status"].asInt();
		  if(status == StatusSet)
		  {
			  adminPwd = root["pwd"].asString();
		  }
	  }

	  return status;
}


string  JsonCmdManager::makeDoorPwd(string &pwd,JsonStatus_t status)
{

	  Json::Value root;
	  root["cmd"] = Json::Value(CMDDoorPwd);
	  root["pwd"] = Json::Value(pwd);
	  root["status"] = Json::Value((int)status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t  JsonCmdManager::parseDoorPwd(string &js,string &pwd)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {

		  status = root["status"].asInt();
		  pwd =  root["pwd"].asString();
	  }

	  return status;
}


string JsonCmdManager::makeDoorCtr(doorState_t &door,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDDoorCtr);
	  if(door == Lock)
		  root["door"] = Json::Value("lock");
	  else
		  root["door"] = Json::Value("unlock");
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseDoorCtr(string &js,doorState_t &door)
{
	  Json::Reader reader;
	  Json::Value root;

	  JsonStatus_t status;
	  string str;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {

		  status = (int)root["status"].asInt();
		  str = root["door"].asString();

		  if(str == "unlock")
		  {
			  door = UnLock;
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

string  JsonCmdManager::makeCourseInfo(CourseInfo_t &info,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDCourseInfo);
	  root["name"] = Json::Value(info.name);
	  root["class"] = Json::Value(info.class_);
	  root["num"] = Json::Value(info.num);
	  root["course"] = Json::Value(info.course);
	  root["picture.name"] = Json::Value(info.picture.name);
	  root["picture.datalen"] = Json::Value((int)info.picture.datalen);

	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t  JsonCmdManager::parseCourseInfo(string &js,CourseInfo_t &info)
{
	JsonStatus_t status;
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		status = root["status"].asInt();
		if(status == StatusSet )
		{
			info.name = root["name"].asString();
			info.class_ = root["class"].asString();
			info.num = root["num"].asString();
			info.course = root["course"].asString();


			info.picture.name = root["pic.name"].asString();  // 访问节点，upload_id = "UP000000"
			info.picture.data = root["pic.data"].asString();    // 访问节点，code = 100
			info.picture.datalen = root["pic.datalen"].asLargestUInt();


			if(info.picture.datalen != info.picture.data.length())
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
	JsonStatus_t status;
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		status = root["status"].asInt();
		Json::Value course = root["plan"];
		int course_size =  root["plan"].size();
		if(status == StatusOK || status == StatusSet)
		{
			plan.clear();
			for(int i = 0; i < course_size; i++)
			{
				Plan::PlanRow_t row;

				row.teacher = course[i]["teacher"].asString();
				row.class_ = course[i]["class"].asString();
				row.courser = course[i]["course"].asString();
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
	  JsonStatus_t status;

	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  status = root["status"].asInt();
		  msg = root["data"].asString();
	  }

	  return status;
}

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
string JsonCmdManager::makeAdPicAck(string &fullname,JsonStatus_t status)
{
	  Json::Value root;
	  uint64_t size = get_file_size(fullname.c_str());
	  root["cmd"] = Json::Value(CMDAdPic);
	  root["name"] = Json::Value(fullname);
	  root["size"] = Json::Value(size);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseFile(string js, char* directory, string &fullName,string &dataout)
{
	Json::Reader reader;
	Json::Value root;
	string fileName;
	string data;
	unsigned long length;
	JsonStatus_t status;
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


string JsonCmdManager::makeDeleteFile(string &fullName,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDDelAdPic);
	  root["name"] = Json::Value(fullName);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseDeleteFile(string js, char* directory, string &fileName, string &fullName)
{
	Json::Reader reader;
	Json::Value root;
	JsonStatus_t status;

	if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{

		fileName = root["name"].asString();  // 访问节点，upload_id = "UP000000"
		status = root["status"].asInt();
		//LOGE("len err:%ul ? %ul",length,data.length());
		fullName = directory ;
		fullName +=  fileName;
		LOGE("%s",fullName.c_str());
	}


	return status;
}


string JsonCmdManager::makeAdClearAck(JsonStatus_t status){
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDAdClear);
	  root["status"] = Json::Value(status);

//	  string temp =  root.asCString();

	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseAdClearAck(string &js){
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status;
	  std::string val_str;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  status = root["status"].asInt();
	  }

	  return status;
}
string JsonCmdManager::makeAdSet(Advertisement &set,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDAdSet);
	  root["enable"] = Json::Value(set.enable);
	  root["idleTime"] = Json::Value(set.idleTime);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseAdSet(string &js,Advertisement &set)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status;
	  std::string val_str;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  status = root["status"].asInt();
		  if(status == StatusOK)
		  {
		  }
		  else if(status == StatusSet)
		  {
			  set.idleTime = root["idleTime"].asInt();
			  set.enable = root["enable"].asBool();
		  }
	  }

	  return status;
}


string JsonCmdManager::makePerson(Person_t &person,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDPerson);
	  root["id"] = Json::Value(person.id);

	  root["name"] = Json::Value(person.name);
	  if(person.level < -1 || person.level > 10)
		  person.level = -1;
	  root["level"] = Json::Value(person.level);

	  if(person.fingers.size() > 0)
	  {
		  Json::Value fingers;
		  Json::Value finger;
		  for(int i = 0; i < person.fingers.size(); i++)
		  {
			  finger["finger"] = person.fingers[i];
			  fingers.append(finger);
		  }
		  root["fingers"] = Json::Value(fingers);
	  }

	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);

	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parsePerson(string &js,Person_t &person)
{
	JsonStatus_t status;
	Json::Reader reader;
	Json::Value root;
	if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		status = root["status"].asInt();
		if(status == StatusOK || status == StatusSet)
		{
			person.id = root["id"].asString();
			person.name = root["name"].asString();
			person.level = root["level"].asInt();
			Json::Value fingers = root["fingers"];
			int fingers_size =  root["fingers"].size();
			person.fingers.clear();
			for(int i = 0; i < fingers_size; i++)
			{
				person.fingers.push_back(fingers[i]["finger"].asString());
			}


			person.picture.name = root["pic.name"].asString();  // 访问节点，upload_id = "UP000000"
			person.picture.data = root["pic.data"].asString();    // 访问节点，code = 100
			person.picture.datalen = root["pic.datalen"].asLargestUInt();


			if(person.picture.datalen != person.picture.data.length())
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
		}

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
		  status = root["status"].asInt();
	  }

	  return status;
}

string JsonCmdManager::makeUpdate(DownloadInfo_t &info, JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDUpdate);
	  root["url"] = Json::Value(info.url);
	  root["port"] = Json::Value(info.port);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return pack(temp);
}
JsonStatus_t JsonCmdManager::parseUpdate(string &js,DownloadInfo_t &info)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status = StatusErr;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  status = root["status"].asInt();
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
		  status = root["status"].asInt();
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



int ParseJsonFromString()

{

  const char* str = "{\"uploadid\": \"UP000000\",\"code\": 100,\"msg\": \"\",\"files\": \"\"}";



  Json::Reader reader;

  Json::Value root;
  std::string upload_id;

  if (reader.parse(str, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素

  {

     upload_id = root["uploadid"].asString();  // 访问节点，upload_id = "UP000000"

    int code = root["code"].asInt();    // 访问节点，code = 100

  }

  return 0;

}

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


JsonCmdManager jm;
