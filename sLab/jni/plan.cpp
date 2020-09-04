/*
 * plan.cpp
 *
 *  Created on: 2019年4月19日
 *      Author: shentq
 */

#include "plan.h"
#include "utils/log.h"

namespace std {

Plan::Plan() :
			_maxSize(20),
			_size(0) {
	// TODO 自动生成的构造函数存根

}

Plan::~Plan() {
	// TODO 自动生成的析构函数存根
}
bool Plan::add(PlanRow_t &_row)
{
	if(_size < _maxSize)
	{
		row[_size].unit = _row.unit;
		row[_size].startTime = _row.startTime;
		row[_size].endTime = _row.endTime;
		row[_size].teacher = _row.teacher;
		row[_size].class_ = _row.class_;
		row[_size].course = _row.course;
		_size++;
	}
}
void Plan::clear()
{
	_size = 0;
}
void  Plan::print()
{
	LOGD("=====课程信息====");
	LOGD("共：%d条",_size);
	for(int i = 0; i < _size; i++)
	{
		LOGD("%s,%s,%s",row[i].unit.c_str(),row[i].teacher.c_str(),row[i].class_.c_str());
	}

}
Plan gPlan;

} /* namespace std */
