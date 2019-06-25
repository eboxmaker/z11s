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
	//门锁状态结构体
	typedef enum
	{
		Lock,
		UnLock,
	}doorState_t;


class Door {
public:
	Door();
	virtual ~Door();
	void set(doorState_t state);
	doorState_t get();

	LockLogic_t LockLogic;
	LockLogic_t Feed1Logic;

};
extern Door door;

} /* namespace std */

#endif /* JNI_DOOR_H_ */
