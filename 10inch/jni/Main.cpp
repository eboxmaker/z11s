#include "entry/EasyUIContext.h"
#include "uart/UartContext.h"
#include "manager/ConfigManager.h"
#include <pthread.h>
#include "utils/Log.h"

#include "uart/Uart.h"
#include "termio.h"
#include <iostream>

#include "global.h"
#include "storage/StoragePreferences.h"
#include "json_manager.h"
#include "lib/fileOpt.h"
#include "version.h"
#include "alarm.h"
#include "lib/finger.h"

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */



static void *MainLoop(void *lParam);
static void LoadParament()
{

	dev.load();
    gAdv.load();

    make_dir(PIC_DIR);
    make_dir(QR_DIR);
    make_dir(AD_DIR);


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
	uint16_t value;

	LoadParament();

	//gSocket->setSocketListener(&gSocketListener);
//	finger.getFeatures();
//	sleep(2);
//	if(finger.get_free(1,100,&value) == true)
//		LOGE("free id%d\r\n",value);
//	else
//		LOGE("free id:err\r\n");
//
//	while(1);


	pthread_t threadID ;
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
	ret = gSocket->connect(dev.get_serverIP().c_str(),dev.get_serverPort());
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
	if(	gSocket->triggerTime != -1)
	{
		//LOGO("开启超时检测触发");
		if(time(NULL) - gSocket->triggerTime >= gSocket->trigerTimeout)
		{
			//LOGO("已经触发");
			exeCMD("triggerTimeout");
			gSocket->triggerTime = -1;
		}
	}
}
//心跳轮训
static void heartbeatLoop()
{
	static int counter = 0;

	if(++counter >= dev.get_heartbeatInterval())
	{
		std::string hearbeatMsg;
		hearbeatMsg = jm.makeHeartbeat(StatusSet);
		gSocket->write_(hearbeatMsg);
		counter = 0;
	}
}
#include "include/utils/GpioHelper.h"

static bool test;
static void *MainLoop(void *lParam)
{
    //pthread_mutex_init(&mutex,NULL);


    int len = 0;
	int counter = 0;
	int reconnect_counter = 4;

	reconncet();

	Thread::sleep(1000);




	sPlayer.setPlayerMessageListener(&myAlarm);
	sPlayer.setVolume(10,10);
	while(1)
	{
		if(dev.get_enable())
		{
			//断线检测
			if(!gSocket->connected())
			{
				if(reconnect_counter > 5)
				{
					reconncet();
					reconnect_counter = 0;
				}
				reconnect_counter++;
			}
			//心跳轮训
			heartbeatLoop();
			//服务器响应时间计数循环
			timeoutLoop();
		}
		else
		{

		}

		myAlarm.loop();

		Thread::sleep(1000);

	}

}
#ifdef __cplusplus
}
#endif  /* __cplusplus */

