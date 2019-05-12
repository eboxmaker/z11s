/*
 * door.h
 *
 *  Created on: 2019年4月11日
 *      Author: shentq
 */

#ifndef JNI_DOOR_H_
#define JNI_DOOR_H_

namespace std {

	typedef enum {HighLock,HighOpen,NONE}LockLogic_t;
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
	LockLogic_t TongueLogic;
	LockLogic_t MagnetLogic;
};
extern Door door;

} /* namespace std */

#endif /* JNI_DOOR_H_ */
