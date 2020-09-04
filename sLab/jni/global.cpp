/*
 * globalVar.cpp
 *
 *  Created on: 2018年12月26日
 *      Author: shentq
 */
#include "global.h"
#include <sys/reboot.h>
#include "utils/Log.h"
#include "device.h"

long gKeyboardLastActionTime = 0;
CourseInfo_t gCourseInfo;
Picture_t 	gQRCode;

string gBroadcastMsg;

void save_course(CourseInfo_t &course)
{
	string filename;
	ioutil::Writer fw;
	filename = PIC_DIR + course.picture.name;
//    string cmd = "rm " + filename;
//    system(cmd.c_str());
	fw.Open(filename.c_str(), 0);
	fw.Write(course.picture.data.c_str(), course.picture.dataLength);
	fw.Close();
}
void save_qrcode(Picture_t &pic)
{
	string filename;
	ioutil::Writer fw;
	filename = QR_DIR + pic.name;
	fw.Open(filename.c_str(), 0);
	fw.Write(pic.data.c_str(), pic.dataLength);
	fw.Close();
	LOGD("保存二维码文件成功,文件名:%s",filename.c_str());
}


