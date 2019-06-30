/*
 * json_test.h
 *
 *  Created on: 2018年12月4日
 *      Author: Administrator
 */

#ifndef JNI_JSON_TEST_H_
#define JNI_JSON_TEST_H_
#include "json/json.h"
#include <string.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

#include "aes/myaes256.h"
#include "plan.h"
#include "ad.h"
#include "global.h"

using namespace std;


bool ParseJsonString(char *str);
JsonCmd_t getJsonCMD(string &str);



class JsonCmdManager
{

public:
	JsonCmdManager();
	~JsonCmdManager();
	string getID();


	string pack(string& data);
	string pack(char* data);
	bool unPack(string& package,string& msg);
	bool unPack(char* package,string& msg);

public:
//	JsonStatus_t parseStatus(string &js);


	string 			makeHeartbeat(JsonStatus_t status);
	JsonStatus_t	parseHeartbeat(string &js, string &msg);

	string 			makeSetHeartbeat(int interval,JsonStatus_t status);
	JsonStatus_t	parseSetHeartbeat(string &js,int &interval);

	string 			makeOrgName(string &org,JsonStatus_t status);
	JsonStatus_t	parseOrgName(string &js,string &org);

	string 			makeDevName(string &name,JsonStatus_t status);
	JsonStatus_t	parseDevName(string &js,string &name);

	string 			makeDevID(string &id,JsonStatus_t status);
	JsonStatus_t	parseDevID(string &js);

	string			makeConfirm(Device &pDev,JsonConfirmStatus_t status);
	JsonStatus_t	parseConfirm(string &js,DevicePara_t &para,string &timeString);

	string 			makeSyncDateTime(string &msg,JsonStatus_t status);
	JsonStatus_t 	parseSyncDateTime(string &js,string &msg);

	string 			makeLocalPwd(string &pwd,JsonStatus_t status);
	JsonStatus_t	parseLocalPwd(string &js,string &pwd);

	string 			makeDoorPwd(string &pwd,JsonStatus_t status);
	JsonStatus_t 	parseDoorPwd(string &js,string &pwd);

	string 			makeFingerKey(PersonInfo_t &key,JsonStatus_t status);
	JsonStatus_t 	parseFingerKey(string &js);

	string 			makeDoorCtr(DoorLockState_t &door,JsonStatus_t status);
	JsonStatus_t 	parseDoorCtr(string &js,DoorLockState_t &door);

	string 			makeDoorState(DoorState_t &door,JsonStatus_t status);
	JsonStatus_t 	parseDoorState(string &js);


	string 			makeCourseInfo(CourseInfo_t &info,JsonStatus_t status);
	JsonStatus_t	parseCourseInfo(string &js, CourseInfo_t &info);

	string 			makePlan(JsonStatus_t status);
	JsonStatus_t	parsePlan(string &js, Plan &plan);


	string  		makeBroadcast(string &msg,JsonStatus_t status);
	JsonStatus_t 	parseBroadcast(string &js,string &msg);





	string 			makeQRCodeAck(string &fullname,JsonStatus_t status);
	JsonStatus_t 	parseFile(string str, char* directory, string &fullName,string &dataout);

	string  		makeDeleteFile(string &fileName,JsonStatus_t status);
	JsonStatus_t 	parseDeleteFile(string js, char* directory, string &fileName,string &fullName);


	string 			makeAdAdd(string &fullname,JsonStatus_t status);
	string 			makeAdRead(Advertisement &ad, JsonStatus_t status);
	string 			makeAdDelet(string fileName,JsonStatus_t status);//回复服务器删除某个广告执行结果
	string 			makeAdClear(JsonStatus_t status);

	JsonStatus_t 	parseAdAdd(string js,string &fileName);//不需要
	JsonStatus_t 	parseAdRead(string js);//不需要
	JsonStatus_t 	parseAdDelet(string js, string &fileName);
	JsonStatus_t 	parseAdClear(string &js);

	string 			makeAdSet(Advertisement &set,JsonStatus_t status);
	JsonStatus_t 	parseAdSet(string &js,Advertisement &set);

	string 			makePerson(PersonTrans_t &person,JsonStatus_t status);
	JsonStatus_t 	parsePerson(string &js,PersonTrans_t &person);

	string 			makePersonGetByLevel(int level, int num, JsonStatus_t status);
	JsonStatus_t 	parsePersonGetByLevel(string &js, int *level, int *num);

	string 			makePersonRead(PersonTrans_t &person,JsonStatus_t status);
	JsonStatus_t 	parsePersonRead(string &js,PersonTrans_t &person);

	string 			makeFingerGet(PersonTrans_t &person,JsonStatus_t status);
	JsonStatus_t 	parseFingerGet(string &js,PersonTrans_t &person);

	string 			makeFingerSet(PersonTrans_t &person,JsonStatus_t status);
	JsonStatus_t 	parseFingerSet(string &js,PersonTrans_t &person);

	string 			makeVersion(JsonStatus_t status);
	JsonStatus_t 	parseVersion(string &js);

	string 			makeUpdate(HttpInfo_t &info,JsonStatus_t status);
	JsonStatus_t 	parseUpdate(string &js,HttpInfo_t &info);

	string 			makeReboot(JsonStatus_t status);
	JsonStatus_t 	parseReboot(string &js);

	AesEncryptor *aes;

};

extern JsonCmdManager jm;
#endif /* JNI_JSON_TEST_H_ */
