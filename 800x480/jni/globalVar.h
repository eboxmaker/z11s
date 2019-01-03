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

using namespace std;

extern Mutex mutex ;
extern std::string gServerIP ;
extern int gServerPort ;
extern struct sockaddr_in gServerAddr;
extern SocketClient* gSocket;
extern std::string gAdminPassword;
extern std::string gDoorPassword;

typedef enum
{
	Lock,
	UnLock
}doorState_t;
extern doorState_t gDoorState;



class MySocketListener : public SocketClient::ISocketListener
{
	public:
		virtual void notify(int what, int status, const char *msg);
};
static MySocketListener gSocketListener;

#endif /* JNI_LIB_GLOBALVAR_H_ */
