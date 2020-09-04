/*
 * plan.h
 *
 *  Created on: 2019年4月19日
 *      Author: shentq
 */

#ifndef JNI_PLAN_H_
#define JNI_PLAN_H_
#include <iostream>
namespace std {

class Plan {

public:
	typedef struct
	{
		string unit;
		string startTime;
		string endTime;
		string teacher;
		string class_;
		string course;
	}PlanRow_t;

public:
	Plan();
	virtual ~Plan();

	int size()	{return _size;}
	int maxSize(){return _maxSize;}
	bool add(PlanRow_t &_row);
	void clear();
	void print();

	PlanRow_t row[10];

private:
	int _maxSize;
	int _size;

};
extern Plan gPlan;

} /* namespace std */

#endif /* JNI_PLAN_H_ */
