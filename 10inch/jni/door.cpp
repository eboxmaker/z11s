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

}

Door::~Door() {
	// TODO 自动生成的析构函数存根
}

void Door::set(doorState_t state)
{
	GpioHelper::output(GPIO_PIN_B_02, state);
}
doorState_t Door::get()
{
	return GpioHelper::input(GPIO_PIN_B_03);
}
Door door;
} /* namespace std */
