/*
 * NetContext.h
 *
 *  Created on: 2020年4月12日
 *      Author: Administrator
 */

#ifndef JNI_NETWORK_NETCONTEXT_H_
#define JNI_NETWORK_NETCONTEXT_H_

#include <vector>
#include "system/Thread.h"
#include "lib/net.h"
#include "netProtocolData.h"
#include "network/NetProtocolSender.h"
#include "network/NetProtocolParser.h"
#include "net/NetManager.h"



class NetContext : public Thread {
public:
	virtual ~NetContext();

	void begin(std::string _server,uint16_t port);
	void begin(std::string _server);
	void begin(const char *_server);


	void Conn();

	void Close();
	int	Write(std::string str);
	int	Write(byte* bytes, int bytes_len);

	bool connected();

	bool rx_loop();

	static NetContext* getInstance();
//	net::Conn* conn = net::Dial("tcp", "www.baidu.com:80");
	net::Conn* conn;

protected:
	virtual bool readyToRun();
	virtual bool threadLoop();

private:
	NetContext();

private:
	char buf[1024*500];
	size_t cnt ;
	int protocol_state;
	bool connected_;

	time_t last_live_time;
	time_t last_conn_time;
	NetProtocolData   		msg;
	NetProtocolDataList   timeoutMsgList;



	std::string server;

};
#define NETCONTEXT		NetContext::getInstance()

#endif /* JNI_NETWORK_NETCONTEXT_H_ */
