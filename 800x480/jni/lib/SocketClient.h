/*
 * SocketClient.h
 *
 *  Created on: Aug 9, 2017
 *      Author: guoxs
 */

#ifndef _SOCKET_SOCKETCLIENT_H_
#define _SOCKET_SOCKETCLIENT_H_

#include "ringbuf.h"
#include <fstream>
#include "netinet/tcp.h"

typedef void (*NetNotify_t)(void);

class SocketClient {
public:
	SocketClient();
	virtual ~SocketClient();

	bool connect(char *ip, uint16_t port);
	bool disconnect();
	bool connected();

	void updateTriger();
	void disableTriger();


	void write_(std::string &msg);
	void write_(char *msg);
	void write_(char *msg,size_t length);

	void read_(char *msg,size_t length);
	char read_();
	size_t available();

	bool setHeartbeat(int Interval);
	void updateHearbeat();
	void sendHearbeat();



	void threadLoop();

	void timer_thread();

	void attachOnConncet(NetNotify_t callback,int num);
	void attachOnDisonncet(NetNotify_t callback,int num);

	void deattachOnConncet(int num);
	void deattachOnDisonncet(int num);

	class ISocketListener {
	public:
		virtual ~ISocketListener() { };
		virtual void notify(int what, int status, const char *msg) = 0;
	};

	void setSocketListener(ISocketListener *pListener) {
		mSocketListener = pListener;
	}

private:
	RingBufInt8 rxbuf;
	bool conncetState;
	int mClientSocket;

	long long trigerTime;
	int trigerTimeout;

	long lastHeartbeatTime;
	int heartbeatInterval;
	char hearbeatMsg[100];



	int maxCallbackNum;
	 NetNotify_t onConncet[5];
	 NetNotify_t onDisconncet[5];


	ISocketListener *mSocketListener;
};

#endif /* _SOCKET_SOCKETCLIENT_H_ */
