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
using namespace std;
typedef enum
{
	PicFile = 0,
	Door1,
	Door2,
}JsonCmd_t;
bool ParseJsonString(char *str);
JsonCmd_t getJsonCMD(const char * str);
string ParseCMDDoor1(char *str);
string ParseCMDDoor2(char *str);
string MakeCMDDoorPassword(char *str);
FILE *openfile(uint32_t *len);
string get_id(const char *str);




#endif /* JNI_JSON_TEST_H_ */
