#include "entry/EasyUIContext.h"
#include "uart/UartContext.h"
#include "manager/ConfigManager.h"
#include <pthread.h>
#include "utils/Log.h"
#include "globalVar.h"
#include "include/utils/GpioHelper.h"

#include "check_nic.h"

#include "udp.h"
#include "storage/StoragePreferences.h"
#include "json_test.h"
#include "packageFile.h"
#include "readdir.h"
#include "netinet/tcp.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */


static void *MainLoop(void *lParam);
static void LoadParament()
{
    gServerIP = StoragePreferences::getString("gServerIP", "192.168.1.1");
    gServerPort = StoragePreferences::getInt("gServerPort", 6000);
    gAdminPwd = StoragePreferences::getString("gAdminPwd", "123456");

    LOGE("gServerIP %s\n", gServerIP.c_str());
    LOGE("gServerPort %d\n", gServerPort);
    LOGE("gServerPort %s\n", gAdminPwd.c_str());

//    StoragePreferences::remove("gDisplayAdAfterTime");
//    StoragePreferences::remove("gSwitchAdTime");
//    StoragePreferences::remove("gAdEnable");
    gAdSet.displayTime = StoragePreferences::getInt("gAdSet.displayTime", 20);
    gAdSet.switchTime = StoragePreferences::getInt("gAdSet.switchTime", 5);
    gAdSet.enable = StoragePreferences::getBool("gAdSet.enable", true);

    LOGE("gDisplayAdAfterTime %D\n", gAdSet.displayTime);
    LOGE("gSwitchAdTime %D\n",gAdSet.switchTime);
    LOGE("gAdEnable %D\n",gAdSet.enable);
    make_dir(QR_DIR);
    make_dir(AD_DIR);
}
void onEasyUIInit(EasyUIContext *pContext) {
	// 初始化时打开串口
	UARTCONTEXT->openUart(CONFIGMANAGER->getUartName().c_str(), CONFIGMANAGER->getUartBaudRate());
}

void onEasyUIDeinit(EasyUIContext *pContext) {
	UARTCONTEXT->closeUart();
}

const char* onStartupApp(EasyUIContext *pContext) {

	LoadParament();

	//gSocket->setSocketListener(&gSocketListener);

	pthread_t threadID = 1;
	pthread_attr_t attr; 		// 线程属性
	pthread_attr_init(&attr);  	// 初始化线程属性
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);      // 设置线程属性
	int ret = pthread_create(&threadID, &attr, MainLoop, (void *)0);
	pthread_attr_destroy(&attr);
	if (ret || !threadID) {
		LOGD("create socket thread error\n");
	}
	else
	{

		LOGD("create socket thread ok\n");
	}


	return "keyboardActivity";
}

static void *MainLoop(void *lParam)
{
    //pthread_mutex_init(&mutex,NULL);

	string cAppName;
	long long timeNow;
    bool ret;
    int len;
//	msg.ptr = buf;
//	msg.len = sizeof(buf);
//	rmsg.ptr = rbuf;
//	rmsg.len = sizeof(rbuf);
//	memset(&msg.remote,0,sizeof(msg.remote));
//	//数据初始化--清零
//	msg.remote.sin_family=AF_INET; //设置为IP通信
//	msg.remote.sin_addr.s_addr=inet_addr("192.168.1.101");//服务器IP地址
//	msg.remote.sin_port=htons(8000); //服务器端口号


	gSocket->setHeartbeat(5);
	if(gSocket->connected() == false)
	{
		gSocket->disconnect();
		ret = gSocket->connect(gServerIP.c_str(),gServerPort);
		if(ret == true)
		{
			LOGE("连接服务器成功!\n");
		}
		else
		{
			gSocket->disconnect();
			LOGE("连接服务器失败 !\n");

		}
	}

	while(1)
	{
		Thread::sleep(1000);
//
//		if(check_nic("eth0") == -1)
//		{
//			LOGE("网线断开");
//			gSocket->disconnect();
//
//		}
//
//		struct tcp_info info;
//		int len = sizeof(info);
//		getsockopt(gSocket->mClientSocket,IPPROTO_TCP,TCP_INFO,&info,(socklen_t*)&len);
//		if(info.tcpi_state == TCP_ESTABLISHED && gSocket->mClientSocket > 0)
//		{
//			LOGE("已连接（%d)",gSocket->mClientSocket);
//		}
//		else
//		{
//			LOGE("未连接");
//			gSocket->disconnect();
//			ret = gSocket->connect(gServerIP.c_str(),gServerPort);
//			if(ret == true)
//			{
//				setServerLiveState(true);
//				LOGE("连接服务器成功!\n");
//			}
//			else
//			{
//				gSocket->disconnect();
//				LOGE("连接服务器失败 !\n");
//
//			}
//		}

		if(gAdSet.enable)
		{
			const char *ptr;
			ptr = EASYUICONTEXT->currentAppName();
			cAppName = ptr;
			timeNow = time(NULL);
			if(cAppName == "keyboardActivity")
			{
				if(timeNow - gKeyboardLastActionTime > gAdSet.displayTime)
				{
					EASYUICONTEXT->openActivity("AdvertisementActivity");
					LOGE("切换成功");
				}
				else
				{
					//LOGE("TIME:%D",timeNow - gKeyboardLastActionTime);
				}
			}
			else
			{
				//LOGE("xxxTIME:%D",timeNow - gKeyboardLastActionTime);

			}
		}

	}

}
#ifdef __cplusplus
}
#endif  /* __cplusplus */

