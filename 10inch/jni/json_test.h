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
#include "ringbuf.h"
#include "globalVar.h"
#include "aes/myaes256.h"

using namespace std;
bool CheckJsonPackage(string& package,string& msg);
bool ParseJsonString(char *str);
JsonCmd_t getJsonCMD(string &str);





JsonStatus_t 	ParseCMDDoor2(string &js,doorState_t &door);


FILE *openfile(uint32_t *len);








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
	string makeHeartbeat(JsonStatus_t status);
	JsonStatus_t parseHeartbeat(string &js, string &msg);

	string makeSetHeartbeat(int interval,JsonStatus_t status);
	JsonStatus_t parseSetHeartbeat(string &js,int &interval);

	string makeOrgName(string &org,JsonStatus_t status);
	JsonStatus_t parseOrgName(string &js,string &org);

	string makeDevName(string &name,JsonStatus_t status);
	JsonStatus_t parseDevName(string &js,string &name);

	string makeDevID(string &id,JsonStatus_t status);
	JsonStatus_t parseDevID(string &js);

	string makeConfirm(Device_t &dev_,JsonConfirmStatus_t status);
	JsonStatus_t parseConfirm(string &js,Device_t &dev_,string &timeString);

	string makeSyncDateTime(string &msg,JsonStatus_t status);
	JsonStatus_t parseSyncDateTime(string &js,string &msg);

	string makeAdminPwd(string &pwd,JsonStatus_t status);
	JsonStatus_t parseAdminPwd(string &js,string &adminPwd);

	string makeDoorPwd(string &pwd,JsonStatus_t status);
	JsonStatus_t parseDoorPwd(string &js,string &pwd);

	string 			makeDoorCtr(doorState_t &door,JsonStatus_t status);
	JsonStatus_t 	parseDoorCtr(string &js,doorState_t &door);


	string makeCourseInfo(CourseInfo_t &info,JsonStatus_t status);
	JsonStatus_t parseCourseInfo(string &js, CourseInfo_t &info);

	string makePlan(JsonStatus_t status);
	JsonStatus_t parsePlan(string &js, Plan &plan);


	string makeBroadcast(string &msg,JsonStatus_t status);
	JsonStatus_t parseBroadcast(string &js,string &msg);





	string makeQRCodeAck(string &fullname,JsonStatus_t status);
	string makePicAck(string &fullname,JsonStatus_t status);
	JsonStatus_t parseFile(string str, char* directory, string &fullName,string &dataout);

	string makeDeleteFile(string &fullName,JsonStatus_t status);
	JsonStatus_t parseDeleteFile(string js, char* directory, string &fileName,string &fullName);

	string makeAdSet(Advertisement &set,JsonStatus_t status);
	JsonStatus_t parseAdSet(string &js,Advertisement &set);

	string makePerson(Person_t &person,JsonStatus_t status);
	JsonStatus_t parsePerson(string &js,Person_t &person);

	string makeVersion(JsonStatus_t status);
	JsonStatus_t parseVersion(string &js);

	string makeUpdate(JsonStatus_t status);
	JsonStatus_t parseUpdate(string &js);

	string makeReboot(JsonStatus_t status);
	JsonStatus_t parseReboot(string &js);

	AesEncryptor *aes;

};

extern JsonCmdManager jm;
#endif /* JNI_JSON_TEST_H_ */
