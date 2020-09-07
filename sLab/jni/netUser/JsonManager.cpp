/*
 * JsonManager.cpp
 *
 *  Created on: 2020年4月12日
 *      Author: Administrator
 */

#include "jsonmanager.h"
#include "type.h"
#include "VERSION.h"
#include "lib/uid.h"
#include "utils/timehelper.h"
#include "lib/base64.h"


NetProtocolData makeUpdate(HttpInfo_t &info, string status)
{
	NetProtocolData msg;
	Json::Value root;
	root["cmd"] = Json::Value(Cmd::Update);
	root["status"] = Json::Value(status);

	Json::FastWriter fw;
	msg.data =  fw.write(root);
	LOGD("测试下载：%s",msg.data.c_str());

//	Json::StyledWriter sw;
//	tmp.data =  sw.write(root);
	msg.cmd = Cmd::Update;
	msg.status = status;
	msg.retryTimes = 0;

	return msg;
}

string parseUpdate(const NetProtocolData &data,HttpInfo_t &info)
{
	Json::Reader reader;
	Json::Value root;
	string status = Status::Err;

	if (!reader.parse(data.data, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		LOGE("解析JSON msg 错误");
		return Status::Err;
	}
	if(!root.isMember("cmd")){LOGE("不存在：cmd");return status;}
	if(!root["cmd"].type() == Json::stringValue){LOGE("cmd:类型错误");return status;}
	if(!root.isMember("status")){LOGE("不存在：status");return status;}
	if(!root["status"].type() == Json::stringValue){LOGE("status:类型错误");return status;}
	if(!root.isMember("url")){LOGE("不存在：url");return status;}
	if(!root["url"].type() == Json::stringValue){LOGE("url:类型错误");return status;}
	if(!root.isMember("port")){LOGE("不存在：port");return status;}
	if(!root["port"].type() == Json::stringValue){LOGE("port:类型错误");return status;}

	status = (string)root["status"].asString();
	if(status == Status::Set || status == Status::OK || status == Status::Get)
	{
		info.url = root["url"].asString();
		info.port = atoi(root["port"].asString().c_str());
	}


	return status;
}


NetProtocolData makeReboot(){
	NetProtocolData msg;
	Json::Value root;
	root["cmd"] = Json::Value(Cmd::Reboot);
	root["status"] = Json::Value(Status::OK);
	Json::StyledWriter sw;
	msg.data =  sw.write(root);
	msg.cmd = Cmd::Reboot;
	msg.status = Status::OK;
	msg.retryTimes = 0;

	return msg;
}

NetProtocolData makeID()
{
	NetProtocolData msg;
	Json::Value root;
	root["cmd"] = Json::Value(Cmd::ID);
	root["id"] = Json::Value(Uid::get_hex_string());
	root["status"] = Json::Value(Status::OK);
	Json::StyledWriter sw;
	msg.data =  sw.write(root);
	msg.cmd = Cmd::Reboot;
	msg.status = Status::OK;
	msg.retryTimes = 0;

	return msg;
}
NetProtocolData makeVersion()
{
	NetProtocolData msg;
	Json::Value root;
	root["cmd"] = Json::Value(Cmd::Version);
	root["version"] = Json::Value(VERSION);
	root["compilationDate"] = Json::Value(__DATE__);
	root["status"] = Json::Value(Status::OK);
	Json::StyledWriter sw;
	msg.data =  sw.write(root);
	msg.cmd = Cmd::Reboot;
	msg.status = Status::OK;
	msg.retryTimes = 0;

	return msg;
}


NetProtocolData makeHeartbeat(string status)
{
	//{"cmd":2,"value":"hello world","status":2}
	NetProtocolData msg;

	Json::Value root;
	root["cmd"] = Json::Value(Cmd::Heartbeat);
	root["value"] = Json::Value("hello world");
	root["status"] = Json::Value(status);

	Json::FastWriter fw;
	msg.data =  fw.write(root);

//	Json::StyledWriter sw;
//	tmp.data =  sw.write(root);
	msg.cmd = Cmd::Heartbeat;
	msg.status = status;
	msg.retryTimes = 0;

	return msg;
}

string parseHeartbeat(const NetProtocolData &data,string &id)
{
	Json::Reader reader;
	Json::Value root;

	string status = Status::Err;

	if (!reader.parse(data.data, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		LOGE("解析JSON msg 错误");
		return Status::Err;
	}
	if(!root.isMember("cmd")){LOGE("不存在：cmd");return status;}
	if(!root["cmd"].type() == Json::stringValue){LOGE("cmd:类型错误");return status;}
	if(!root.isMember("status")){LOGE("不存在：status");return status;}
	if(!root["status"].type() == Json::stringValue){LOGE("status:类型错误");return status;}
	if(!root.isMember("id")){LOGE("不存在：id");return status;}
	if(!root["id"].type() == Json::stringValue){LOGE("id:类型错误");return status;}
	if(!root.isMember("value")){LOGE("不存在：value");return status;}
	if(!root["value"].type() == Json::stringValue){LOGE("value:类型错误");return status;}

	id = root["id"].asString();
	status = root["status"].asString();
	return status;
}

NetProtocolData makeLogin(string status)
{
	//{"cmd":2,"value":"hello world","status":2}
	NetProtocolData msg;

	Json::Value root;


	root["cmd"] = Json::Value(Cmd::Login);
	root["id"] = Json::Value(Uid::get_hex_string());
	root["version"] = Json::Value(VERSION);
	root["compilationDate"] = Json::Value(__DATE__);
	root["status"] = Json::Value(status);

	Json::FastWriter fw;
	msg.data =  fw.write(root);

//	Json::StyledWriter sw;
//	msg.data =  sw.write(root);
	msg.cmd = Cmd::Login;
	msg.status = status;
	msg.retryTimes = 0;

	return msg;
}
string parseLogin(const NetProtocolData &data,DevicePara_t &info)
{
	Json::Reader reader;
	Json::Value root;

	string status = Status::Err;



	if (!reader.parse(data.data, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		LOGE("解析JSON msg 错误");
		return Status::Err;
	}
	if(!root.isMember("cmd")){LOGE("不存在：cmd");return status;}
	if(!root["cmd"].type() == Json::stringValue){LOGE("cmd:类型错误");return status;}
	if(!root.isMember("status")){LOGE("不存在：status");return status;}
	if(!root["status"].type() == Json::stringValue){LOGE("status:类型错误");return status;}
	if(!root.isMember("organization")){LOGE("不存在：organization");return status;}
	if(!root["organization"].type() == Json::stringValue){LOGE("organization:类型错误");return status;}
	if(!root.isMember("department")){LOGE("不存在：id");return status;}
	if(!root["department"].type() == Json::stringValue){LOGE("department:类型错误");return status;}
	if(!root.isMember("time")){LOGE("不存在：time");return status;}
	if(!root["time"].type() == Json::stringValue){LOGE("time:类型错误");return status;}


	info.login_time = root["time"].asString();
	info.org = root["organization"].asString();
	info.department = root["department"].asString();
	status = root["status"].asString();
	TimeHelper::setDateTime(info.login_time.c_str());
	return status;
}


NetProtocolData makeOrg(string status,string &org)
{
	NetProtocolData msg;

	Json::Value root;
	root["cmd"] = Json::Value(Cmd::Organization);
	if(status == Status::Get)
	{
		root["organization"] = Json::Value("");
	}
	else if(status == Status::Set || status == Status::OK)
	{
		root["organization"] = Json::Value(org);
	}
	else
	{
		root["organization"] = Json::Value(org);
	}
	root["status"] = Json::Value(status);

	Json::FastWriter fw;
	msg.data =  fw.write(root);

//	Json::StyledWriter sw;
//	tmp.data =  sw.write(root);

	msg.cmd = Cmd::Organization;
	msg.status = status;
	msg.retryTimes = 0;

	return msg;
}
string parseOrg(const NetProtocolData &data,string &name)
{
	Json::Reader reader;
	Json::Value root;
	string status = Status::Err;

	if (!reader.parse(data.data, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		LOGE("解析JSON msg 错误");
		return Status::Err;
	}
	if(!root.isMember("cmd")){LOGE("不存在：cmd");return status;}
	if(!root["cmd"].type() == Json::stringValue){LOGE("cmd:类型错误");return status;}
	if(!root.isMember("status")){LOGE("不存在：status");return status;}
	if(!root["status"].type() == Json::stringValue){LOGE("status:类型错误");return status;}
	if(!root.isMember("organization")){LOGE("不存在：organization");return status;}
	if(!root["organization"].type() == Json::stringValue){LOGE("organization:类型错误");return status;}


	name = root["organization"].asString();

	return status;
}

NetProtocolData makeDepartment(string status,string &department)
{
	NetProtocolData msg;

	Json::Value root;
	root["cmd"] = Json::Value(Cmd::Department);
	if(status == Status::Get)
	{
		root["department"] = Json::Value("");
	}
	else if(status == Status::Set || status == Status::OK)
	{
		root["department"] = Json::Value(department);
	}
	else
	{
		root["department"] = Json::Value(department);
	}
	root["status"] = Json::Value(status);

	Json::FastWriter fw;
	msg.data =  fw.write(root);

//	Json::StyledWriter sw;
//	tmp.data =  sw.write(root);


	msg.cmd = Cmd::Department;
	msg.status = status;
	msg.retryTimes = 0;

	return msg;
}
string parseDepartment(const NetProtocolData &data,string &department)
{
	Json::Reader reader;
	Json::Value root;
	string status = Status::Err;

	if (!reader.parse(data.data, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		LOGE("解析JSON msg 错误");
		return Status::Err;
	}
	if(!root.isMember("cmd")){LOGE("不存在：cmd");return status;}
	if(!root["cmd"].type() == Json::stringValue){LOGE("cmd:类型错误");return status;}
	if(!root.isMember("status")){LOGE("不存在：status");return status;}
	if(!root["status"].type() == Json::stringValue){LOGE("status:类型错误");return status;}
	if(!root.isMember("department")){LOGE("不存在：department");return status;}
	if(!root["department"].type() == Json::stringValue){LOGE("department:类型错误");return status;}


	department = root["department"].asString();

	return status;
}

NetProtocolData makeDateTime(string status)
{
	char timeStr[20];
	string str ;
	struct tm *t = TimeHelper::getDateTime();
	sprintf(timeStr, "%d-%d-%d %02d:%02d:%02d", 1900 + t->tm_year, t->tm_mon + 1, t->tm_mday,\
												t->tm_hour,t->tm_min,t->tm_sec);
	str = timeStr;

	NetProtocolData msg;

	Json::Value root;
	root["cmd"] = Json::Value(Cmd::DateTime);
	root["dateTime"] = Json::Value(str);
	root["status"] = Json::Value(status);
	Json::StyledWriter sw;
	msg.data =  sw.write(root);
	msg.cmd = Cmd::DateTime;
	msg.status = Status::OK;
	msg.retryTimes = 0;

	return msg;
}
string parseDateTime(const NetProtocolData &data)
{
	Json::Reader reader;
	Json::Value root;
	string dtStr;
	string status = Status::Err;

	if (!reader.parse(data.data, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		LOGE("解析JSON msg 错误");
		return Status::Err;
	}
	if(!root.isMember("cmd")){LOGE("不存在：cmd");return status;}
	if(!root["cmd"].type() == Json::stringValue){LOGE("cmd:类型错误");return status;}
	if(!root.isMember("status")){LOGE("不存在：status");return status;}
	if(!root["status"].type() == Json::stringValue){LOGE("status:类型错误");return status;}
	if(!root.isMember("dateTime")){LOGE("不存在：dateTime");return status;}
	if(!root["dateTime"].type() == Json::stringValue){LOGE("dateTime:类型错误");return status;}


	status = (string)root["status"].asString();
	if(status == Status::Set)
	{
		dtStr = root["dateTime"].asString();
		TimeHelper::setDateTime(dtStr.c_str());
	}


	return status;
}

NetProtocolData makeDoorCtr(string status,DoorLockState_t door)
{
	NetProtocolData msg;
	Json::Value root;

	root["cmd"] = Json::Value(Cmd::DoorLockControl);

	switch(door)
	{
		case Lock: root["doorControl"] = Json::Value("lock");break;
		case Unlock: root["doorControl"] = Json::Value("unlock");break;
	}
	root["status"] = Json::Value(status);

	Json::StyledWriter sw;
	msg.data =  sw.write(root);
	msg.cmd = Cmd::DoorLockControl;
	msg.status = Status::OK;
	msg.retryTimes = 0;

	LOGD("DoorLockControl回复：%s",msg.data.c_str());
	return msg;
}
string 	parseDoorCtr(const NetProtocolData &data,DoorLockState_t &door)
{
	  Json::Reader reader;
	  Json::Value root;

	  string status = Status::Err;
	  string str;
	if (!reader.parse(data.data, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		LOGE("解析JSON msg 错误");
		return Status::Err;
	}
	if(!root.isMember("cmd")){LOGE("不存在：cmd");return status;}
	if(!root["cmd"].type() == Json::stringValue){LOGE("cmd:类型错误");return status;}
	if(!root.isMember("status")){LOGE("不存在：status");return status;}
	if(!root["status"].type() == Json::stringValue){LOGE("status:类型错误");return status;}
	if(!root.isMember("doorControl")){LOGE("不存在：doorControl");return status;}
	if(!root["doorControl"].type() == Json::stringValue){LOGE("doorControl:类型错误");return status;}


	status = root["status"].asString();
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


	  return status;
}

NetProtocolData makeDoorState(string status,DoorState_t door)
{
	NetProtocolData msg;
	Json::Value root;
	root["cmd"] = Json::Value(Cmd::DoorState);

	switch(door)
	{
	case LockClose: root["doorState"] = Json::Value("lockClose");break;
	case LockOpen: root["doorState"] = Json::Value("lockOpen");break;
	case UnlockClose: root["doorState"] = Json::Value("unlockClose");break;
	case UnlockOpen: root["doorState"] = Json::Value("unlockOpen");break;
	}

	root["status"] = Json::Value(status);
	Json::StyledWriter sw;
	msg.data =  sw.write(root);
	msg.cmd = Cmd::DoorState;
	msg.status = status;
	msg.retryTimes = 0;

	return msg;
}


NetProtocolData	makeCourseInfo(string status,CourseInfo_t info,int retrytimes = 0)
{
	NetProtocolData msg;
	Json::Value root;
	char buf[128];

	root["cmd"] = Json::Value(Cmd::CourseInfo);

	if(status == Status::OK)
	{
		root["name"] = Json::Value(info.name);
		root["class"] = Json::Value(info.class_);
		root["num"] = Json::Value(info.num);
		root["course"] = Json::Value(info.course);
		root["picture_name"] = Json::Value(info.picture.name);

		sprintf(buf,"%u",info.picture.dataLength);
		root["picture_dataLength"] = Json::Value(buf);
	}

	root["status"] = Json::Value(status);

	Json::StyledWriter sw;
	msg.data =  sw.write(root);
	msg.cmd = Cmd::CourseInfo;
	msg.status = status;
	msg.retryTimes = retrytimes;


//	LOGD("COURSER INFO:%s",msg.data.c_str());
	return msg;

}
string	parseCourseInfo(const NetProtocolData data, CourseInfo_t &info)
{
	string status = Status::Err;
	Json::Reader reader;
	Json::Value root;
	string temp ;
	if (!reader.parse(data.data, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		LOGE("解析JSON msg 错误");
		return Status::Err;
	}
	if(!root.isMember("cmd")){LOGE("不存在：cmd");return status;}
	if(!root["cmd"].type() == Json::stringValue){LOGE("cmd:类型错误");return status;}
	if(!root.isMember("status")){LOGE("不存在：status");return status;}
	if(!root["status"].type() == Json::stringValue){LOGE("status:类型错误");return status;}
	if(!root.isMember("name")){LOGE("不存在：name");return status;}
	if(!root["name"].type() == Json::stringValue){LOGE("name:类型错误");return status;}
	if(!root.isMember("class")){LOGE("不存在：class");return status;}
	if(!root["class"].type() == Json::stringValue){LOGE("class:类型错误");return status;}
	if(!root.isMember("num")){LOGE("不存在：num");return status;}
	if(!root["num"].type() == Json::stringValue){LOGE("num:类型错误");return status;}
	if(!root.isMember("course")){LOGE("不存在：course");return status;}
	if(!root["course"].type() == Json::stringValue){LOGE("course:类型错误");return status;}

	if(!root.isMember("picture_name")){LOGE("不存在：picture_name");return status;}
	if(!root["picture_name"].type() == Json::stringValue){LOGE("picture_name:类型错误");return status;}
	if(!root.isMember("picture_data")){LOGE("不存在：picture_data");return status;}
	if(!root["picture_data"].type() == Json::stringValue){LOGE("picture_data:类型错误");return status;}
	if(!root.isMember("picture_dataLength")){LOGE("不存在：picture_dataLength");return status;}
	if(!root["picture_dataLength"].type() == Json::stringValue){LOGE("picture_dataLength:类型错误");return status;}




	status = (string)root["status"].asString();

	if(status == Status::Set || status == Status::OK  )
	{
		info.name = root["name"].asString();
		info.class_ = root["class"].asString();
		info.num = root["num"].asString();
		info.course = root["course"].asString();


		info.picture.name = root["picture_name"].asString();  // 访问节点，upload_id = "UP000000"
		//LOGD("info->picture_name:%s",info.picture.name.c_str());
		info.picture.name = "courseInfo.jpg";  // 访问节点，upload_id = "UP000000"

		info.picture.data = root["picture_data"].asString();    // 访问节点，code = 100
		//LOGD("info->picture_data:%s",info.picture.data.c_str());


		temp  = root["picture_dataLength"].asString();

		info.picture.dataLength = atoi(temp.c_str());
		LOGD("info->picture_dataLength:%d",info.picture.dataLength);



		if(info.picture.dataLength != info.picture.data.length())
		{
			LOGE("头像长度不匹配");
			return Status::Err;
		}
		string picBuf;
		picBuf = info.picture.data;
		info.picture.data = "";
		if(Base64::Decode(picBuf,&info.picture.data))
		{

		}
	}



	return status;
}

NetProtocolData makePlan(string status)
{
	NetProtocolData msg;
	Json::Value root;
	root["cmd"] = Json::Value(Cmd::Plan);
	root["status"] = Json::Value(status);
	Json::StyledWriter sw;
	msg.data =  sw.write(root);
	msg.cmd = Cmd::Plan;
	msg.status = status;
	msg.retryTimes = 0;

	return msg;
}
string	parsePlan(const NetProtocolData &data, Plan &plan)
{
	string status = Status::Err;
	Json::Reader reader;
	Json::Value root;

	if (!reader.parse(data.data, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		LOGE("解析JSON msg 错误");
		return Status::Err;
	}
	if(!root.isMember("cmd")){LOGE("不存在：cmd");return status;}
	if(!root["cmd"].type() == Json::stringValue){LOGE("cmd:类型错误");return status;}
	if(!root.isMember("status")){LOGE("不存在：status");return status;}
	if(!root["status"].type() == Json::stringValue){LOGE("status:类型错误");return status;}
	if(!root.isMember("plan")){LOGE("不存在：plan");return status;}
	if(!root["plan"].type() == Json::arrayValue){LOGE("plan:类型错误");return status;}



	status = (string)root["status"].asString();

	Json::Value course = root["plan"];
	int course_size =  root["plan"].size();
	if(status == Status::OK || status == Status::Set)
	{
		plan.clear();
		LOGD("SIZE course_size = %d",course_size);
		for(int i = 0; i < course_size; i++)
		{
			Plan::PlanRow_t row;
			if(!course[i].isMember("unit")){LOGE("不存在：unit");return status;}
			if(!course[i]["unit"].type() == Json::stringValue){LOGE("unit:类型错误");return status;}
			if(!course[i].isMember("startTime")){LOGE("不存在：startTime");return status;}
			if(!course[i]["startTime"].type() == Json::stringValue){LOGE("startTime:类型错误");return status;}
			if(!course[i].isMember("endTime")){LOGE("不存在：endTime");return status;}
			if(!course[i]["endTime"].type() == Json::stringValue){LOGE("endTime:类型错误");return status;}
			if(!course[i].isMember("teacher")){LOGE("不存在：teacher");return status;}
			if(!course[i]["teacher"].type() == Json::stringValue){LOGE("teacher:类型错误");return status;}
			if(!course[i].isMember("class")){LOGE("不存在：class");return status;}
			if(!course[i]["class"].type() == Json::stringValue){LOGE("class:类型错误");return status;}
			if(!course[i].isMember("course")){LOGE("不存在：course");return status;}
			if(!course[i]["course"].type() == Json::stringValue){LOGE("course:类型错误");return status;}


			row.unit	 	= course[i]["unit"].asString();
			row.startTime 	= course[i]["startTime"].asString();
			row.endTime 	= course[i]["endTime"].asString();
			row.teacher 	= course[i]["teacher"].asString();
			row.class_ 		= course[i]["class"].asString();
			row.course	 	= course[i]["course"].asString();
			gPlan.add(row);
		}
		gPlan.print();
	}



	return status;
}

NetProtocolData	makeBroadcast(string status,string &broadcast_msg)
{
	NetProtocolData msg;
	Json::Value root;
	root["cmd"] = Json::Value(Cmd::Broadcast);
	root["data"] = Json::Value(broadcast_msg);
	root["status"] = Json::Value(status);
	Json::StyledWriter sw;
	msg.data =  sw.write(root);
	msg.cmd = Cmd::LocalPassword;
	msg.status = status;
	msg.retryTimes = 0;
	return msg;
}
string 	parseBroadcast(const NetProtocolData &data,string &broadcast_msg)
{
	Json::Reader reader;

	Json::Value root;
	string status = Status::Err;

	if (!reader.parse(data.data, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		LOGE("解析JSON msg 错误");
		return Status::Err;
	}
	if(!root.isMember("cmd")){LOGE("不存在：cmd");return status;}
	if(!root["cmd"].type() == Json::stringValue){LOGE("cmd:类型错误");return status;}
	if(!root.isMember("status")){LOGE("不存在：status");return status;}
	if(!root["status"].type() == Json::stringValue){LOGE("status:类型错误");return status;}
	if(!root.isMember("data")){LOGE("不存在：data");return status;}
	if(!root["data"].type() == Json::stringValue){LOGE("data:类型错误");return status;}


	status = (string)root["status"].asString();
	broadcast_msg = root["data"].asString();


	return status;
}
NetProtocolData	makeQRCode(string status,int retrytimes = 0)
{
	NetProtocolData msg;
	Json::Value root;
	root["cmd"] = Json::Value(Cmd::QRCode);
	root["status"] = Json::Value(status);
	Json::StyledWriter sw;
	msg.data =  sw.write(root);
	msg.cmd = Cmd::QRCode;
	msg.status = status;
	msg.retryTimes = retrytimes;
	return msg;
}
string	parseQRCode(const NetProtocolData data, Picture_t &pic)
{
	string status = Status::Err;
	Json::Reader reader;
	Json::Value root;
	if (!reader.parse(data.data, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		LOGE("解析JSON msg 错误");
		return Status::Err;
	}
	if(!root.isMember("cmd")){LOGE("不存在：cmd");return status;}
	if(!root["cmd"].type() == Json::stringValue){LOGE("cmd:类型错误");return status;}
	if(!root.isMember("status")){LOGE("不存在：status");return status;}
	if(!root["status"].type() == Json::stringValue){LOGE("status:类型错误");return status;}
	if(!root.isMember("name")){LOGE("不存在：name");return status;}
	if(!root["name"].type() == Json::stringValue){LOGE("name:类型错误");return status;}
	if(!root.isMember("data")){LOGE("不存在：data");return status;}
	if(!root["data"].type() == Json::stringValue){LOGE("data:类型错误");return status;}
	if(!root.isMember("dataLength")){LOGE("不存在：dataLength");return status;}
	if(!root["dataLength"].type() == Json::stringValue){LOGE("dataLength:类型错误");return status;}



	status = (string)root["status"].asString();
	if(status == Status::Set || status == Status::OK )
	{

		pic.name = root["name"].asString();
		LOGD("---name:%s",pic.name.c_str());
		pic.name = "qrcode.jpg";

		pic.data = root["data"].asString();    // 访问节点，code = 100
//		LOGD("---data:%s",pic.data.c_str());

		pic.dataLength = atoi(root["dataLength"].asString().c_str());
//		LOGD("---dataLength:%d",pic.dataLength);

		if(pic.dataLength != pic.data.length())
		{
			LOGE("头像长度不匹配");
			return Status::Err;
		}
		string picBuf;
		picBuf = pic.data;
		pic.data = "";
		if(Base64::Decode(picBuf,&pic.data))
		{

		}
	}
	  return status;
}




NetProtocolData makeLocalPassword(string status,string &password)
{
	NetProtocolData msg;

	Json::Value root;
	root["cmd"] = Json::Value(Cmd::LocalPassword);
	root["password"] = Json::Value(password);
	root["status"] = Json::Value(status);
	Json::StyledWriter sw;
	msg.data =  sw.write(root);
	msg.cmd = Cmd::LocalPassword;
	msg.status = status;
	msg.retryTimes = 0;

	return msg;
}
string parseLocalPassword(const NetProtocolData &data,string &password)
{
	Json::Reader reader;

	Json::Value root;
	string status = Status::Err;
	if (!reader.parse(data.data, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		LOGE("解析JSON msg 错误");
		return Status::Err;
	}
	if(!root.isMember("cmd")){LOGE("不存在：cmd");return status;}
	if(!root["cmd"].type() == Json::stringValue){LOGE("cmd:类型错误");return status;}
	if(!root.isMember("status")){LOGE("不存在：status");return status;}
	if(!root["status"].type() == Json::stringValue){LOGE("status:类型错误");return status;}
	if(!root.isMember("password")){LOGE("不存在：password");return status;}
	if(!root["password"].type() == Json::stringValue){LOGE("password:类型错误");return status;}

	status = (string)root["status"].asString();

	if(status == Status::Set)
	{
		password = root["password"].asString();
	}


}

NetProtocolData  makeDoorPwd(string status,string &pwd)
{
	NetProtocolData msg;

	Json::Value root;
	root["cmd"] = Json::Value(Cmd::DoorPassword);
	root["password"] = Json::Value(pwd);
	root["status"] = Json::Value(status);
	Json::StyledWriter sw;
	msg.data =  sw.write(root);
	msg.cmd = Cmd::DoorPassword;
	msg.status = status;
	msg.retryTimes = 0;

	return msg;
}
string  parseDoorPwd(const NetProtocolData &data,string &pwd)
{
	Json::Reader reader;

	Json::Value root;
	string status = Status::Err;

	if (!reader.parse(data.data, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		LOGE("解析JSON msg 错误");
		return Status::Err;
	}
	if(!root.isMember("cmd")){LOGE("不存在：cmd");return status;}
	if(!root["cmd"].type() == Json::stringValue){LOGE("cmd:类型错误");return status;}
	if(!root.isMember("status")){LOGE("不存在：status");return status;}
	if(!root["status"].type() == Json::stringValue){LOGE("status:类型错误");return status;}
	if(!root.isMember("password")){LOGE("不存在：password");return status;}
	if(!root["password"].type() == Json::stringValue){LOGE("password:类型错误");return status;}

	status = (string)root["status"].asString();
	pwd =  root["password"].asString();
	return status;
}


NetProtocolData makePersonList(string status,int retrytimes)
{
	NetProtocolData msg;

	Json::Value root;
	root["cmd"] = Json::Value(Cmd::PersonList);
	root["status"] = Json::Value(status);
	Json::StyledWriter sw;
	msg.data = root.toStyledString();
//	msg.data =  sw.write(root);
	msg.cmd = Cmd::PersonList;
	msg.status = status;
	msg.retryTimes = retrytimes;

	return msg;
}

string parsePersonList(const NetProtocolData data,PersonInfoList_t &personList)
{
	string status = Status::Err;
	PersonInfo_t person;
	Json::Reader reader(Json::Features::strictMode());
	Json::Value root;
	LOGD("开始解析:Person");
	if (reader.parse(data.data, root) == false)  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		LOGE("解析失败:Person");
		return status;
	}
	if(!root.isMember("cmd")){LOGE("不存在：cmd");return status;}
	if(!root["cmd"].type() == Json::stringValue){LOGE("cmd:类型错误");return status;}
	if(!root.isMember("status")){LOGE("不存在：status");return status;}
	if(!root["status"].type() == Json::stringValue){LOGE("status:类型错误");return status;}
	if(!root.isMember("persons")){LOGE("不存在：persons");return status;}
	if(!root["persons"].isArray() == false){LOGE("persons:类型错误");return status;}

	LOGD("解析成功:Person");
	status = (string)root["status"].asString();
	if((status == Status::Err)|| (status == Status::Get))
	{
		LOGE("状态不需要本地解析:%s",status.c_str());
		return status;
	}
	personList.clear();
	LOGD("personList清空");
	Json::Value persons = root["persons"];
	LOGD("====人员数量：%d====",persons.size());
	for(Json::ArrayIndex i = 0; i < persons.size(); i++)
	{
		if(!persons[i].isMember("name")){LOGE("不存在：name");return status;}
		if(!persons[i]["name"].type() == Json::stringValue){LOGE("name:类型错误");return status;}
		if(!persons[i].isMember("id")){LOGE("不存在：id");return status;}
		if(!persons[i]["id"].type() == Json::stringValue){LOGE("id:类型错误");return status;}
		if(!persons[i].isMember("level")){LOGE("不存在：level");return status;}
		if(!persons[i]["level"].type() == Json::stringValue){LOGE("level:类型错误");return status;}
		if(!persons[i].isMember("lockControl")){LOGE("不存在：lockControl");return status;}
		if(!persons[i]["lockControl"].type() == Json::stringValue){LOGE("lockControl:类型错误");return status;}

		person.name = persons[i]["name"].asString();
		person.id = persons[i]["id"].asString();
		person.level = persons[i]["level"].asString();
		person.lockCtr = persons[i]["lockControl"].asString();


		if(!persons[i].isMember("fingers")){LOGE("不存在：fingers");continue ;}
		if(!persons[i]["fingers"].type() == Json::arrayValue){LOGE("fingers:类型错误");continue;}

		Json::Value fingers = persons[i]["fingers"];
		LOGD("===%s的指纹数量：%d===",person.name.c_str(),fingers.size());
		string temp;
		for(Json::ArrayIndex j = 0; j < fingers.size(); j++)
		{
			if(!fingers[j].isMember("finger")){LOGE("不存在：finger");continue;}
			if(!fingers[j]["finger"].type() == Json::stringValue){LOGE("finger:类型错误");continue;}

			temp = fingers[j]["finger"].asString();
			if(temp != ""){
				person.fingers.push_back(fingers[j]["finger"].asString());
				LOGD("finger:%s",person.fingers[j].c_str());
			}
			else{
			}
		}
	}
	return status;
}



NetProtocolData makePersonGet(string status,string id)
{
	NetProtocolData msg;

	Json::Value root;
	root["cmd"] = Json::Value(Cmd::PersonGet);
	root["id"] = Json::Value(id);
	root["status"] = Json::Value(status);
	Json::StyledWriter sw;
	msg.data = root.toStyledString();
	msg.cmd = Cmd::PersonGet;
	msg.status = status;
	msg.retryTimes = 0;

	return msg;
}
string parsePersonGet(const NetProtocolData &data,PersonInfo_t &person)
{
	Json::Reader reader;
	Json::Value root;

	string status = Status::Err;
	if (reader.parse(data.data, root) == false)  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{
		LOGE("解析失败:PersonGet");
		return status;
	}
	LOGD("解析成功:PersonGet");
	if(root.isMember("status")){
	  if(root["status"].type() == Json::stringValue)
		  status = (string)root["status"].asString();
	}
	if((status == Status::Err)|| (status == Status::Get))
	{
		LOGE("状态不需要本地解析:%s",status.c_str());
		return status;
	}

	if(status == Status::Set || (status == Status::OK))
	{
		if(!root.isMember("name")){LOGE("不存在：name");return status;}
		if(!root.isMember("id")){LOGE("不存在：id");return status;}
		if(!root.isMember("level")){LOGE("不存在：level");return status;}
		if(!root.isMember("lockControl")){LOGE("不存在：lockControl");return status;}
		if(!root["name"].type() == Json::stringValue){LOGE("name:类型错误");return status;}
		if(!root["id"].type() == Json::stringValue){LOGE("id:类型错误");return status;}
		if(!root["level"].type() == Json::stringValue){LOGE("level:类型错误");return status;}
		if(!root["lockControl"].type() == Json::stringValue){LOGE("lockControl:类型错误");return status;}

		person.name = root["name"].asString();
		person.id =root["id"].asString();
		person.level = root["level"].asString();
		person.lockCtr = root["lockControl"].asString();
		if(root.isMember("fingers"))
		{
			Json::Value fingers = root["fingers"];
			int fingers_size =  root["fingers"].size();
			LOGD("===%s的指纹数量：%d===",person.name.c_str(),fingers_size);
			string temp;
			for(int j = 0; j < fingers_size; j++)
			{
				temp = fingers[j]["finger"].asString();
				if(temp != "")
				{
					person.fingers.push_back(fingers[j]["finger"].asString());
					LOGD("finger:%s",person.fingers[j].c_str());
				}
				else
				{
				}
			}
		}
		else
		{
			LOGE("该成员不存在指纹对象");
		}
	}


	  return status;
}
NetProtocolData makePersonUpdate(string status,PersonInfo_t &person)
{
	NetProtocolData msg;
	Json::Value fingers;
	Json::Value root;


	root["cmd"] = Json::Value(Cmd::PersonUpdate);
	root["id"] = Json::Value(person.id);

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

	root["status"] = Json::Value(status);
	Json::StyledWriter sw;
	msg.data = root.toStyledString();
	LOGD("添加指纹后的数据：%s",msg.data.c_str());
	msg.cmd = Cmd::PersonUpdate;
	msg.status = status;
	msg.retryTimes = 0;

	return msg;
}

string parsePersonUpdate(const NetProtocolData &data)
{

}
NetProtocolData makeUnknown(string status)
{
	NetProtocolData msg;
	Json::Value root;

	root["cmd"] = Json::Value(Cmd::Unknown);
	root["status"] = Json::Value(status);
	Json::StyledWriter sw;
	msg.data = root.toStyledString();
	msg.cmd = Cmd::Unknown;
	msg.status = status;
	msg.retryTimes = 0;
	return msg;
}

//
//NetProtocolData makePassword(string status,string &password)
//{
//	NetProtocolData tmp;
//
//	Json::Value root;
//	root["cmd"] = Json::Value(Cmd::Password);
//	root["password"] = Json::Value(password);
//	root["status"] = Json::Value(status);
//	Json::StyledWriter sw;
//	tmp.data =  sw.write(root);
//	tmp.cmd = Cmd::Password;
//	tmp.status = Status::OK;
//	return tmp;
//}
//string parsePassword(const NetProtocolData &data,string &password)
//{
//	  Json::Reader reader;
//	  Json::Value root;
//
//	  string status = Status::Err;
//
//	  if (reader.parse(data.data, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
//	  {
//		  status = (string)root["status"].asString();
//		  if(status == Status::Set)
//		  {
//			  password = root["password"].asString();
//			  LOGD("密码：%s",password.c_str());
//		  }
//	  }
//	  return status;
//}
