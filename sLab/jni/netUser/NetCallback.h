/*
 * NetCallback.h
 *
 *  Created on: 2020年4月13日
 *      Author: Administrator
 */

#ifndef JNI_NETCALLBACK_H_
#define JNI_NETCALLBACK_H_
#include "system/thread.h"
#include "network/netContext.h"


void onNetDataToExeUpdate(const NetProtocolData &data);
void onNetDataServerAck(const NetProtocolData &data);

#endif /* JNI_NETCALLBACK_H_ */
