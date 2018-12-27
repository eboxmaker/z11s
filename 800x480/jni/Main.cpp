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

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

Udp *udp = NULL;

static void *MainLoop(void *lParam);
static void LoadParament()
{
    gServerIP = StoragePreferences::getString("gServerIP", "192.168.1.1");
    LOGD("gServerIP %s\n", gServerIP.c_str());
    gServerPort = StoragePreferences::getInt("gServerPort", 6000);
    LOGD("gServerPort %d\n", gServerPort);

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
	gSocket->start();
	gSocket->setSocketListener(&gSocketListener);

	udp = new Udp();
	udp->start(1245);
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
UDPMessage msg;
UDPMessage rmsg;
char buf[4096] = "hello world\n";
char rbuf[4096] ;
static void *MainLoop(void *lParam)
{
//	msg.ptr = buf;
//	msg.len = sizeof(buf);
//	rmsg.ptr = rbuf;
//	rmsg.len = sizeof(rbuf);
//	memset(&msg.remote,0,sizeof(msg.remote));
//	//数据初始化--清零
//	msg.remote.sin_family=AF_INET; //设置为IP通信
//	msg.remote.sin_addr.s_addr=inet_addr("192.168.1.101");//服务器IP地址
//	msg.remote.sin_port=htons(8000); //服务器端口号



	while(1)
	{
//		udp->send(&msg);
//		if(!gSocket->connected()){
//			gSocket->start();
//		}
//		if(check_nic("eth0") == -1)
//		{
//			gSocket->stop();
//		}
//		else
//		{
//
//			if(!gSocket->connected()){
//				gSocket->start();
//			}
//		}
//		if(udp->recv(&rmsg)>0)
//		{
//			LOGE("%s:%d{%s}",udp->parseIP(&rmsg).c_str(),udp->parsePort(&rmsg),rbuf);
//		}

		usleep(5000);
	}

}
#ifdef __cplusplus
}
#endif  /* __cplusplus */

