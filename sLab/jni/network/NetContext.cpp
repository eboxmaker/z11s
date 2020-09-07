/*
 * NetContext.cpp
 *
 *  Created on: 2020年4月12日
 *      Author: Administrator
 */


#include <errno.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <memory.h>
#include <termio.h>
#include <sys/ioctl.h>

#include "NetContext.h"

#include "utils/Log.h"
#include "netProtocolData.h"





NetContext::NetContext() :
	cnt(0),
	protocol_state(0),
	connected_(false),
	conn(NULL)
{


}

NetContext::~NetContext() {
	Close();
}

void NetContext::begin(std::string _server,uint16_t port){
	char buf[32];
	sprintf(buf,"%s:%d",_server.c_str(),port);
	server = buf;
	LOGD("服务器信息:%s",server.c_str());

	Conn();
	if(!isRunning())
	{
		run("NetContext");
	}
}

void NetContext::begin(std::string _server)
{
	server = _server;
	Conn();
	if(!isRunning())
		run("NetContext");

}
void NetContext::begin(const char *_server)
{
	server = _server;
	Conn();
	if(!isRunning())
		run("NetContext");

}

void NetContext::Conn()
{
	if(conn != NULL)//初次运行防止空指针
		conn->Close();
	conn = net::Dial("tcp", server);

	if(conn->get_sock() > 0)
	{
		LOGD("conn连接成功sock:%d",conn->get_sock());
		connected_ = true;
		last_live_time = time(NULL);
	}
	else
	{
		connected_ = false;
		LOGD("conn连接失败");
	}
}

void NetContext::Close() {
	LOGD("close network ...\n");
	connected_ = false;
	conn->Close();
}
int	NetContext::Write(std::string str)
{
	return conn->Write((byte*)str.c_str(), str.size());
}

int NetContext::Write(byte* bytes, int bytes_len)
{
	return conn->Write(bytes, bytes_len);
}
bool NetContext::connected()
{
	return connected_;
}


NetContext* NetContext::getInstance() {
	static NetContext sUC;
	return &sUC;           //UartContext类实例
}
bool NetContext::rx_loop(){
	bool ret = false;
	int res;
	char data;
	do{
		res = conn->Read((byte*)&data, 1 , 1000);//sock->read_(&data);
		if(res == 1)
		{
			last_live_time = time(NULL);
			switch(protocol_state)
			{
				case 0:
					if(data == '{')
					{
						protocol_state = 1;
						buf[cnt] = data;
						cnt++;
					}
					break;
				case 1:
					buf[cnt] = data;
					cnt++;
					if(cnt >= 1024*500)
					{
						LOGE("消息数据溢出");
						cnt = 0;
						protocol_state = 0;
						break;
					}
					if(data == '}'){
						buf[cnt] = '\0';
						cnt++;
//						LOGD("接收完成：len=%d\n[%s]",cnt,buf);
						if(parseNetProtocol(buf,msg))
						{
//							LOGD("解析json成功:%s",buf);
							if(deletDataFromList(msg))
							{
//								LOGD("删除成功");
							}
							else if(msg.status == Status::OK || msg.status == Status::Err)
							{
								LOGE("删除失败");
							}
							else
							{
//								LOGD("不需要删除");
							}
							ret = true;
						}else
						{
							LOGE("解析json失败:%s",buf);
							ret = false;
						}
						protocol_state = 0;
						cnt = 0;
					}
					break;
				default:
					protocol_state = 0;
					cnt = 0;
					ret = false;
					LOGE("绝对不应该执行的代码...............");
					break;
			}
		}
		else if(res == -10000)
		{
			ret = false;
		}
		else if(res == 0 || res == -1)
		{
			connected_ = false;
			ret = false;
		}
	}while(res == 1);

	return ret;
}
bool NetContext::readyToRun() {
//	netUser.begin();
//	LOGD("net Context readyToRun Success\n");
	return (1);
}

bool NetContext::threadLoop() {
	bool ret;
	int timeout_cnt;
	Thread::sleep(2000);


	while(1){
		ret = rx_loop();
		if(ret){
			//LOGD("处理完一条消息");
		}

		tx_loop();


		if(time(NULL) - last_live_time > 16)
		{
			connected_ = false;
		}
		if(connected_ == false)
		{
			if(time(NULL) - last_conn_time > 4)
			{
				LOGD("重新连接");
				last_conn_time = time(NULL);
				Conn();
			}
		}


		Thread::sleep(100);
		if (exitPending()) {
			return false;
		}
	}

	return true;
}






