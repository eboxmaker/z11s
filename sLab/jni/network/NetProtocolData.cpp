/*
 * NetProtocolData.cpp
 *
 *  Created on: 2020年4月15日
 *      Author: Administrator
 */


#include "netprotocoldata.h"
#include "aes/myaes256.h"
#include "lib/md5.h"
#include "json/json.h"
#include "utils/log.h"



const char *cmd_table[] = {
		"未知",
		"系统更新",
		"设备重启",
		"ID读取",
		"版本信息",
		"心跳",
		"登录",
		"组织单位",
		"部门",
		"日期时间",
		"电源控制",
		"获取门锁状态",
		"课程信息",
		"课程表",
		"广播",
		"二维码",
		"本地管理员密码设置",
		"门密码",
		"密码",
		"更新人员列表",
		"查询人员",
		"更新指纹",
		"本地管理员密码设置",
		"本地管理员密码设置",
		"本地管理员密码设置",
		"本地管理员密码设置",
		"本地管理员密码设置",
//		"",
//		"",
};

const string Status::Set("Set");
const string Status::Get("Get");
const string Status::OK("OK");
const string Status::Err("Err");


const string Cmd::Unknown("Unknown");
const string Cmd::Update("Update");
const string Cmd::Reboot("Reboot");
const string Cmd::ID("ID");
const string Cmd::Version("Version");
const string Cmd::Heartbeat("Heartbeat");
const string Cmd::Login("Login");
const string Cmd::Organization("Organization");
const string Cmd::Department("Department");// = 8,//包含department
const string Cmd::DateTime("DateTime");// = 9,
const string Cmd::DoorLockControl("DoorLockControl");//,
const string Cmd::DoorState("DoorState");//,
const string Cmd::CourseInfo("CourseInfo");//课程信息
const string Cmd::Plan("Plan");//计划（课程表）
const string Cmd::Broadcast("Broadcast");//
const string Cmd::QRCode("QRCode");//
const string Cmd::LocalPassword("LocalPassword");//
const string Cmd::DoorPassword("DoorPassword");//
const string Cmd::PersonList("PersonList");//
const string Cmd::PersonGet("PersonGet");//
const string Cmd::PersonUpdate("PersonUpdate");//




static string key =  "12345678900000001234567890000000";
static string iv =  "1234567890000000";
AesEncryptor *aes = new AesEncryptor(key,iv);





void pack(NetProtocolData &msg)
{
	string str;
	string js;

	MD5 md5(msg.data);

	str = aes->encrypt(msg.data);
//	LOGD("(%d):%s",md5.toStr().size(),md5.toStr().c_str());
//	LOGD("data src(%d):%s",msg.data.size() ,msg.data.c_str());
//	LOGE("data aes(%d):%s",str.size() ,str.c_str());
	js = aes->decrypt(str);
//	LOGD("data:%s",js.c_str());

	Json::Value root;
	root["sign"] = Json::Value(md5.toStr());
	root["data"] = Json::Value(str);

	Json::FastWriter fw;
	msg.data =  fw.write(root);

//	Json::StyledWriter sw;
//	msg.data =  sw.write(root);


//	LOGD("msg:%s",msg.data.c_str());
}
bool unPack(std::string& package,std::string& js)
{
	  Json::Reader reader;

	  Json::ValueType  item_type;
	  Json::Value root;
	  string data;
	  string md5str;
	  if (reader.parse(package, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	  {
//		  md5str = root["sign"].asString();
//		  data = root["data"].asString();
		  if(root.isMember("sign"))
		  {
			  item_type = root["sign"].type();
			  if(item_type == Json::stringValue)
			  {
				  md5str = root["sign"].asString();
//				  LOGD("：%s",md5str.c_str());
			  }
			  else
			  {
				  LOGE(" 类型错误");
			  }
		  }
		  else{
			  LOGE("不存在sign");
			  return false;
		  }

		  if(root.isMember("data"))
		  {
			  item_type = root["data"].type();
			  if(item_type == Json::stringValue)
			  {
				  data = root["data"].asString();
//				  LOGD("src data：%s",data.c_str());
			  }
			  else
			  {
				  LOGE("data 类型错误");
			  }
		  }
		  else{
			  LOGE("不存在data");
			  return false;

		  }
	  }
	  else
	  {
		  LOGE("帧错误");
		  return false;
	  }
//	  js = "";
//	  LOGD("测试1：%s",js.c_str());
	  js = aes->decrypt(data);
//	  LOGD("测试2(size=%d)：%s",js.size(),js.c_str());

//	  string test = aes->decrypt(data);
//	  LOGD("测试test(size=%d)：%s",test.size(),test.c_str());


//	  js = js.substr(0,js.find_last_of('}') + 1);
//	  LOGD("测试4(size=%d)：%s",js.size(),js.c_str());

	  MD5 md5(js);
	  string checkMD5 = md5.toStr();

//	  LOGE("un md5:%s",checkMD5.c_str());
//	  LOGE("un data:%s(len:%d,size:%d)",js.c_str(),js.length(),js.size());

	  if(checkMD5 == md5str)
	  {
//		  LOGD("解密：%s",js.c_str());
		  return true;
		  //LOGD("md5正确");
	  }
	  else
	  {
		  LOGE("md5错误");
		  LOGE("src md5：%s",md5str.c_str());
		  LOGE("src data：%s",data.c_str());
		  LOGE("un md5:%s",checkMD5.c_str());
		  LOGE("un data:%s(len:%d,size:%d)",js.c_str(),js.length(),js.size());
		  return false;
	  }
	  return false;
}


