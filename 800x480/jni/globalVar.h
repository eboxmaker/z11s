/*
 * globalVar.h
 *
 *  Created on: 2018年12月26日
 *      Author: shentq
 */

#ifndef JNI_LIB_GLOBALVAR_H_
#define JNI_LIB_GLOBALVAR_H_
#include <string.h>
#include <fstream>
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "lib/SocketClient.h"
#include "include/utils/GpioHelper.h"
#include "utils/Log.h"
#include <vector>
using namespace std;

#define QR_DIR		"/mnt/extsd/qr/"
#define AD_DIR		"/mnt/extsd/ad/"
typedef enum
{
	Lock,
	UnLock
}doorState_t;


typedef enum
{
	CMDHeartbeat,
	CMDSetHeartbeat,
	CMDConfirm,
	CMDAdminPwd,
	CMDDoorPwd,
	CMDDoorCtr,
	CMDQR,
	CMDAdvertisement,
	CMDSyncDateTime,
}JsonCmd_t;

typedef std::vector<std::string> stringList;

typedef void (*myNotify_t)(JsonCmd_t,string &);

extern string gServerIP ;
extern int gServerPort ;
extern struct sockaddr_in gServerAddr;
extern SocketClient* gSocket;

extern string gAdminPwd;//需要存储
extern string gDoorPassword;
extern unsigned long long gLastHelloTime;
extern bool gDoorPwdState ;

extern long long gKeyboardLastActionTime;

extern int gAdEnable;//需要存储
extern int gDisplayAdAfterTime;//需要存储
extern int gSwitchAdTime;//需要存储

extern stringList gAdPicList;

extern doorState_t gDoorState;



//class MySocketListener : public SocketClient::ISocketListener
//{
//	public:
//		virtual void notify(int what, int status, const char *msg);
//};
//static MySocketListener gSocketListener;
//
//回调函数声明区域
extern myNotify_t keyboardCallback;
extern myNotify_t AdvertisementCallback;
extern myNotify_t networkTestCallback;
extern myNotify_t settingsCallback;

void exeCMD(string &JsonString);
bool updateServerLiveState();
bool setServerLiveState(bool state);
bool getServerLiveState();

#endif /* JNI_LIB_GLOBALVAR_H_ */
