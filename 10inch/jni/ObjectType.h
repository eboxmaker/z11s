/*
 * ObjectType.h
 *
 *  Created on: 2019年3月7日
 *      Author: shentq
 */

#ifndef JNI_OBJECTTYPE_H_
#define JNI_OBJECTTYPE_H_

#include <fstream>
#include <vector>

typedef std::vector<std::string> stringList;

using namespace std;

typedef struct {
	string organization;
	string name;
	string id;
	string version;

	string pwdLocal;
	string pwdDoor;

	string serverIP;
	int serverPort;

	int	   heartbeatInterval;


	bool confirmState;
	bool enable;
}Device_t;

typedef struct
{
	string url;
	int port;
}HttpInfo_t;



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
//	string time_start;
//	string time_end;
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


typedef union
{
	unsigned long long value;
	unsigned char bytes[8];
}XdataULong_t;

typedef enum
{
	Lock,
	UnLock
}doorState_t;

typedef enum
{
	StatusSet = 0,
	StatusRead ,
	StatusOK,
	StatusErr
}JsonStatus_t;

typedef enum
{
	StatusReqDev2Ser = 0,
	StatusParaSer2Dev ,
	StatusAckDev2Ser,
	StatusOKSer2Dev,
	StatusErrSer2Dev,
}JsonConfirmStatus_t;

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

	CMDAdAdd,//CMDAdvertisement,
	CMDAdRead,//CMDAdvertisement,
	CMDAdDel,//CMDAdvertisement,
	CMDAdClear,//清空广告,
	CMDAdSet,

	CMDSuperPic,

	CMDPerson,


	CMDVersion,
	CMDUpdate,
	CMDReboot,

    CMDErr,

}JsonCmd_t;
#endif /* JNI_OBJECTTYPE_H_ */
