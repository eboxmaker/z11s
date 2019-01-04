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
bool gServerLiveState = false;

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


void exeCMD(string *JsonString)
{
	std::string fileFullName;
	std::string filename;
	std::string msg;

	int counter =0;
	bool ret;

	ret = ParseJsonString(JsonString->c_str());
	if(ret == true)
	{
		JsonCmd_t cmd = getJsonCMD(JsonString->c_str());
		LOGE("CMD :%d",cmd);
		switch(cmd)
		{
		case CMDHeartbeat:
			gLastHelloTime = time(NULL);
			LOGE("服务器响应");
			break;
		case CMDQR:
			LOGE("接受到二维码!\n");
			SaveFile(JsonString->c_str(),QR_DIR);
			filename = GetFileName(JsonString->c_str());
			fileFullName = QR_DIR;
			fileFullName += filename;
			//LOGE("文件名:%s!\n",fileFullName.c_str());
			if(keyboardCallback != NULL)
				keyboardCallback(CMDQR,fileFullName);
			if(AdvertisementCallback != NULL)
				AdvertisementCallback(CMDQR,fileFullName);
			break;
		case CMDAdvertisement:
			LOGE("接受到图片!\n");
			SaveFile(JsonString->c_str(),AD_DIR);
			filename = GetFileName(JsonString->c_str());
			fileFullName = AD_DIR;
			fileFullName += filename;
			//LOGE("文件名:%s!\n",fileFullName.c_str());
			if(AdvertisementCallback != NULL)
			{
				AdvertisementCallback(CMDAdvertisement,fileFullName);
			}
			break;
		case CMDDoorCtr:
			msg = ParseCMDDoor1(JsonString->c_str());
			if(msg == "0")
			{
				gDoorState = Lock;
				GpioHelper::output(GPIO_PIN_B_02, 1);
				LOGD("door1:Lock\n");
			}
			else
			{
				gDoorState = UnLock;
				GpioHelper::output(GPIO_PIN_B_02, 0);
				LOGD("door1:UnLock\n");
			}
			if(AdvertisementCallback != NULL)
				AdvertisementCallback(CMDDoorCtr,msg);
			break;
		case CMDDoorPwd:
			msg = ParseCMDDoorPwdStatus(JsonString->c_str());

			LOGE("msg:%s\n",msg.c_str());

			if(msg == "0")
			{
				LOGD("door 密码错误\n");
			}
			else
			{
				LOGD("door 密码正确\n");
			}
			if(keyboardCallback != NULL)
				keyboardCallback(CMDDoorPwd,msg);
			break;
		default:
			break;
		}
	}
}

bool updateServerLiveState()
{
	if(time(NULL) - gLastHelloTime > 10)
	{
		gServerLiveState = false;
		LOGE("服务器离线");
	}
	else
	{
		gServerLiveState = true;
	}
	return gServerLiveState;
}
bool setServerLiveState(bool state)
{
	gLastHelloTime = time(NULL);
	gServerLiveState = state;
	return gServerLiveState;

}
