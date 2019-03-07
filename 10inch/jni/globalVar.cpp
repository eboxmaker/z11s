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

Database dbAdv("/mnt/extsd/test.db");
doorState_t gDoorState = Lock;
string gDoorPwd;
Person_t gPerson;
string gServerIP ;
int gServerPort ;
struct sockaddr_in gServerAddr;
SocketClient* gSocket= new SocketClient();
string gAdminPwd = "123456";
string gDoorPassword = "123456";


long gKeyboardLastActionTime = 0;
string gDevID;
string gDevName;
int gHeartbeatInterval;

PersonList_t gUserAdmin;
Plan gPlan;
string gBroadcastMsg;

struct sysinfo gSystemInfo;
float gMemUsage;

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

	int counter =0;
	bool ret;
	int status = -1;
	msg = "";
	string js;
	if(msg == "trigerTimeout")
	{

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
	ret = jm.unPack(package, js);;
	if(ret == true)
	{

		JsonCmd_t cmd = getJsonCMD(js);
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
				if(tempInterval > 10)tempInterval= 10;
				if(tempInterval < 3)tempInterval = 3;
				gHeartbeatInterval = tempInterval;
				gSocket->interval = gHeartbeatInterval;
				StoragePreferences::putInt("gHeartbeatInterval", gHeartbeatInterval);

			}
			ack = jm.makeSetHeartbeat(gHeartbeatInterval, StatusOK);
			gSocket->write_(ack);
			break;
		case CMDConfirm:
			status = jm.parseConfirm(js);
			if(status == StatusSet || status == StatusRead)
			{
				//LOGE("回复:%s:%s",gDevID.c_str(),gDevName.c_str());
				ack = jm.makeConfirm(gDevID,gDevName, StatusOK);
				gSocket->write_(ack);
			}
			break;

		case CMDDevID:
			status = jm.parseDevID(js);
			if(status == StatusSet || status == StatusRead)
			{
				//LOGE("回复:%s",gDevID.c_str());
				ack = jm.makeDevID(gDevID, StatusOK);
				gSocket->write_(ack);
			}
			break;
		case CMDAdminPwd:
			status = jm.parseAdminPwd(js,gAdminPwd);
			if(status == StatusSet)
			{
			    StoragePreferences::putString("gAdminPwd", gAdminPwd.c_str());
				ack = jm.makeAdminPwd(gAdminPwd,StatusOK);
				gSocket->write_(ack);
			}
			else if(status == StatusRead)
			{
				ack = jm.makeAdminPwd(gAdminPwd,StatusOK);
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
				tempDoorState = GpioHelper::input(GPIO_PIN_B_02);
			}
			//应该触发一个定时器，两秒之后返回该值
			ack = jm.makeDoorCtr(tempDoorState, StatusOK);
			gSocket->write_(ack);
			break;
		case CMDDoorPwd:
			status = jm.parseDoorPwd(js, msg);
			if(status == StatusSet)
			{
				gDoorPwd = msg;
			}
			ack = jm.makeDoorPwd(gDoorPwd, StatusOK);
			gSocket->write_(ack);
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

		case CMDDevName:
			status = jm.parseDevName(js,gDevName);
			if(status == StatusSet)
			{
			    StoragePreferences::putString("gDevName", gDevName);

				ack = jm.makeDevName(gDevName, StatusOK);
				gSocket->write_(ack);
			}
			else if(status == StatusRead)
			{
				ack = jm.makeDevName(gDevName, StatusOK);
				gSocket->write_(ack);
			}
			LOGE("status：%d",status);
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

