/*
 * SocketClient.h
 *
 *  Created on: Aug 9, 2017
 *      Author: guoxs
 */

#ifndef _SOCKET_SOCKETCLIENT_H_
#define _SOCKET_SOCKETCLIENT_H_


#define FILE_DIR		"/mnt/extsd/"


class SocketClient {
public:
	SocketClient();
	virtual ~SocketClient();

	void start();
	void stop();
	void send(char *msg);
	void threadLoop();

public:
	typedef enum {
		E_SOCKET_STATUS_START_RECV		= 0,
		E_SOCKET_STATUS_RECV_OK			= 1,
		E_SOCKET_STATUS_RECV_ERROR		= 2,
		E_SOCKET_STATUS_UPDATE_DATE		= 3
	} ESocketStatus;

	class ISocketListener {
	public:
		virtual ~ISocketListener() { };
		virtual void notify(int what, int status, const char *msg) = 0;
	};

	void setSocketListener(ISocketListener *pListener) {
		mSocketListener = pListener;
	}
	bool connected();
	bool conncetState;
private:
	bool connect(char *ip, uint16_t port);
	bool disconnect();

private:
	int mClientSocket;
	ISocketListener *mSocketListener;
	bool connectState;
};

#endif /* _SOCKET_SOCKETCLIENT_H_ */
