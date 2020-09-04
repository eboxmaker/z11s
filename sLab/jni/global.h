/*
 * globalVar.h
 *
 *  Created on: 2018年12月26日
 *      Author: shentq
 */

#ifndef JNI_LIB_GLOBALVAR_H_
#define JNI_LIB_GLOBALVAR_H_
#include "type.h"
#include "lib/ioutil.h"

using namespace std;



//60s后自动进入keyboard页面
//#define GO_HOME_TIME 60*1000
extern CourseInfo_t gCourseInfo;
extern string 		gBroadcastMsg;
extern Picture_t 	gQRCode;

void save_course(CourseInfo_t &course);
void save_qrcode(Picture_t &pic);

#endif /* JNI_LIB_GLOBALVAR_H_ */
