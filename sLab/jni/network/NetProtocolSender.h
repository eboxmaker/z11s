/*
 * NetProtocolSender.h
 *
 *  Created on: 2020年4月12日
 *      Author: Administrator
 */

#ifndef JNI_NETWORK_NETPROTOCOLSENDER_H_
#define JNI_NETWORK_NETPROTOCOLSENDER_H_
#include "netProtocolData.h"

void tx_loop();
int writeProtocol(NetProtocolData data);
bool deletDataFromList(NetProtocolData &data);


#endif /* JNI_NETWORK_NETPROTOCOLSENDER_H_ */
