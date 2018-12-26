/*
 * globalVar.cpp
 *
 *  Created on: 2018年12月26日
 *      Author: shentq
 */

#include "globalVar.h"



lockState_t gLockState = UnLock;

string gServerIP ;
string gServerPort ;
struct sockaddr_in gServerAddr;
SocketClient* gSocket= new SocketClient();

void MySocketListener::notify(int what, int status, const char *msg){
	string msg_string = msg;
	if(status == SocketClient::E_SOCKET_STATUS_RECV_OK){
		LOGE("FILE RECV OK!");
		LOGE("what:%d---msg:%s",what,msg);
	}
	else
	{
		return ;
	}

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
			gLockState = UnLock;
			GpioHelper::output(GPIO_PIN_B_02, 1);
			LOGD("Lock:1\n");
		}
		else
		{
			gLockState = Lock;
			GpioHelper::output(GPIO_PIN_B_02, 0);
			LOGD("Lock:0\n");
		}
//			mEditTextMSGPtr->setText(msg);
		break;

	}
}
