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
string JsonCmdManager::makeHeartbeat(JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDHeartbeat);
	  root["value"] = Json::Value("hello");
	  root["status"] = Json::Value((int)status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return temp;
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




string JsonCmdManager::makeDoorCtr(doorState_t &door,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDDoorCtr);
	  if(status == Lock)
		  root["door"] = Json::Value("lock");
	  else
		  root["door"] = Json::Value("unlock");
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return temp;
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
string  JsonCmdManager::makeDoorPwd(string &pwd,JsonStatus_t status)
{

	  Json::Value root;
	  root["cmd"] = Json::Value(CMDDoorPwd);
	  root["pwd"] = Json::Value(pwd);
	  root["status"] = Json::Value((int)status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return temp;
}
JsonStatus_t  JsonCmdManager::parseDoorPwd(string &js,string &msg)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {

		  status = root["status"].asInt();
		  msg =  root["pwd"].asString();
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
	  return temp;
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

string JsonCmdManager::makePlan(JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDPlan);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return temp;
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
		for(int i = 0; i < course_size; i++)
		{
			PlanRow_t row;
			row.teacher = course[i]["teacher"].asString();
			row.class_ = course[i]["class"].asString();
			row.courser = course[i]["course"].asString();
			gPlan.add(row);
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
	  return temp;
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

string JsonCmdManager::makeAdSet(AdSet_t &set,JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDAdSet);
	  root["enable"] = Json::Value(set.enable);
	  root["displayTime"] = Json::Value(set.displayTime);
	  root["switchTime"] = Json::Value(set.switchTime);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return temp;
}
JsonStatus_t JsonCmdManager::parseAdSet(string &js,AdSet_t &set)
{
	  Json::Reader reader;

	  Json::Value root;
	  JsonStatus_t status;
	  AdSet_t temp;
	  std::string val_str;
	  if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
		  status = root["status"].asInt();
		  if(status == StatusOK)
		  {
		  }
		  else if(status == StatusSet)
		  {
			  set.displayTime = root["displayTime"].asInt();
			  set.switchTime = root["switchTime"].asInt();
			  set.enable = root["enable"].asBool();
		  }
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
	  return temp;
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

string JsonCmdManager::makeConfirm(string &id,string &name,JsonStatus_t status)
{

	//UTF8String u8 = L"UNICODE字符串";
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDConfirm);
	  root["id"] = Json::Value(id);
	  root["name"] = Json::Value(name);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return temp;

}
JsonStatus_t JsonCmdManager::parseConfirm(string &js)
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
string JsonCmdManager::makeDevID(string &id,JsonStatus_t status)
{

	  Json::Value root;
	  root["cmd"] = Json::Value(CMDDevID);
	  root["id"] = Json::Value(id);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return temp;

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
string JsonCmdManager::makeDevName(string &name,JsonStatus_t status)
{

	  Json::Value root;
	  root["cmd"] = Json::Value(CMDDevName);
	  root["name"] = Json::Value(name);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return temp;
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
string JsonCmdManager::makeQRCodeAck(JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDQR);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return temp;
}
string JsonCmdManager::makePicAck(JsonStatus_t status)
{
	  Json::Value root;
	  root["cmd"] = Json::Value(CMDAdPic);
	  root["status"] = Json::Value(status);
	  Json::FastWriter fw;
	  string temp =  fw.write(root);
	  return temp;
}
JsonStatus_t JsonCmdManager::parseFile(string str, char* directory, string &fullName)
{
	Json::Reader reader;
	Json::Value root;
	string fileName;
	string data;
	string dataout;
	unsigned long length;
	JsonStatus_t status;
	if (reader.parse(str, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{

		fileName = root["name"].asString();  // 访问节点，upload_id = "UP000000"
		data = root["data"].asString();    // 访问节点，code = 100
		length = root["dataLength"].asLargestUInt();
		//LOGE("len err:%ul ? %ul",length,data.length());

		if(length != data.length())
		{
			return StatusErr;
		}
		fullName = directory ;
		fullName +=  fileName;
		LOGE("%s",fullName.c_str());
	}

	Base64::Decode(data, &dataout);
	FILE *fp = fopen(fullName.c_str(), "w");
	if (fp != NULL)
	{
		int writeLength = fwrite(dataout.c_str(), sizeof(char), dataout.size(), fp);
	}
	else
	{
		return StatusErr;
	}
	if (fclose(fp) != 0) {
		return StatusErr;
	}
	return StatusSet;
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
