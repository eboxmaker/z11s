/*
 * door.h
 *
 *  Created on: 2019年4月11日
 *      Author: shentq
 */

#ifndef JNI_DOOR_H_
#define JNI_DOOR_H_
#include "enum_def.h"
namespace std {

typedef enum {HighLock,HighUnlock}LockLogic_t;
typedef enum {HighClose,HighOpen}DoorLogic_t;
	//门锁状态结构体
	typedef enum
	{
		Lock,
		Unlock,
	}DoorLockState_t;

	typedef enum
	{
		Close,
		Open
	}DoorDoorState_t;


	typedef enum
	{
		LockClose,
		LockOpen,
		UnlockClose,
		UnlockOpen,
	}DoorState_t;


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


class Door {
public:
	Door();
	virtual ~Door();

	void set_lock_ctr(DoorLockState_t state);


	DoorLockState_t get_lock_ctr_state();
	DoorLockState_t get_lock_state();
	DoorDoorState_t get_door_state();

	DoorState_t		get_state();



	void			set_lock_ctr_logic(LockLogic_t logic);
	void			set_lock_logic(LockLogic_t logic);
	void			set_door_logic(DoorLogic_t logic);
	LockLogic_t 	get_lock_ctr_logic(){return LockCtrLogic;};
	LockLogic_t 	get_lock_logic(){return Feed1Logic;};
	DoorLogic_t 	get_door_logic(){return Feed2Logic;};

	bool 	get_door_btn();

	void 	loop();
private:
	DoorStateRaw_t get_raw();
	LockLogic_t LockCtrLogic;
	LockLogic_t Feed1Logic;
	DoorLogic_t Feed2Logic;

	DoorLockState_t lock_state;
	DoorDoorState_t door_state;
	DoorState_t state;

	DoorState_t last_state;

	DoorLockState_t io_lock_ctr_state;
};
extern Door door;

} /* namespace std */

#endif /* JNI_DOOR_H_ */
