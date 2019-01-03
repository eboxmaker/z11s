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



#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */


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
char buf[4096] = "hello world\n";
char rbuf[409600] ;
static void *MainLoop(void *lParam)
{
    //pthread_mutex_init(&mutex,NULL);


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
	std::string fileFullName;
	std::string filename;
	std::string msg;

	ret = gSocket->connect(gServerIP.c_str(),gServerPort);
	gSocket->setHeartbeat(5,"123",sizeof("123"));
	if(ret == true)
	{
		LOGE("socket thread connect OK!\n");
	}
	else
	{
		gSocket->disconnect();
	}
//	while(1);
	while(1)
	{
		//sleep(1);
		//LOGE("r加锁");
		len = gSocket->read_json(rbuf,409600);
		//LOGE("r解锁");
		if(len > 0)
		{
			JsonCmd_t cmd = getJsonCMD(rbuf);
			switch(cmd)
			{
			case PicFile:
				LOGE("接受到图片!\n");
				SaveFile(rbuf,FILE_DIR);

				filename = GetFileName(rbuf);
				fileFullName = FILE_DIR;
				fileFullName += filename;
				LOGE("文件名:%s!\n",fileFullName.c_str());
				memset(rbuf,0,sizeof(rbuf));
				break;
			case Door1:
				msg = ParseCMDDoor1(rbuf);
				memset(rbuf,0,sizeof(rbuf));
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
			memset(rbuf,0,sizeof(rbuf));

		}
	}

}
#ifdef __cplusplus
}
#endif  /* __cplusplus */

