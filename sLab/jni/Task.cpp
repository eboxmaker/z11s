/*
 * Task.cpp
 *
 *  Created on: 2020年3月19日
 *      Author: Administrator
 */

#include "Task.h"
#include "utils/log.h"
#include "utils/GpioHelper.h"
#include "unistd.h"
namespace std {

Task task;

Task::Task() {
	// TODO 自动生成的构造函数存根

}

Task::~Task() {
	// TODO 自动生成的析构函数存根
}
bool Task::readyToRun(){

}

static bool value;
bool Task::threadLoop(){

	while(1)
	{

//		LOGD("查询温度 task pid=%d",pthread_self());
//		dev.update_meter();


//		LOGD("采集温度：%0.1f,启动温度：%0.1f",dev.senser_temperature,dev.start_temperature_master);
		Thread::sleep(5000);
	}

}

}
