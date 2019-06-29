/*
 * door.cpp
 *
 *  Created on: 2019年4月11日
 *      Author: shentq
 */
#include "include/utils/GpioHelper.h"
#include "storage/StoragePreferences.h"
#include "json_manager.h"
#include "door.h"

namespace std {

#define  IO_LOCK_CTR 	GPIO_PIN_B_02
#define  IO_LOCK_FEED 	GPIO_PIN_B_03
#define  IO_DOOR_FEED 	GPIO_PIN_B_07


Door::Door() {
	// TODO 自动生成的构造函数存根
	LockCtrLogic = StoragePreferences::getInt("door.LockCtrLogic",HighLock);
	Feed1Logic = StoragePreferences::getInt("door.Feed1Logic",HighLock);
	Feed2Logic = StoragePreferences::getInt("door.Feed2Logic",HighClose);

	last_state = LockClose;


}

Door::~Door() {
	// TODO 自动生成的析构函数存根
}
void Door::loop()
{
	state = get_state();
	if(state != last_state)
	{
		string ack = "";
		last_state = state;
		ack = jm.makeDoorState(state, StatusSet);
		gSocket->write_(ack);
	}
}

void Door::set_lock(DoorLockState_t state)
{
	if(state == Lock){
		if(LockCtrLogic == HighLock)
			GpioHelper::output(IO_LOCK_CTR, 1);
		else
			GpioHelper::output(IO_LOCK_CTR, 0);
	}
	else
	{
		if(LockCtrLogic == HighLock)
			GpioHelper::output(IO_LOCK_CTR, 0);
		else
			GpioHelper::output(IO_LOCK_CTR, 1);
	}

}

DoorLockState_t Door::get_lock_state()
{
	if(Feed1Logic == HighLock){
		if( GpioHelper::input(IO_LOCK_FEED) == 1) return Lock;
		else return Unlock;
	}
	else{
		if( GpioHelper::input(IO_LOCK_FEED) == 0) return Lock;
		else  return Unlock;
	}
}
DoorDoorState_t Door::get_door_state()
{
	if(Feed2Logic == HighClose){
		if( GpioHelper::input(IO_DOOR_FEED) == 1) return Close;
		else return Open;
	}
	else{
		if( GpioHelper::input(IO_DOOR_FEED) == 0) return Close;
		else  return Open;
	}
}

void Door::set_lock_ctr_logic(LockLogic_t logic)
{
	door.LockCtrLogic  = logic;
	StoragePreferences::putInt("door.LockCtrLogic", door.LockCtrLogic);
}
void Door::set_lock_logic(LockLogic_t logic)
{
	door.Feed1Logic  = logic;
	StoragePreferences::putInt("door.Feed1Logic", door.Feed1Logic);
}

void Door::set_door_logic(DoorLogic_t logic)
{
	door.Feed2Logic  = logic;
    StoragePreferences::putInt("door.Feed2Logic", door.Feed2Logic);
}

DoorStateRaw_t Door::get_raw()
{
	DoorStateRaw_t raw;
	raw.value = 0;
	raw.bit.feed1 = GpioHelper::input(IO_LOCK_FEED);
	raw.bit.feed2 = GpioHelper::input(IO_DOOR_FEED);
	return raw;
}

DoorState_t Door::get_state()
{
	DoorStateRaw_t raw;

	raw = get_raw();

	if(Feed1Logic == HighLock){
		if( raw.bit.feed1 == 1)
			lock_state = Lock;
		else
			lock_state = Unlock;
	}
	else{
		if( raw.bit.feed1 == 1)
			lock_state = Unlock;
		else
			lock_state = Lock;
	}


	if(Feed2Logic == HighOpen){
		if( raw.bit.feed2 == 1)
			door_state = Open;
		else
			door_state = Close;
	}
	else{
		if( raw.bit.feed2 == 1)
			door_state = Close;
		else
			door_state = Open;
	}

	if(lock_state == Unlock && door_state == Open){
		state = UnlockOpen;
	}
	else if(lock_state == Unlock && door_state == Close){
		state = UnlockClose;
	}
	else if(lock_state == Lock && door_state == Open){
		state = LockOpen;
	}
	else if(lock_state == Lock && door_state == Close){
		state = LockClose;
	}
	return state;

}


Door door;
} /* namespace std */
