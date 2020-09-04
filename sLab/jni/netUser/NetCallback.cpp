/*
 * NetCallback.cpp
 *
 *  Created on: 2020年4月13日
 *      Author: Administrator
 */

#include "NetCallback.h"
#include "device.h"
#include "network/netcontext.h"
#include "jsonmanager.h"
#include<unistd.h>
#include<sys/reboot.h>
#include "http/httpDownload.h"
#include "type.h"
#include "netuser/netlogintask.h"
#include "door.h"
#include "global.h"
#include "person.h"

void onNetDataToExeUpdate(const NetProtocolData &data);
void onNetDataServerAck(const NetProtocolData &data);


void onDownload(std::string &msg)
{
	LOGD("下载事件");

	if(msg == ""){
		LOGD("下载成功");
		if(NETCONTEXT->connected())
			NETCONTEXT->Close();
	}
	else
	{
		LOGD("下载结果:%s",msg.c_str());
	}

}

void onNetDataToExeUpdate(const NetProtocolData &data)
{
	HttpInfo_t http;
	std::string filename;
	string org,department;
	string tempstr;
	float temperature;
	DoorLockState_t doorState;
	if(data.status == Status::OK || data.status == Status::Err)//不处理回复消息
	{
//		LOGD("这是一个服务器回复命令");
		return ;
	}
	if(data.err == -1)
	{
//		LOGD("这是一个本地删除命令");
		return ;
	}
	LOGD("触发回调函数：服务器命令执行");
	NetProtocolData tmp;

	if(data.cmd == Cmd::Update)
	{
		parseUpdate(data, http);
		filename = http.url.substr(http.url.find_last_of('/') + 1);
		if(downloadThread.isRunning())
		{
			tmp = makeUpdate(http,Status::Err);
			writeProtocol(tmp);
		}
		else
		{
			tmp = makeUpdate(http, Status::OK);
			writeProtocol(tmp);
			downloadThread.registerEvent(onDownload,0);
			downloadThread.settings(http.url,http.port,"/mnt/extsd/temp",filename);
			downloadThread.run("download-file");
		}
	}else if(data.cmd == Cmd::Reboot)
	{
		tmp = makeReboot();
		writeProtocol(tmp);
		Thread::sleep(2000);
		//同步数据，将缓存数据保存，以防数据丢失
		sync();
		reboot(RB_AUTOBOOT);
	}
	else if(data.cmd == Cmd::ID)
	{
		tmp = makeID();
		writeProtocol(tmp);
	}

	else if(data.cmd == Cmd::Version)
	{
		tmp = makeVersion();
		writeProtocol(tmp);
	}
	else if(data.cmd == Cmd::Heartbeat)
	{
		tmp = makeHeartbeat(Status::OK);
		writeProtocol(tmp);
	}
	else if(data.cmd == Cmd::Login)
	{

	}
	else if(data.cmd == Cmd::Organization)
	{
		parseOrg(data, org);
		if(data.status == Status::Set)
		{
			dev.set_organization(org);
		}
		tmp = makeOrg(Status::OK,dev.get_organization());
		netUser.write(tmp);
	}
	else if(data.cmd == Cmd::Department)
	{
		parseDepartment(data, department);
		if(data.status == Status::Set)
		{
			dev.set_department(department);
		}
		tmp = makeDepartment(Status::OK,dev.get_department());//
		netUser.write(tmp);
	}
	else if(data.cmd == Cmd::DateTime)
	{
		parseDateTime(data);
		if(data.status == Status::Set || data.status == Status::Get)
		{
			tmp = makeDateTime(Status::OK);
			writeProtocol(tmp);
		}
	}


	else if(data.cmd == Cmd::DoorLockControl)
	{
		parseDoorCtr(data, doorState);
		if(data.status == Status::Set)
		{
			door.set_lock_ctr(doorState);
		}
		tmp = makeDoorCtr(Status::OK, door.get_lock_ctr_state());
		netUser.write(tmp);
		LOGD("DoorLockControl 已回复");
	}
	else if(data.cmd == Cmd::DoorState)
	{
		tmp = makeDoorState(Status::OK, door.get_state());
		netUser.write(tmp);
		LOGD("DoorState 已回复");
	}
	else if(data.cmd == Cmd::Plan)
	{
		LOGD("plan:%s",data.data.c_str());
		parsePlan(data, gPlan);

		tmp = makePlan(Status::OK);
		netUser.write(tmp);
	}
	else if(data.cmd == Cmd::CourseInfo)
	{
		parseCourseInfo(data, gCourseInfo);
		save_course(gCourseInfo);
		tmp = makeCourseInfo(Status::OK, gCourseInfo);
		netUser.write(tmp);
	}
	else if(data.cmd == Cmd::Broadcast)
	{
		parseBroadcast(data, tempstr );
		if(data.status == Status::Set)
		{
			gBroadcastMsg = tempstr;
		}
		tmp = makeBroadcast(Status::OK, gBroadcastMsg);
		netUser.write(tmp);

	}
	else if(data.cmd == Cmd::QRCode)
	{
		parseQRCode(data, gQRCode);
		save_qrcode(gQRCode);
		tmp = makeQRCode(Status::OK);
		netUser.write(tmp);
		LOGD("二维码信息已回复");
	}
	else if(data.cmd == Cmd::LocalPassword)
	{
		parseLocalPassword(data, tempstr);
		if(data.status == Status::Set)
		{
			dev.set_pwdLocal(tempstr);
		}
		tmp = makeLocalPassword(Status::OK, dev.get_pwdLocal());
		netUser.write(tmp);
	}
	else if(data.cmd == Cmd::DoorPassword)
	{
		parseDoorPwd(data, tempstr);
		tmp = makeLocalPassword(Status::OK, tempstr);
		netUser.write(tmp);
	}
	else if(data.cmd == Cmd::PersonList)
	{
		parsePersonList(data, gPersonList);
		if(data.status == Status::Set)
		{
			gPerson.update(gPersonList);
		}
		tmp = makePersonList(Status::OK);
		netUser.write(tmp);
	}
	else if(data.cmd == Cmd::Unknown)
	{
		tmp = makeUnknown(Status::OK);
		netUser.write(tmp);
	}
}

