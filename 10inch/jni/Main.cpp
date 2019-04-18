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

#include "uart/ProtocolSender.h"
#include "uart/Uart.h"
#include "termio.h"

#include <iostream>

#include "sqlite/database.h"
#include "version.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */



static void *MainLoop(void *lParam);
static void LoadParament()
{
	dev.enable = true;
    dev.id = jm.getID();
    dev.version = VERSION;

    dev.serverIP = StoragePreferences::getString("dev.serverIP", "192.168.1.1");
    dev.serverPort = StoragePreferences::getInt("dev.serverPort", 6000);
    dev.pwdLocal = StoragePreferences::getString("dev.pwdLocal", "123456");

    dev.organization = StoragePreferences::getString("dev.organization", "none");
    dev.name = StoragePreferences::getString("dev.name","none");

    dev.heartbeatInterval = StoragePreferences::getInt("dev.heartbeatInterval", 5);






    make_dir(PIC_DIR);
    make_dir(QR_DIR);
    make_dir(AD_DIR);


    //从系统变量存储区更新广告使能设置
    gAdv.idleTime = StoragePreferences::getInt("gAdv.idleTime", 20);
    gAdv.enable = StoragePreferences::getBool("gAdv.enable", true);
    //从数据库中更新广告信息

	 dbAdv.recodeResult("1.jpg", 5);
	 dbAdv.recodeResult("1.jpg", 6);
	 dbAdv.recodeResult("1.jpg", 7);
	 gAdv.logDBList();
	 gAdv.logFileList();


    //system("rm /mnt/extsd/update.img");

}
void onEasyUIInit(EasyUIContext *pContext) {
	// 初始化时打开串口
	UARTCONTEXT->openUart(CONFIGMANAGER->getUartName().c_str(), B19200);
	uart2.openUart("/dev/ttyS0",B19200);
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


	return "mainActivity";
}
static void reconncet()
{
	bool ret = false;
	int counter = 0;

	dev.confirmState = false;
	LOGO("正在连接。。。");
	gSocket->disconnect();
	ret = gSocket->connect(dev.serverIP.c_str(),dev.serverPort);
	if(ret == true)
	{
//		LOGO("连接服务器成功!\n");
		LOGO("正在注册。。。");
		string js = jm.makeConfirm(dev, StatusReqDev2Ser);
		gSocket->write_(js);

		while(dev.confirmState == false )
		{
			if(counter >= 10)
			{
				LOGE("注册超时，重新注册！");
				break;
			}
			counter++;
			Thread::sleep(1000);
		}
		if(	dev.confirmState == false)
		{
			LOGE("断开服务器!\n");
			gSocket->disconnect();
		}
		else
		{
			LOGO("注册成功!!!\n");
			gSocket->conncetState = true;
		}


	}
	else
	{
		gSocket->disconnect();
		LOGE("连接服务器失败 !\n");
		gSocket->conncetState = false;

	}
}
static void timeoutLoop()
{
	if(	gSocket->trigerTime != -1)
	{
		//LOGO("开启超时检测触发");
		if(time(NULL) - gSocket->trigerTime >= gSocket->trigerTimeout)
		{
			//LOGO("已经触发");
			exeCMD("trigerTimeout");
			gSocket->trigerTime = -1;
		}
	}
}
//心跳轮训
static void heartbeatLoop()
{
	static int counter = 0;
	if(dev.heartbeatInterval < 3)
		dev.heartbeatInterval = 3;
	if(++counter >= dev.heartbeatInterval)
	{
		std::string hearbeatMsg;
		hearbeatMsg = jm.makeHeartbeat(StatusSet);
		gSocket->write_(hearbeatMsg);
		counter = 0;
	}
}
static void *MainLoop(void *lParam)
{
    //pthread_mutex_init(&mutex,NULL);


    bool ret;
    int len;
	int counter = 0;


	Thread::sleep(1000);


	while(1)
	{
		if(dev.enable)
		{
			//断线检测
			if(!gSocket->connected())
			{
				reconncet();
			}
			//心跳轮训
			heartbeatLoop();
			//服务器响应时间计数循环
			timeoutLoop();
		}
		else
		{

		}



		Thread::sleep(1000);

	}

}
#ifdef __cplusplus
}
#endif  /* __cplusplus */

