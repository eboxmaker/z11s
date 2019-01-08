/*
 * globalVar.cpp
 *
 *  Created on: 2018年12月26日
 *      Author: shentq
 */

#include "globalVar.h"
#include "json_test.h"
#include "packageFile.h"
Mutex mutex;

doorState_t gDoorState = Lock;
bool gDoorPwdState = false;

string gServerIP ;
int gServerPort ;
struct sockaddr_in gServerAddr;
SocketClient* gSocket= new SocketClient();
string gAdminPwd = "123456";
string gDoorPassword = "123456";

unsigned long long gLastHelloTime = 0;

long long gKeyboardLastActionTime = 0;

AdSet_t gAdSet;
PersonList_t gUserAdmin;
Plan gPlan;
//void MySocketListener::notify(int what, int status, const char *msg){
//	string msg_string = msg;
////	if(status == SocketClient::E_SOCKET_STATUS_RECV_OK){
////		LOGE("FILE RECV OK!");
////		LOGE("what:%d---msg:%s",what,msg);
////	}
////	else
////	{
////		return ;
////	}
//
//	switch(what)
//	{
//	case 0:
//		//mButton1Ptr->setText("");
//		//bHavePic = true;
//		//mButton1Ptr->setBackgroundPic(msg);
//		break;
//	case 1:
//		if(msg_string == "0")
//		{
//			gDoorState = Lock;
//			GpioHelper::output(GPIO_PIN_B_02, 1);
//			LOGD("g Lock:1\n");
//		}
//		else
//		{
//			gDoorState = UnLock;
//			GpioHelper::output(GPIO_PIN_B_02, 0);
//			LOGD("g Lock:0\n");
//		}
//	case 2:
//		LOGD("g close\n");
//		//mBtnConnectServerPtr->setText("连接服务器");
////			mEditTextMSGPtr->setText(msg);
//		break;
//
//	}
//}
//
myNotify_t keyboardCallback;
myNotify_t AdvertisementCallback;
myNotify_t networkTestCallback;
myNotify_t settingsCallback;

void exeCMD(char *ptr)
{
	string js;
	js = ptr;
	exeCMD(js);
}
void exeCMD(string &js)
{
	std::string msg;
	string ack ;

	int counter =0;
	bool ret;
	int status = -1;
	msg = "";
	if(js == "trigerTimeout")
	{

		if(networkTestCallback != NULL)
			networkTestCallback(255,StatusErr,js);
		if(keyboardCallback != NULL)
			keyboardCallback(255,StatusErr,js);
		if(settingsCallback != NULL)
			settingsCallback(255,StatusErr,js);
		if(AdvertisementCallback != NULL)
			AdvertisementCallback(255,StatusErr,js);
		return;
	}
	ret = ParseJsonString(js.c_str());
	if(ret == true)
	{
		JsonCmd_t cmd = getJsonCMD(js);
		switch(cmd)
		{
		case CMDHeartbeat:
			status = jm.parseHeartbeat(js,msg);
			gLastHelloTime = time(NULL);
			break;
		case CMDSetHeartbeat:

			break;
		case CMDAdminPwd:
			status = jm.parseAdminPwd(js,gAdminPwd);
			if(status == StatusSet)
			{
				ack = jm.makeAdminPwd(gAdminPwd,StatusOK);
				gSocket->write_(ack);
			}
			LOGE("status:%d",status);
			break;
		case CMDQR:
			LOGE("接收到二维码!\n");
			ret = SaveFile(js.c_str(),QR_DIR);
			msg = QR_DIR;
			msg += GetFileName(js.c_str());
			if(ret == true)
				status = 0;
			break;
		case CMDAdPic:
			LOGE("接收到图片!\n");
			ret = SaveFile(js.c_str(),AD_DIR);
			msg = AD_DIR;
			msg += GetFileName(js.c_str());
			if(ret == true)
				status = 0;
			break;
		case CMDDoorCtr:
			status = jm.parseDoorCtr(js,gDoorState);
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
			break;
		case CMDDoorPwd:
			status = jm.parseDoorPwd(js, msg);
			if(status == StatusSet)
			{
				//设置RTC，
				//回复
			}
			break;
		case CMDSyncDateTime:
			status = jm.parseSyncDateTime(js, msg);
			if(status == StatusSet)
			{
				//设置RTC，
			}
			else if(status == StatusRead)
			{

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
				//设置RTC，
			}
			else if(status == StatusRead)
			{

			}
			ack = jm.makeBroadcast(msg, StatusOK);
			gSocket->write_(ack);
			break;
		case CMDAdSet:
			status = jm.parseAdSet(js,gAdSet);
			if(status == StatusSet)
			{
				ack = jm.makeAdSet(gAdSet, StatusOK);
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

	}
}

