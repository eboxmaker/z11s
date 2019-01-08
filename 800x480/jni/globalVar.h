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

typedef std::vector<std::string> stringList;
typedef std::vector< std::vector<std::string> > stringListList;

typedef enum
{
	Lock,
	UnLock
}doorState_t;

typedef struct
{
	bool enable;
	int displayTime;
	int switchTime;
	stringList list;
}AdSet_t;
extern AdSet_t gAdSet;

typedef enum
{
	CMDHeartbeat,
	CMDSetHeartbeat,
	CMDConfirmDevID,
	CMDAdminPwd,
	CMDDoorPwd,
	CMDDoorCtr,
	CMDQR,
	CMDAdPic,//CMDAdvertisement,
	CMDAdSet,
	CMDSyncDateTime,
	CMDPlan,
	CMDBroadcast,
	CMDSuperPic,
}JsonCmd_t;
typedef enum
{
	StatusSet = 0,
	StatusRead ,
	StatusOK,
	StatusErr
}JsonStatus_t;

typedef struct
{
	string teacher;
	int	   level;
	string pwd;
}Person_t;

typedef struct
{
	string teacher;
	string class_;
	string courser;
}PlanRow_t;



class Plan
{
public:
	Plan() :
		_maxSize(100),
		_size(0){
	}
	int size()	{return _size;}
	int maxSize(){return _maxSize;}
	bool add(PlanRow_t &_row)
	{
		if(_size < _maxSize)
		{
			row[_size].teacher = _row.teacher;
			row[_size].class_ = _row.class_;
			row[_size].courser = _row.courser;
			_size++;
		}
	}

	PlanRow_t row[100];

private:
	int _maxSize;
	int _size;
};

typedef std::vector< Person_t> PersonList_t;

typedef void (*myNotify_t)(JsonCmd_t,JsonStatus_t, string &);

extern string gServerIP ;
extern int gServerPort ;
extern struct sockaddr_in gServerAddr;
extern SocketClient* gSocket;

extern string gAdminPwd;//需要存储
extern string gDoorPassword;
extern unsigned long long gLastHelloTime;
extern bool gDoorPwdState ;

extern long long gKeyboardLastActionTime;

extern doorState_t gDoorState;
extern PersonList_t gUserAdmin;
extern Plan gPlan;


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

void exeCMD(char *ptr);
void exeCMD(string &JsonString);


#endif /* JNI_LIB_GLOBALVAR_H_ */
