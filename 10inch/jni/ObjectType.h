/*
 * ObjectType.h
 *
 *  Created on: 2019年3月7日
 *      Author: shentq
 */

#ifndef JNI_OBJECTTYPE_H_
#define JNI_OBJECTTYPE_H_

#include <fstream>
#include <vector>

typedef std::vector<std::string> stringList;

typedef union
{
	unsigned long long value;
	unsigned char bytes[8];
}XdataULong_t;

typedef enum
{
	Lock,
	UnLock
}doorState_t;
#endif /* JNI_OBJECTTYPE_H_ */
