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
	MagnetLogic = None;
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
MagnetState Door::getMagnet()
{
	if(MagnetLogic == HighLock){
		if( GpioHelper::input(GPIO_PIN_B_03) == 1) return MagnetState::Close;
		else return MagnetState::Open;
	}
	else if(MagnetLogic == HighOpen){
		if( GpioHelper::input(GPIO_PIN_B_03) == 0) return MagnetState::Close;
		else  return MagnetState::Open;
	}
	else {
		return MagnetState::Unkonw;
	}
}
TongueState Door::getTongue()
{
	if(TongueLogic == HighLock){
		if( GpioHelper::input(GPIO_PIN_B_03) == 1) return TongueState::Lock;
		else return TongueState::Unlock;
	}
	else if(MagnetLogic == HighOpen){
		if( GpioHelper::input(GPIO_PIN_B_03) == 0) return TongueState::Lock;
		else  return TongueState::Unlock;
	}
	else {
		return TongueState::Unkonw;
	}
}
doorState_t Door::get()
{
	if(TongueLogic == HighLock){
		if( GpioHelper::input(GPIO_PIN_B_03) == 1) return Lock;
		else return UnLock;
	}
	else{
		if( GpioHelper::input(GPIO_PIN_B_03) == 0) return Lock;
		else  return UnLock;
	}
}
doorFullState_t Door::getFull()
{
	TongueState ts = getTongue();
	MagnetState ms = getMagnet();

	if(ts == TongueState::Lock && ms == MagnetState::Close)
		return Close_Lock;
	else if(ts == TongueState::Lock && ms == MagnetState::Unkonw)
		return Close_Lock;
	else if(ts == TongueState::Lock && ms == MagnetState::Open)
		return Open_Lock;
	else if(ts == TongueState::Unlock && ms == MagnetState::Open)
		return Open_Unlock;
	else if(ts == TongueState::Unlock && ms == MagnetState::Close)
		return Close_Unlock;
	else if(ts == TongueState::Unlock && ms == MagnetState::Unkonw)
		return Open_Lock;
	else if(ts == TongueState::Unkonw && ms == MagnetState::Close)
		return Close_Lock;
	else if(ts == TongueState::Unkonw && ms == MagnetState::Open)
		return Open_Lock;
	else if(ts == TongueState::Unkonw && ms == MagnetState::Unkonw)
		return Open_Unlock;


}

Door door;
} /* namespace std */
