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


extern std::string gServerIP ;
extern std::string gServerPort ;
extern struct sockaddr_in gServerAddr;
extern SocketClient* gSocket;

typedef enum
{
	UnLock,
	Lock
}lockState_t;
extern lockState_t gLockState;



class MySocketListener : public SocketClient::ISocketListener
{
	public:
		virtual void notify(int what, int status, const char *msg);
};
static MySocketListener gSocketListener;

#endif /* JNI_LIB_GLOBALVAR_H_ */
