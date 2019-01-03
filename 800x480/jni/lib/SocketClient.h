/*
 * SocketClient.h
 *
 *  Created on: Aug 9, 2017
 *      Author: guoxs
 */

#ifndef _SOCKET_SOCKETCLIENT_H_
#define _SOCKET_SOCKETCLIENT_H_

#include "ringbuf.h"

#define FILE_DIR		"/mnt/extsd/"


class SocketClient {
public:
	SocketClient();
	virtual ~SocketClient();

	bool connect(char *ip, uint16_t port);
	bool disconnect();
	bool connected();

	void write_(char *msg);
	void write_(char *msg,size_t length);
	void read_(char *msg,size_t length);
	char read_();
	size_t read_json(char *msg,size_t max_len);
	size_t available();

	bool setHeartbeat(int timeout,char *msg,size_t len);
	void threadLoop();

	void timer_thread();




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
	//ISocketListener *mSocketListener;
	bool connectState;
	int heartbeatTime;
	char *hearbeatMsg;
	ISocketListener *mSocketListener;

};

#endif /* _SOCKET_SOCKETCLIENT_H_ */