void onNetDataServerAck(const NetProtocolData &data)
{
	HttpInfo_t http;
	std::string filename;
	string status;
	if((data.status == Status::Set || data.status == Status::Get) )//不处服务器执行命令
	{
		return ;
	}
	NetProtocolData tmp;
	LOGD("触发网络回调函数：服务器的响应cmd:%s,err:%d",data.cmd.c_str(),data.err);
//	LOGD("接收到的回复：\ncmd:%s\n err:%d,\n stuts:%s,\ndata:%s",data.cmd.c_str(),data.err,data.status.c_str(),data.data.c_str());
	if(data.cmd == Cmd::Login)
	{
		status = parseLogin(data, dev.para);
		LOGD("登录结果：%s",data.data.c_str());
		if(status == Status::OK)
		{
			netUser.login_state_set(true);
			dev.set_organization(dev.para.org);
			dev.set_department(dev.para.department);

			tmp = makeCourseInfo(Status::Get, gCourseInfo);
			netUser.write(tmp);
			tmp = makeQRCode(Status::Get);
			netUser.write(tmp);
			tmp = makePersonList(Status::Get);
			netUser.write(tmp);

		}
	}
	else if(data.cmd == Cmd::Update)
	{
		parseUpdate(data, http);
		filename = http.url.substr(http.url.find_last_of('/') + 1);
		LOGD("路径：%s",http.url.c_str());
		LOGD("文件名：%s",filename.c_str());
		LOGD("端口：%d",http.port);
		LOGD("状态：%d",data.status.c_str());
		if(data.status == Status::OK)
		{
			if(!downloadThread.isRunning())
			{
				downloadThread.registerEvent(onDownload,0);
				downloadThread.settings(http.url,http.port,"/mnt/extsd/temp",filename);
				downloadThread.run("download-file");
				LOGD("启动下载");
			}
			else
			{
				LOGD("有一个正在下载的任务执行中");
			}
		}
	}
	else if(data.cmd == Cmd::Plan)
	{
		LOGD("plan:%s",data.data.c_str());
		parsePlan(data, gPlan);
	}
	else if(data.cmd == Cmd::CourseInfo)
	{
		parseCourseInfo(data, gCourseInfo);
		if(data.status == Status::OK)
		{
			save_course(gCourseInfo);
		}
	}
	else if(data.cmd == Cmd::QRCode)
	{
		parseQRCode(data, gQRCode);
		if(data.status == Status::OK)
		{
			save_qrcode(gQRCode);
		}
	}
	else if(data.cmd == Cmd::PersonList)
	{
		parsePersonList(data, gPersonList);
		if(data.status == Status::OK)
		{

		}
	}
	else
	{
		LOGE("-----未识别的回复--------");
	}



}


