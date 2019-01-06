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

string cutOneJsonString(RingBufInt8 *msg);
bool ParseJsonString(char *str);
JsonCmd_t getJsonCMD(string &str);
string ParseCMDDoor1(string &str);
string ParseCMDDoor2(char *str);
string MakeCMDDoorPassword(char *str);
FILE *openfile(uint32_t *len);
string get_id(const char *str);
string MakeCMDHeatbeat();
string ParseCMDDoorPwdStatus(string &str);
string MakeCMDSyncDateTime(string &str);
string ParseCMDSyncDateTime(string &str);
string MakeCMDPlan();
stringListList ParseCMDPlan(string &str);
string ParseCMDBroadcast(string &str);
string MakeCMDBroadcastAck(string &str);



#endif /* JNI_JSON_TEST_H_ */
