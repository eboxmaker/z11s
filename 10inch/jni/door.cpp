/*
 * door.cpp
 *
 *  Created on: 2019年4月11日
 *      Author: shentq
 */
#include "include/utils/GpioHelper.h"

#include "door.h"

namespace std {

Door::Door() {
	// TODO 自动生成的构造函数存根
	LockLogic = HighLock;
	TongueLogic = HighLock;
}

Door::~Door() {
	// TODO 自动生成的析构函数存根
}

void Door::set(doorState_t state)
{
	if(state == Lock){
		if(LockLogic == HighLock)
			GpioHelper::output(GPIO_PIN_B_02, 1);
		else
			GpioHelper::output(GPIO_PIN_B_02, 0);
	}
	else
	{
		if(LockLogic == HighLock)
			GpioHelper::output(GPIO_PIN_B_02, 0);
		else
			GpioHelper::output(GPIO_PIN_B_02, 1);
	}

}
doorState_t Door::get()
{
	if(TongueLogic == HighLock)
		if( GpioHelper::input(GPIO_PIN_B_03) == 1)
			return Lock;
		else
			return UnLock;
	else
		if( GpioHelper::input(GPIO_PIN_B_03) == 0)
			return Lock;
		else
			return UnLock;
}
Door door;
} /* namespace std */
