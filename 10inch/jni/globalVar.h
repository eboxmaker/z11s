/*
 * globalVar.h
 *
 *  Created on: 2018年12月26日
 *      Author: shentq
 */

#ifndef JNI_LIB_GLOBALVAR_H_
#define JNI_LIB_GLOBALVAR_H_
#include "objectType.h"

#include "lib/SocketClient.h"



using namespace std;

#define HOME_DIR	"/mnt/extsd/"
#define QR_DIR		"/mnt/extsd/qr/"
#define AD_DIR		"/mnt/extsd/ad/"
#define AD_DB		"/mnt/extsd/advertisment.db"
#define PIC_DIR		"/mnt/extsd/picture/"




typedef void (*myNotify_t)(JsonCmd_t,JsonStatus_t, string &);
typedef void (*dlNotify_t)(string &msg);



extern Device_t dev;
extern SocketClient* gSocket;

extern long gLastHelloTime;
extern  long gKeyboardLastActionTime;


extern doorState_t gDoorState;
extern string gBroadcastMsg;
extern Person_t gPerson;
extern CourseInfo_t gCourseInfo;


//回调函数声明区域
extern myNotify_t keyboardCallback;
extern myNotify_t AdvertisementCallback;
extern myNotify_t networkTestCallback;
extern myNotify_t settingsCallback;
extern myNotify_t PersonCallback;

void exeCMD(char *ptr);
void exeCMD(string &JsonString);


#endif /* JNI_LIB_GLOBALVAR_H_ */
