/*
 * door.h
 *
 *  Created on: 2019年4月11日
 *      Author: shentq
 */

#ifndef JNI_DOOR_H_
#define JNI_DOOR_H_
#include "objectType.h"

namespace std {

class Door {
public:
	Door();
	virtual ~Door();
	void set(doorState_t state);
	doorState_t get();
};
extern Door door;

} /* namespace std */

#endif /* JNI_DOOR_H_ */
