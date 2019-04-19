/*
 * plan.cpp
 *
 *  Created on: 2019年4月19日
 *      Author: shentq
 */

#include "plan.h"

namespace std {

Plan::Plan() :
			_maxSize(100),
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
		row[_size].teacher = _row.teacher;
		row[_size].class_ = _row.class_;
		row[_size].courser = _row.courser;
		_size++;
	}
}
void Plan::clear()
{
	_size = 0;
}
Plan gPlan;

} /* namespace std */
