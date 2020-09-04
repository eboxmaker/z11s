/*
 * SystemInfo.cpp
 *
 *  Created on: 2020年4月11日
 *      Author: Administrator
 */

#include "SystemInfo.h"
#include <sys/sysinfo.h>
#include "stdio.h"
#include "utils/log.h"
namespace std {

SystemInfo systemInfo;
SystemInfo::SystemInfo() {
	// TODO 自动生成的构造函数存根

}

SystemInfo::~SystemInfo() {
	// TODO 自动生成的析构函数存根
}
float SystemInfo::mem_usage(){

	struct sysinfo tmp;
	sysinfo(&tmp);
	float usage;
	usage =  (tmp.totalram - tmp.freeram)/(float)tmp.totalram ;
//	LOGD("内存：%0.1fM 空闲：%0.1fM",tmp.totalram/1024.0/1024.0,tmp.freeram/1024.0/1024.0);
//	LOGD("内存使用率：%0.1f",usage);
	return usage;
}


} /* namespace std */
