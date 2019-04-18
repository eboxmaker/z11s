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

	CMDAdPic,//CMDAdvertisement,
	CMDDelAdPic,//CMDAdvertisement,
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
