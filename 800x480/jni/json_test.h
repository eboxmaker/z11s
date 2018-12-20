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

typedef enum
{
	PicFile = 0,
	test
}JsonCmd_t;

JsonCmd_t getJsonCMD(const char * str);

FILE *openfile(uint32_t *len);
std::string get_id(const char *str);




#endif /* JNI_JSON_TEST_H_ */
