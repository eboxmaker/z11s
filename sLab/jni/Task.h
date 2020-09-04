/*
 * Task.h
 *
 *  Created on: 2020年3月19日
 *      Author: Administrator
 */

#ifndef JNI_TASK_H_
#define JNI_TASK_H_
#include "stdint.h"
#include "uart/ProtocolParser.h"
#include "uart/UartContext.h"
#include "uart/ProtocolSender.h"

namespace std {

class Task : public Thread
{
public:
	Task();
	virtual ~Task();



protected:
	virtual bool readyToRun();
	virtual bool threadLoop();
};
extern Task task;
}

#endif /* JNI_TASK_H_ */
