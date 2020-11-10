/*
 * door.h
 *
 *  Created on: 2019年4月11日
 *      Author: shentq
 */

#ifndef JNI_DOOR_H_
#define JNI_DOOR_H_
#include "system/Thread.h"

namespace std {

typedef enum {HighLock,HighUnlock}LockLogic_t;
typedef enum {HighClose,HighOpen}DoorLogic_t;
	//门锁状态结构体
	typedef enum
	{
		Lock,
		Unlock,
	}LockState_t;

	typedef enum
	{
		Close,
		Open
	}DoorState_t;

	typedef enum
	{
		LockClose,
		LockOpen,
		UnlockClose,
		UnlockOpen,
	}DoorLockState_t;


	typedef struct
	{
		union{
			struct{
				uint8_t feed1:1;
				uint8_t feed2:1;
			}bit;
			uint8_t value;
		};
	}DoorStateRaw_t;


class Door :public Thread
{
public:
	Door();
	virtual ~Door();

	void 			set_lock_ctr(LockState_t state);
	void 			lock_ctr_unlock();
	void 			lock_ctr_lock();
	LockState_t 	get_lock_state();
	DoorState_t 	get_door_state();
	DoorLockState_t	get_state();




	//和门相关的三个IO的逻辑关系配置
	LockState_t 	get_lock_ctr_state();
	void			set_lock_ctr_logic(LockLogic_t logic);
	LockLogic_t 	get_lock_ctr_logic(){return LockCtrLogic;};

	void			set_lock_logic(LockLogic_t logic);
	LockLogic_t 	get_lock_logic(){return Feed1Logic;};

	void			set_door_logic(DoorLogic_t logic);
	DoorLogic_t 	get_door_logic(){return Feed2Logic;};


	//室内门的按键开关
	bool 	get_door_btn();

	void 	state_loop();
	void 	lock_btn_loop();

protected:
	virtual bool readyToRun();
	virtual bool threadLoop();
private:
	DoorStateRaw_t get_raw();
	LockLogic_t LockCtrLogic;
	LockLogic_t Feed1Logic;
	DoorLogic_t Feed2Logic;

	LockState_t lock_state;
	DoorState_t door_state;

	LockState_t lock_ctr_state;
	LockState_t last_lock_ctr_state;




	long last_lock_ctr_open_time;


};
extern Door door;

} /* namespace std */

#endif /* JNI_DOOR_H_ */
