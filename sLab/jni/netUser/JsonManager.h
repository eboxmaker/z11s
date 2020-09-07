/*
 * JsonManager.h
 *
 *  Created on: 2020年4月12日
 *      Author: Administrator
 */

#ifndef JNI_JSONMANAGER_H_
#define JNI_JSONMANAGER_H_

#include"json/json.h"
#include "network/netProtocolData.h"
#include "type.h"
#include "device.h"
#include "door.h"
#include "plan.h"
#include "person.h"

NetProtocolData makeUpdate(HttpInfo_t &info, string status);
string parseUpdate(const NetProtocolData &data,HttpInfo_t &info);

NetProtocolData makeReboot();

NetProtocolData makeID();

NetProtocolData makeVersion();

NetProtocolData makeHeartbeat(string status);
string parseHeartbeat(const NetProtocolData &data,string &id);

NetProtocolData makeLogin(string status);
string parseLogin(const NetProtocolData &data,DevicePara_t &info);

NetProtocolData makeOrg(string status,string &org);
string parseOrg(const NetProtocolData &data,string &org);

NetProtocolData makeDepartment(string status,string &department);
string parseDepartment(const NetProtocolData &data,string &department);

NetProtocolData makeDateTime(string status);
string parseDateTime(const NetProtocolData &data);



NetProtocolData makeDoorCtr(string status,DoorLockState_t door);
string 	parseDoorCtr(const NetProtocolData &data,DoorLockState_t &door);
NetProtocolData makeDoorState(string status,DoorState_t door);


NetProtocolData	makeCourseInfo(string status,CourseInfo_t info,int retrytimes = 0);
string	parseCourseInfo(const NetProtocolData data, CourseInfo_t &info);

NetProtocolData makePlan(string status);
string	parsePlan(const NetProtocolData &data, Plan &plan);

NetProtocolData	makeBroadcast(string status,string &broadcast_msg);
string 	parseBroadcast(const NetProtocolData &data,string &broadcast_msg);

NetProtocolData	makeQRCode(string status,int retrytimes = 0);
string	parseQRCode(const NetProtocolData data, Picture_t &pic);


NetProtocolData makeLocalPassword(string status,string &password);
string parseLocalPassword(const NetProtocolData &data,string &password);

NetProtocolData makeDoorPwd(string status,string &pwd);
string 	parseDoorPwd(const NetProtocolData &data,string &pwd);

NetProtocolData makePersonList(string status,int retrytimes = 0);
string parsePersonList(const NetProtocolData data,PersonInfoList_t &personList);

NetProtocolData makePersonGet(string status,string id);
string parsePersonGet(const NetProtocolData &data,PersonInfo_t &person);

NetProtocolData makePersonUpdate(string status,PersonInfo_t &person);
string parsePersonUpdate(const NetProtocolData &data);


NetProtocolData makeUnknown(string status);

#endif /* JNI_JSONMANAGER_H_ */
