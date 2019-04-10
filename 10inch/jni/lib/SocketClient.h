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
#include <iostream>
#include <fstream>

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


	void hearbeatUpdate();
	void hearbeatSend();


	void threadLoop();

	void attachOnConnect(NetNotify_t callback,int num);
	void attachOnDisconnect(NetNotify_t callback,int num);

	void deattachOnConnect(int num);
	void deattachOnDisconnect(int num);

	void asCmd();
	void asFile();

	class ISocketListener {
	public:
		virtual ~ISocketListener() { };
		virtual void notify(int what, int status, const char *msg) = 0;
	};

	void setSocketListener(ISocketListener *pListener) {
		mSocketListener = pListener;
	}
	long  trigerTime;
	int trigerTimeout;
	bool conncetState;
	enum {
		CmdMode,
		FileMode
	}mode;
private:
	int mClientSocket;



	long lastHeartbeatTime;



	int maxCallbackNum;
	 NetNotify_t onConncet[5];
	 NetNotify_t onDisconncet[5];


	ISocketListener *mSocketListener;
};

#endif /* _SOCKET_SOCKETCLIENT_H_ */
