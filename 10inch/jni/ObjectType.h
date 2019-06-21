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


//设备信息结构体


//系统更新结网址构体
typedef struct
{
	string url;
	int port;
}HttpInfo_t;



//用户存储json传递过来的图片。
typedef struct
{
	string name;
	long datalen;
	string data;
}Picture_t;

//主界面课程信息
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

//录入指纹时传递的信息
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





//普通命令传输状态枚举类型
typedef enum
{
	StatusSet = 0,
	StatusRead ,
	StatusOK,
	StatusErr
}JsonStatus_t;

//注册过程传输状态枚举类型
typedef enum
{
	StatusReqDev2Ser = 0,
	StatusParaSer2Dev ,
	StatusAckDev2Ser,
	StatusOKSer2Dev,
	StatusErrSer2Dev,
}JsonConfirmStatus_t;

//命令列表
typedef enum
{
	CMDHeartbeat,
	CMDSetHeartbeat,
	CMDOrgName,
	CMDDevName,
	CMDDevID,
	CMDConfirm,
	CMDSyncDateTime,
	CMDLocalPwd,
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


typedef void (*myNotify_t)(JsonCmd_t,JsonStatus_t, string &);
typedef void (*dlNotify_t)(string &msg);

#endif /* JNI_OBJECTTYPE_H_ */
