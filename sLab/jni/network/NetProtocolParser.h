/*
 * NetProtocolParser.h
 *
 *  Created on: 2020年4月12日
 *      Author: Administrator
 */

#ifndef JNI_NETWORK_NETPROTOCOLPARSER_H_
#define JNI_NETWORK_NETPROTOCOLPARSER_H_

#include "netProtocolData.h"


typedef void (*OnNetProtocolDataUpdateFun)(const NetProtocolData &data);

void registerNetProtocolDataUpdateListener(OnNetProtocolDataUpdateFun pListener);
void unregisterNetProtocolDataUpdateListener(OnNetProtocolDataUpdateFun pListener);
void notifyNetProtocolDataUpdate(const NetProtocolData &data) ;


bool parseNetProtocol(char *data,NetProtocolData &msg) ;
int notifyProtocolDataTimeout(NetProtocolDataList &data);

#endif /* JNI_NETWORK_NETPROTOCOLPARSER_H_ */
