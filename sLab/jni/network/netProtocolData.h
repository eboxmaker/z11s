/*
 * netProtocol.h
 *
 *  Created on: 2020年4月12日
 *      Author: Administrator
 */

#ifndef NETWORK_NETPROTOCOLDATA_H_
#define NETWORK_NETPROTOCOLDATA_H_
#include <vector>
#include <string>
#include "system/mutex.h"

#define AESMD5_ENABLE 1

class Status
{
public:
	const static std::string Set;
	const static std::string Get;
	const static std::string OK;
	const static std::string Err;
};
class Cmd
{
public:
	Cmd();
	std::string str;

	const static std::string Unknown;
	const static std::string Update;
	const static std::string Reboot;
	const static std::string ID;
	const static std::string Version;
	const static std::string Heartbeat;
	const static std::string Login;
	const static std::string Organization;
	const static std::string Department;// = 8,//包含department
	const static std::string DateTime;// = 9,
	const static std::string DoorLockControl;//,
	const static std::string DoorState;//,
	const static std::string CourseInfo;//课程信息
	const static std::string Plan;//计划（课程表）
	const static std::string Broadcast;//
	const static std::string QRCode;//
	const static std::string LocalPassword;//
	const static std::string DoorPassword;//
	const static std::string PersonList;//
	const static std::string PersonGet;//
	const static std::string PersonUpdate;//
};


typedef struct {
	std::string   	cmd;   //modbus命令
	std::string  	status;   //modbus命令
	int 		err;      //错误信息
	int 		retryTimes;
	time_t 		time;
	std::string data; //modbus数据指针

} NetProtocolData;

typedef  std::vector<NetProtocolData> NetProtocolDataList;

void pack(NetProtocolData &msg);
bool unPack(std::string& package,std::string& js);

#endif /* JNI_NETWORK_NETPROTOCOL_H_ */
