/*
 * globalVar.cpp
 *
 *  Created on: 2018年12月26日
 *      Author: shentq
 */

#include "globalVar.h"
#include "json_test.h"
#include "packageFile.h"
#include "storage/StoragePreferences.h"
#include "utils/TimeHelper.h"
#include "readdir.h"
#include <sys/reboot.h>
#include "httpDownload.h"

Database dbAdv("/mnt/extsd/test.db");
doorState_t gDoorState = Lock;

SocketClient* gSocket= new SocketClient();


long gKeyboardLastActionTime = 0;

Person_t gPerson;
PersonList_t gUserAdmin;
Plan gPlan;
CourseInfo_t gInfo;
StorageFileInfo_t gFileInfo;
DownloadInfo_t gDownloadInfo;

string gBroadcastMsg;



Device_t dev;

myNotify_t keyboardCallback;
myNotify_t AdvertisementCallback;
myNotify_t networkTestCallback;
myNotify_t settingsCallback;
myNotify_t PersonCallback;

void exeCMD(char *ptr)
{
	string js;
	js = ptr;
	exeCMD(js);
}
void exeCMD(string &package)
{
	string fileName = "";
	string msg;
	string dataout;
	string ack ;
	Device_t tempDev;


	int counter =0;
	bool ret = false;
	int status = -1;
	int cStatus = -1;
	msg = "";
	char msgBuf[50];
	string js;
	if(package == "trigerTimeout")
	{
		//LOGE("发出超时通知");
		if(networkTestCallback != NULL)
			networkTestCallback(255,StatusErr,msg);
		if(keyboardCallback != NULL)
			keyboardCallback(255,StatusErr,msg);
		if(settingsCallback != NULL)
			settingsCallback(255,StatusErr,msg);
		if(AdvertisementCallback != NULL)
			AdvertisementCallback(255,StatusErr,msg);
		if(PersonCallback != NULL)
			PersonCallback(255,StatusErr,msg);
		return;
	}
	else
	{
		ret = jm.unPack(package, js);;
	}
	if(ret == true)
	{

		JsonCmd_t cmd = getJsonCMD(js);
		//LOGE("CMD:%d",cmd);
		switch(cmd)
		{
		case CMDHeartbeat:
			status = jm.parseHeartbeat(js,msg);
			if(status == StatusSet || status == StatusRead)
			{
				ack = jm.makeHeartbeat(StatusOK);
				gSocket->write_(ack);
			}

			break;
		case CMDSetHeartbeat:
			int tempInterval;
			status = jm.parseSetHeartbeat(js,tempInterval);
			if(status == StatusSet)
			{
				if(tempInterval > 100)tempInterval= 100;
				if(tempInterval < 3)tempInterval = 3;
				dev.heartbeatInterval = tempInterval;
				StoragePreferences::putInt("dev.heartbeatInterval", dev.heartbeatInterval);
				ack = jm.makeSetHeartbeat(dev.heartbeatInterval, StatusOK);
				gSocket->write_(ack);
			}
			if(status == StatusRead)
			{
				ack = jm.makeSetHeartbeat(dev.heartbeatInterval, StatusOK);
				gSocket->write_(ack);
			}
			break;
		case CMDConfirm:
			cStatus = jm.parseConfirm(js,tempDev,msg);
			//LOGE("%s",js.c_str());
			if(cStatus == StatusParaSer2Dev)
			{
				if(tempDev.id == dev.id)
				{
					//LOGE("服务器匹配设备正确！");
					//更新四个参数
					TimeHelper::setDateTime(msg.c_str());
					StoragePreferences::putInt("dev.heartbeatInterval", tempDev.heartbeatInterval);
					StoragePreferences::putString("dev.organization", tempDev.organization);
					StoragePreferences::putString("dev.name", tempDev.name);


					dev.organization = StoragePreferences::getString("dev.organization","none");
					dev.name = StoragePreferences::getString("dev.name","none");
				    dev.heartbeatInterval = StoragePreferences::getInt("dev.heartbeatInterval", 5);

				    ack = jm.makeConfirm(dev,StatusAckDev2Ser );
					gSocket->write_(ack);
					//LOGE("回复:%s:%s",dev.organization.c_str(),dev.name.c_str());

				}
				else
				{
					dev.confirmState = StatusErrSer2Dev;
					LOGE("服务器匹配设备ID错误！");

				}

			}
			else if(cStatus == StatusOKSer2Dev)
			{
				dev.confirmState = true;
			}
			else
			{

			}
			break;
		case CMDOrgName:
			status = jm.parseOrgName(js,dev.organization);
			if(status == StatusSet)
			{
			    StoragePreferences::putString("dev.organization", dev.organization);

				ack = jm.makeOrgName(dev.organization, StatusOK);
				gSocket->write_(ack);
			}
			else if(status == StatusRead)
			{
				ack = jm.makeOrgName(dev.organization, StatusOK);
				gSocket->write_(ack);
			}
			break;
		case CMDDevName:
			status = jm.parseDevName(js,dev.name);
			if(status == StatusSet)
			{
			    StoragePreferences::putString("dev.name", dev.name);

				ack = jm.makeDevName(dev.name, StatusOK);
				gSocket->write_(ack);
			}
			else if(status == StatusRead)
			{
				ack = jm.makeDevName(dev.name, StatusOK);
				gSocket->write_(ack);
			}
			break;
		case CMDDevID:
			status = jm.parseDevID(js);
			if(status == StatusSet || status == StatusRead)
			{
				//LOGE("回复:%s",gDevID.c_str());
				ack = jm.makeDevID(dev.id, StatusOK);
				gSocket->write_(ack);
			}
			break;
		case CMDAdminPwd:
			status = jm.parseAdminPwd(js,dev.pwdLocal);
			if(status == StatusSet)
			{
			    StoragePreferences::putString("dev.pwdLocal", dev.pwdLocal.c_str());
				ack = jm.makeAdminPwd(dev.pwdLocal,StatusOK);
				gSocket->write_(ack);
			}
			else if(status == StatusRead)
			{
				ack = jm.makeAdminPwd(dev.pwdLocal,StatusOK);
				gSocket->write_(ack);
			}
			break;
		case CMDQRCode:
			status = jm.parseFile(js,QR_DIR,msg,dataout);
			ack = jm.makeQRCodeAck(msg,StatusErr);
			if(status == StatusSet || status == StatusRead)
			{
				if(creat_file(msg,dataout.c_str(),dataout.size()))
					ack = jm.makeQRCodeAck(msg,StatusOK);
			}
			gSocket->write_(ack);
			LOGE("接收到二维码!%d:%s\n",status,msg.c_str());
			break;
		case CMDDelQRCode:
			status = jm.parseDeleteFile(js,QR_DIR,fileName,msg);
			if(status == StatusSet || status == StatusRead)
			{
				rm_file(msg);
				ack = jm.makeDeleteFile(msg,StatusOK);
				gSocket->write_(ack);
			}
			else if(status == StatusErr)
			{
				ack = jm.makeQRCodeAck(msg,StatusErr);
				gSocket->write_(ack);
			}
			break;
		case CMDAdPic:
			status = jm.parseFile(js,AD_DIR,msg,dataout);

			ack = jm.makeQRCodeAck(msg,StatusErr);
			if(status == StatusSet || status == StatusRead)
			{
				if(gAdv.add(js)  && creat_file(msg,dataout.c_str(),dataout.size()) )
				{
					ack = jm.makePicAck(msg,StatusOK);
				}
			}
			gSocket->write_(ack);
			LOGE("接收到图片!%d:%s\n",status,msg.c_str());
			break;
		case CMDDelAdPic:
			status = jm.parseDeleteFile(js,AD_DIR,fileName,msg);
			if(status == StatusSet || status == StatusRead)
			{
				gAdv.remove(fileName);
				ack = jm.makeDeleteFile(msg,StatusOK);
				gSocket->write_(ack);
			}
			else if(status == StatusErr)
			{
				ack = jm.makeQRCodeAck(msg,StatusErr);
				gSocket->write_(ack);
			}
			break;
		case CMDAdSet:
			status = jm.parseAdSet(js,gAdv);
			if(status == StatusSet)
			{
			    StoragePreferences::putBool("gAdv.enable", gAdv.enable);
			    StoragePreferences::putInt("gAdv.idleTime", gAdv.idleTime);

				ack = jm.makeAdSet(gAdv, StatusOK);
				gSocket->write_(ack);
			}
			break;

		case CMDSuperPic:
//			status = jm.parseFile(js,AD_DIR,msg);
//			if(status == StatusSet || status == StatusRead)
//			{
//				ack = jm.makePicAck(msg,StatusOK);
//				gSocket->write_(ack);
//			}
//			updateAdFileList(gAdSet.list);
//			LOGE("接收到图片!%d:%s\n",status,msg.c_str());
			break;
		case CMDDoorCtr:
			doorState_t tempDoorState;
			status = jm.parseDoorCtr(js,tempDoorState);
			if(status == StatusSet )
			{
				gDoorState = tempDoorState;
				if(gDoorState == UnLock)
				{
					msg = "unlock";
					GpioHelper::output(GPIO_PIN_B_02, UnLock);
				}
				else
				{
					msg = "lock";
					GpioHelper::output(GPIO_PIN_B_02, Lock);
				}
			}else if(status == StatusRead)
			{
				tempDoorState = GpioHelper::input(GPIO_PIN_B_03);
				LOGD("door：%d",tempDoorState);
			}
			//应该触发一个定时器，两秒之后返回该值
			ack = jm.makeDoorCtr(tempDoorState, StatusOK);
			gSocket->write_(ack);
			break;
		case CMDDoorPwd:
			status = jm.parseDoorPwd(js, msg);
			//下位机不存储开门密码
//			if(status == StatusSet)
//			{
//				gDoorPwd = msg;
//			}
//			ack = jm.makeDoorPwd(gDoorPwd, StatusOK);
//			gSocket->write_(ack);
			break;
		case CMDSyncDateTime:
			status = jm.parseSyncDateTime(js, msg);
			if(status == StatusSet)
			{
				TimeHelper::setDateTime(msg.c_str());
				ack = jm.makeSyncDateTime(msg, StatusOK);
				gSocket->write_(ack);
			}
			else if(status == StatusRead)
			{

			}
			else if(status == StatusOK)
			{
				TimeHelper::setDateTime(msg.c_str());
			}
			//回复

			break;

		case CMDCourseInfo:
			LOGE("CMD:CMDCourseInfo");
			status = jm.parseCourseInfo(js, gInfo);
			if(status == StatusSet)
			{
				msg = PIC_DIR + gInfo.picture.name;
				if(creat_file(msg,gInfo.picture.data.c_str(),gInfo.picture.data.size()))
				{
					ack = jm.makeCourseInfo(gInfo,StatusOK);
					gSocket->write_(ack);
				}
			}
			LOGE("CMD:CMDCourseInfo:s=%d",status);
			LOGE("%s，%s",gInfo.name.c_str(),gInfo.course.c_str());

			break;
		case CMDPlan:
			status = jm.parsePlan(js, gPlan);
			if(status == StatusRead)
			{

			}
			break;
		case CMDBroadcast:
			status = jm.parseBroadcast(js, msg);
			if(status == StatusSet)
			{
				gBroadcastMsg = msg;
			}
			else if(status == StatusRead)
			{

			}
			ack = jm.makeBroadcast(gBroadcastMsg, StatusOK);
			gSocket->write_(ack);
			break;


		case CMDPerson:
			status = jm.parsePerson(js, gPerson);
			if(status == StatusOK)
			{
				msg = "read or set ok";
			}
			else if(status == StatusSet || status == StatusRead)
			{
				ack = jm.makePerson(gPerson, StatusOK);
				gSocket->write_(ack);
			}
			break;
		case CMDVersion:
			status = jm.parseVersion(js);
			if(status == StatusRead)
			{
				ack = jm.makeVersion(StatusOK);
				gSocket->write_(ack);
			}
			break;
		case CMDUpdate:
			status = jm.parseUpdate(js,gDownloadInfo);
			if(status == StatusSet)
			{
			    string filename = gDownloadInfo.url.substr(gDownloadInfo.url.find_last_of('/') + 1);
			    LOGE("文件名：%s",filename.c_str());
				if(downloadThread.isRunning())
				{
					ack = jm.makeUpdate(gDownloadInfo,StatusErr);
					gSocket->write_(ack);
				}
				else
				{
					ack = jm.makeUpdate(gDownloadInfo,StatusOK);
					gSocket->write_(ack);
					downloadThread.settings(gDownloadInfo.url,gDownloadInfo.port,"/mnt/extsd/temp",filename);
				    downloadThread.run("download-update");
				}
				LOGE("FILE:%s,%d,%s",gFileInfo.name.c_str(),gFileInfo.size,gFileInfo.md5.c_str());
			}
			else if( status == StatusOK)
			{
			    string filename = gDownloadInfo.url.substr(gDownloadInfo.url.find_last_of('/') + 1);
				//downloadThread.settings(gDownloadInfo.url,gDownloadInfo.port,"/mnt/extsd/temp",filename.c_str());
				downloadThread.settings(gDownloadInfo.url,gDownloadInfo.port,"/mnt/extsd/temp",filename);
			    downloadThread.run("download-update");

				LOGE("FILE:%s,%d,%s",gFileInfo.name.c_str(),gFileInfo.size,gFileInfo.md5.c_str());
			}
			break;
		case CMDReboot:
			status = jm.parseReboot(js);
			if(status == StatusSet)
			{
				ack = jm.makeReboot(StatusOK);
				gSocket->write_(ack);
				Thread::sleep(2000);
			    reboot(RB_AUTOBOOT);
			}
			break;
		default:
			break;
		}
		if(networkTestCallback != NULL)
			networkTestCallback(cmd,status,msg);
		if(keyboardCallback != NULL)
			keyboardCallback(cmd,status,msg);
		if(settingsCallback != NULL)
			settingsCallback(cmd,status,msg);
		if(AdvertisementCallback != NULL)
			AdvertisementCallback(cmd,status,msg);
		if(PersonCallback != NULL)
			PersonCallback(cmd,status,msg);

	}
}

