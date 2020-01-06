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
typedef std::vector<int> IntList;
typedef std::vector<uint16_t> uint16List;


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
	long dataLength;
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





typedef union
{
	unsigned long long value;
	unsigned char bytes[8];
}XdataULong_t;





//普通命令传输状态枚举类型
typedef enum
{
	StatusSet = 0,
	StatusGet ,
	StatusOK,
	StatusErr
}JsonStatus_t;

//注册过程传输状态枚举类型


//命令列表
typedef enum
{
	CMDUpdate,//更新终端系统
	CMDReboot,//重启终端
	CMDVersion,//查询终端的版本
	CMDDevID,//设备ID
	CMDRegister,//设备认证

	CMDHeartbeat,//心跳
	CMDSetHeartbeat,//心跳间隔时间 s
	CMDOrgName,//组织名称
	CMDDevName,//设备名称

	CMDSyncDateTime,//同步时间
	CMDLocalPassword,//本地密码

	CMDFingerKey,//指纹密码
	CMDDoorPassword,//动态开门密码
	CMDDoorLockControl,//门控制命令
	CMDDoorState,//门状态

	CMDCourseInfo,//课程信息
	CMDPlan,//计划（课程表）
	CMDBroadcast,//广播

	CMDQRCode,//二维码
	CMDDelQRCode,//删除二维码

	CMDAdAdd,//CMDAdvertisement,
	CMDAdRead,//CMDAdvertisement,
	CMDAdDel,//CMDAdvertisement,
	CMDAdClear,//清空广告,
	CMDAdSet,


	CMDPersonAdd,//开机时服务器向终端发送的人员列表,上课前向设备发送开门的教师
	CMDPersonDel,//删除某几个人，服务器发送一个id 列比，本地删除这些人
	CMDPersonByLevel,//

	CMDFingerGet,
	CMDFingerSet,



    CMDErr,
    CMDTimeout = 255,

}JsonCmd_t;

std::string jsoncmd_to_str(JsonCmd_t cmd);
std::string jsoncmdstatus_to_str(JsonStatus_t cmd);
typedef void (*myNotify_t)(JsonCmd_t,JsonStatus_t, string &);
typedef void (*dlNotify_t)(string &msg);

#endif /* JNI_OBJECTTYPE_H_ */
