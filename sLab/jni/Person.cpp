/*
 * Person.cpp
 *
 *  Created on: 2020年9月2日
 *      Author: shentq
 */

#include "Person.h"
#include "utils/log.h"

namespace std {
PersonInfoList_t gPersonList;
Person gPerson;

Person::Person() {
	// TODO 自动生成的构造函数存根

}

Person::~Person() {
	// TODO 自动生成的析构函数存根
}
void Person::update(PersonInfoList_t &list_)
{
	//清空指纹
	if(!isRunning())
	{
		run();
	}
}

bool Person::readyToRun()
{
	LOGD("指纹处理线程启动");
}
bool Person::threadLoop()
{


	LOGD("指纹处理线程结束");
	Thread::sleep(1000);
	return false;
}

} /* namespace std */
