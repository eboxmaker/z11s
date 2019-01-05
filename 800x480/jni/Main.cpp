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


#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */


static void *MainLoop(void *lParam);
static void LoadParament()
{
    gServerIP = StoragePreferences::getString("gServerIP", "192.168.1.1");
    LOGE("gServerIP %s\n", gServerIP.c_str());
    gServerPort = StoragePreferences::getInt("gServerPort", 6000);
    LOGE("gServerPort %d\n", gServerPort);
    gAdminPwd = StoragePreferences::getString("gAdminPwd", "123456");
    LOGE("gServerPort %s\n", gAdminPwd.c_str());

//    StoragePreferences::remove("gDisplayAdAfterTime");
//    StoragePreferences::remove("gSwitchAdTime");
//    StoragePreferences::remove("gAdEnable");
    gDisplayAdAfterTime = StoragePreferences::getInt("gDisplayAdAfterTime", 20);
    gSwitchAdTime = StoragePreferences::getInt("gSwitchAdTime", 5);
    gAdEnable = StoragePreferences::getInt("gAdEnable", 1);

    LOGE("gDisplayAdAfterTime %D\n", gDisplayAdAfterTime);
    LOGE("gSwitchAdTime %D\n",gSwitchAdTime);
    LOGE("gAdEnable %D\n",gAdEnable);
    make_dir(QR_DIR);
    make_dir(AD_DIR);
//	stringList list = get_all_ad_full_name();
//	adTotal = 0;
//	 for(stringList::iterator it = list.begin() ; it !=list.end(); it++)
//	 {
//		 list[0]
//		picPath[pic_total] = *it;
//		LOGE("文件全名:%s",picPath[pic_total].c_str());
//		adTotal++;
//	 }

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

	while(1)
	{
		Thread::sleep(1000);

		if(updateServerLiveState() == false)
		{
			gSocket->disconnect();
			ret = gSocket->connect(gServerIP.c_str(),gServerPort);
			if(ret == true)
			{
				setServerLiveState(true);
				LOGE("连接服务器成功!\n");
			}
			else
			{
				gSocket->disconnect();
				LOGE("连接服务器失败 !\n");

			}
		}

		const char *ptr;
		ptr = EASYUICONTEXT->currentAppName();
		cAppName = ptr;
		timeNow = time(NULL);
		if(cAppName == "keyboardActivity")
		{
			if(timeNow - gKeyboardLastActionTime > gDisplayAdAfterTime)
			{
				EASYUICONTEXT->openActivity("AdvertisementActivity");
				LOGE("切换成功");
			}
			else
			{
				LOGE("TIME:%D",timeNow - gKeyboardLastActionTime);
			}
		}
		else
		{
			//LOGE("xxxTIME:%D",timeNow - gKeyboardLastActionTime);

		}
	}

}
#ifdef __cplusplus
}
#endif  /* __cplusplus */

