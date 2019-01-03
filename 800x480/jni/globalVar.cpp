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

string gServerIP ;
int gServerPort ;
struct sockaddr_in gServerAddr;
SocketClient* gSocket= new SocketClient();
string gAdminPassword = "123456";
string gDoorPassword = "123456";

void MySocketListener::notify(int what, int status, const char *msg){
	string msg_string = msg;
//	if(status == SocketClient::E_SOCKET_STATUS_RECV_OK){
//		LOGE("FILE RECV OK!");
//		LOGE("what:%d---msg:%s",what,msg);
//	}
//	else
//	{
//		return ;
//	}

	switch(what)
	{
	case 0:
		//mButton1Ptr->setText("");
		//bHavePic = true;
		//mButton1Ptr->setBackgroundPic(msg);
		break;
	case 1:
		if(msg_string == "0")
		{
			gDoorState = Lock;
			GpioHelper::output(GPIO_PIN_B_02, 1);
			LOGD("g Lock:1\n");
		}
		else
		{
			gDoorState = UnLock;
			GpioHelper::output(GPIO_PIN_B_02, 0);
			LOGD("g Lock:0\n");
		}
	case 2:
		LOGD("g close\n");
		//mBtnConnectServerPtr->setText("连接服务器");
//			mEditTextMSGPtr->setText(msg);
		break;

	}
}




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
		switch(cmd)
		{
		case PicFile:
			LOGE("接受到图片!\n");
			SaveFile(JsonString->c_str(),FILE_DIR);
			filename = GetFileName(JsonString->c_str());
			fileFullName = FILE_DIR;
			fileFullName += filename;
			LOGE("文件名:%s!\n",fileFullName.c_str());
			break;
		case Door1:
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
			break;
		default:
			break;
		}
	}


}
