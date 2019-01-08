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

using namespace std;

bool ParseJsonString(char *str);
JsonCmd_t getJsonCMD(string &str);





JsonStatus_t 	ParseCMDDoor2(string &js,doorState_t &door);


FILE *openfile(uint32_t *len);
string get_id(const char *str);








class JsonCmdManager
{
public:
	string makeHeartbeat(JsonStatus_t status);
	JsonStatus_t parseHeartbeat(string &js, string &msg);

	string 			makeDoorCtr(doorState_t &door,JsonStatus_t status);
	JsonStatus_t 	parseDoorCtr(string &js,doorState_t &door);

	string makeDoorPwd(string &pwd,JsonStatus_t status);
	JsonStatus_t parseDoorPwd(string &js,string &msg);

	string makeSyncDateTime(string &msg,JsonStatus_t status);
	JsonStatus_t parseSyncDateTime(string &js,string &msg);

	string makePlan(JsonStatus_t status);
	JsonStatus_t parsePlan(string &js, Plan &plan);


	string makeBroadcast(string &msg,JsonStatus_t status);
	JsonStatus_t parseBroadcast(string &js,string &msg);

	string makeAdSet(AdSet_t &set,JsonStatus_t status);
	JsonStatus_t parseAdSet(string &js,AdSet_t &set);


	string makeAdminPwd(string &pwd,JsonStatus_t status);
	JsonStatus_t parseAdminPwd(string &js,string &adminPwd);
};

extern JsonCmdManager jm;
#endif /* JNI_JSON_TEST_H_ */
