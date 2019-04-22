/*
 * Udp.h
 *
 *  Created on: 2018年12月26日
 *      Author: shentq
 */

#ifndef JNI_UDP_H_
#define JNI_UDP_H_

#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;
class UDPMessage
{
public:
    char *ptr;
    int len;
    struct sockaddr_in remote;
};
class Udp {
public:
	Udp();
	virtual ~Udp();

	bool start(uint16_t port);
	int send(UDPMessage *msg);
	int recv(UDPMessage *msg);
	bool stop();
	string parseIP(UDPMessage *msg);
	uint16_t parsePort(UDPMessage *msg);
public:
    struct sockaddr_in remote;
    int sock;

};

#endif /* JNI_UDP_H_ */
