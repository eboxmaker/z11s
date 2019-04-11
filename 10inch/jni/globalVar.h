/*
 * globalVar.h
 *
 *  Created on: 2018年12月26日
 *      Author: shentq
 */

#ifndef JNI_LIB_GLOBALVAR_H_
#define JNI_LIB_GLOBALVAR_H_
#include "objectType.h"
#include <netinet/in.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "lib/SocketClient.h"
#include "utils/Log.h"

#include <sys/sysinfo.h>

#include "sqlite/database.h"

#include "uart/Uart.h"

#include "finger.h"
#include "ad.h"

using namespace std;

#define HOME_DIR	"/mnt/extsd/"
#define QR_DIR		"/mnt/extsd/qr/"
#define AD_DIR		"/mnt/extsd/ad/"
#define PIC_DIR		"/mnt/extsd/picture/"
#define SU_DIR		"/mnt/extsd/super/"


extern Database dbAdv;



typedef enum
{
	StatusReqDev2Ser = 0,
	StatusParaSer2Dev ,
	StatusAckDev2Ser,
	StatusOKSer2Dev,
	StatusErrSer2Dev,
}JsonConfirmStatus_t;

typedef struct {
	string organization;
	string name;
	string id;

	string pwdLocal;
	string pwdDoor;

	string serverIP;
	int serverPort;

	int	   heartbeatInterval;

	struct sysinfo systemInfo;

	bool confirmState;
	bool enable;
}Device_t;

typedef enum
{
	CMDHeartbeat,
	CMDSetHeartbeat,
	CMDOrgName,
	CMDDevName,
	CMDDevID,
	CMDConfirm,
	CMDSyncDateTime,
	CMDAdminPwd,
	CMDDoorPwd,
	CMDDoorCtr,
	CMDCourseInfo,
	CMDPlan,
	CMDBroadcast,

	CMDQRCode,
	CMDDelQRCode,

	CMDAdPic,//CMDAdvertisement,
	CMDDelAdPic,//CMDAdvertisement,
	CMDAdSet,

	CMDSuperPic,

	CMDPerson,


	CMDVersion,
	CMDUpdate,
	CMDReboot,

    CMDErr,

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
	string name;
	int size;
	string md5;
}StorageFileInfo_t;

typedef struct
{
	string url;
	int port;
}DownloadInfo_t;

typedef struct
{
	string teacher;
	string class_;
	string courser;
}PlanRow_t;

typedef struct
{
	string name;
	long datalen;
	string data;
}Picture_t;

typedef struct
{
	string name;
	string class_;
	string num;
	string course;
	Picture_t picture;
}CourseInfo_t;
typedef struct
{
	string name;
	string id;
	int	   level;
	stringList fingers;
	Picture_t picture;

}Person_t;
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
	void clear()
	{
		_size = 0;
	}

	PlanRow_t row[100];

private:
	int _maxSize;
	int _size;
};

typedef std::vector< Person_t> PersonList_t;

typedef void (*myNotify_t)(JsonCmd_t,JsonStatus_t, string &);
typedef void (*dlNotify_t)(string &msg);



extern Device_t dev;

extern SocketClient* gSocket;

extern long gLastHelloTime;
extern  long gKeyboardLastActionTime;

extern doorState_t gDoorState;

extern PersonList_t gUserAdmin;
extern Plan gPlan;
extern string gBroadcastMsg;
extern Person_t gPerson;
extern CourseInfo_t gInfo;
extern StorageFileInfo_t gFileInfo;
extern DownloadInfo_t gDownloadInfo;
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
extern myNotify_t PersonCallback;

void exeCMD(char *ptr);
void exeCMD(string &JsonString);


#endif /* JNI_LIB_GLOBALVAR_H_ */
