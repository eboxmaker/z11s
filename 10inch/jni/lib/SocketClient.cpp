/*
 * SocketClient.cpp
 *
 *  Created on: Aug 9, 2017
 *      Author: guoxs
 */

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/rtc.h>
#include <time.h>
#include <sys/time.h>

#include "SocketClient.h"
#include "utils/Log.h"
#include "json_test.h"
#include "packageFile.h"
#include "globalVar.h"
#include "check_nic.h"
#include <time.h>
#include <signal.h>
#include "system/Thread.h"


static void* socketThreadRx(void *lParam) {
	((SocketClient *) lParam)->threadLoop();
	return NULL;
}


SocketClient::SocketClient() :
	conncetState(false),
	mClientSocket(-1),
	trigerTimeout(5),
	trigerTime(-1),
	maxCallbackNum(5),
	mode(SocketClient::CmdMode)
{

	for(int i = 0; i < maxCallbackNum; i++ )
	{
		onConncet[i] = NULL;
		onDisconncet[i] = NULL;
	}

}

SocketClient::~SocketClient() {
	disconnect();
}



bool SocketClient::connect(char *ip, uint16_t port) {

	conncetState = false;

	LOGE("%s:%d\n",ip,port);
	// 设置一个socket地址结构clientAddr,代表客户机internet地址, 端口
	struct sockaddr_in clientAddr;
	bzero(&clientAddr, sizeof(clientAddr)); // 把一段内存区的内容全部设置为0
	clientAddr.sin_family = AF_INET;    	// internet协议族
	clientAddr.sin_addr.s_addr = htons(INADDR_ANY);// INADDR_ANY表示自动获取本机地址
	clientAddr.sin_port = htons(0);    // 0表示让系统自动分配一个空闲端口
	// 创建用于internet的流协议(TCP)socket,用clientSocket代表客户机socket
	mClientSocket = socket(AF_INET, SOCK_STREAM, 0);

	LOGE("Create Socket clientSocket: %d\n", mClientSocket);
	if (mClientSocket < 0) {
		LOGE("Create Socket Failed!\n");
		disconnect();
		return false;
	}


	// 把客户机的socket和客户机的socket地址结构联系起来
	if (bind(mClientSocket, (struct sockaddr*) &clientAddr, sizeof(clientAddr))) {
		LOGE("Client Bind Port Failed!\n");
		disconnect();
		return false;
	}

	LOGE("Client Bind OK!\n");

	// 设置一个socket地址结构serverAddr,代表服务器的internet地址, 端口
	struct sockaddr_in serverAddr;
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port=htons(port); //服务器端口号


	if (inet_aton(ip, &serverAddr.sin_addr) == 0) {     // 服务器的IP地址来自程序的参数
		LOGE("Server IP Address Error!%s\n",ip);
		disconnect();
		return false;
	}

	socklen_t serverAddrLength = sizeof(serverAddr);
	// 向服务器发起连接,连接成功后clientSocket代表了客户机和服务器的一个socket连接
	if (::connect(mClientSocket, (struct sockaddr *) &serverAddr, serverAddrLength) < 0) {
		LOGE("Can Not Connect To %s!\n", ip);
		disconnect();
		return false;
	}
	LOGE("connect %s success!\n", ip);
//	bool bSet=true;
//	   setsockopt(mClientSocket,SOL_SOCKET,SO_KEEPALIVE,(const char*)&bSet,sizeof(bool));
//
//
//
//	   int                 keepIdle = 6;
//	     int                 keepInterval = 5;
//	     int                 keepCount = 3;
//	     setsockopt(mClientSocket, SOL_TCP, TCP_KEEPIDLE, (void *)&keepIdle, sizeof(keepIdle));
//	     setsockopt(mClientSocket, SOL_TCP,TCP_KEEPINTVL, (void *)&keepInterval, sizeof(keepInterval));
//	     setsockopt(mClientSocket,SOL_TCP, TCP_KEEPCNT, (void *)&keepCount, sizeof(keepCount));



	pthread_t threadID = 0;
	pthread_attr_t attr; 		// 线程属性
	pthread_attr_init(&attr);  	// 初始化线程属性
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);      // 设置线程属性
	int ret = pthread_create(&threadID, &attr, socketThreadRx, this);
	pthread_attr_destroy(&attr);
	if (ret || !threadID) {
		LOGE("create socket thread error, erro=%s\n", strerror(errno));
		disconnect();
		return false;
	}
	else
	{

		LOGE("创建一个线程, erro=%d\n",threadID);
	}

	LOGE("create socket thread success!\n");

	conncetState = true;
	for(int i = 0; i < maxCallbackNum; i++ )
	{
		if(onConncet[i] != NULL)
			onConncet[i]();
	}
	hearbeatUpdate();

	return true;
}
bool SocketClient::connected()
{
//	int optval, optlen = sizeof(int);
//	getsockopt(mClientSocket, SOL_SOCKET, SO_ERROR,(char*) &optval, &optlen);
//
//	switch(optval){
//
//	case 0:
//		conncetState = true;
//		break;
//	default:
//		conncetState = false;
//		break;
//	}
	//LOGE("上次通讯时间：%D",time(NULL) - lastHeartbeatTime);

	if(conncetState == true)
	{
		if(time(NULL) - lastHeartbeatTime > dev.heartbeatInterval*3)
			conncetState = false;
		else
			conncetState = true;
	}

	return conncetState;
}

bool SocketClient::disconnect() {
	LOGE("SocketClient disconnect\n");
	conncetState = false;
	if (mClientSocket > 0) {
//		write_("");
		close(mClientSocket);
		mClientSocket = -1;
		for(int i = 0; i < maxCallbackNum; i++ )
		{
			if(onDisconncet[i] != NULL)
				onDisconncet[i]();
		}
//		LOGE("SocketClient close socket...\n");
	}
	// 关闭socket
	return true;
}


void SocketClient::hearbeatUpdate()
{
	lastHeartbeatTime = time(NULL);
}

void SocketClient::attachOnConnect(NetNotify_t callback,int num)
{
	if(num>=0 && num < maxCallbackNum)
		onConncet[num] = callback;
}
void SocketClient::attachOnDisconnect(NetNotify_t callback,int num)
{
	if(num>=0 && num < maxCallbackNum)
		onDisconncet[num] = callback;
}
void SocketClient::deattachOnConnect(int num)
{
	if(num>=0 && num < maxCallbackNum)
		onConncet[num] = NULL;
}
void SocketClient::deattachOnDisconnect(int num)
{
	if(num>=0 && num < maxCallbackNum)
		onDisconncet[num] = NULL;
}
void SocketClient::write_(string &msg)
{
	if(connected())
		write(mClientSocket,msg.c_str(), msg.length());
	return ;
}
void SocketClient::write_(char *msg)
{
	if(connected())
		write(mClientSocket,msg, strlen(msg));
	return ;
}
void SocketClient::write_(char *msg,size_t length)
{
	if(connected())
		write(mClientSocket,msg, length);
	return ;
}

void SocketClient::updateTriger()
{
	trigerTime = time(NULL);
}
void SocketClient::disableTriger()
{
	trigerTime = -1;
}
//char SocketClient::read_()
//{
//	return rxbuf.read();
//}
//
//void SocketClient::read_(char *msg,size_t length)
//{
//	for(int i = 0; i < length; i++)
//	{
//		msg[i] = rxbuf.read();
//	}
//}
//size_t SocketClient::available()
//{
////	return rxbuf.available();
//}

#define CMD_BUF_SIZE 2000*1024
#define FILE_BUF_SIZE 1024

void SocketClient::asCmd()
{
	static int counter =0;
	static bool ret;
	static int length = 0;
	static int msg_counter = 0;
	static int state = 0;
	static char msg_buf[CMD_BUF_SIZE];

	length = recv(mClientSocket, &msg_buf[msg_counter], 1,0);
	if(errno == 110)
	{
		LOGE("断网线,服务器开启防火墙：%d-(%s)",errno,strerror(errno));
		//断网线,服务器开启防火墙
		disconnect();
	}
	if(length == 0)
	{
		//服务器主动断开
		disconnect();
	}
	if(length > 0)
	{
		gSocket->hearbeatUpdate();

		switch(state)
		{
			case 0:
				if(msg_buf[msg_counter] == '{')
				{
					state = 1;
					msg_counter++;
				}
				break;
			case 1:
				if(msg_buf[msg_counter] == '}')
				{
					msg_buf[msg_counter + 1] = '\0';
					if(ParseJsonString(msg_buf) == true)
					{
						//LOGE("解析完成,size:%dbytes",msg_counter);
						exeCMD(msg_buf);
					}
					else//解析失败。顶层使用加密。数据中不会出现额外的{}；
					{
//							msg_counter++;
					}
					msg_counter = 0;
					memset(msg_buf,0,msg_counter);
					state = 0;
				}
				else
				{
					msg_counter++;
					if(msg_counter > CMD_BUF_SIZE*0.9)//防止缓冲区溢出
					{
						msg_counter = 0;
						memset(msg_buf,0,msg_counter);
						state = 0;
					}
				}
				break;
		}
	}
	else
	{
		msg_counter = 0;
		memset(msg_buf,0,msg_counter);
		state = 0;

	}
}
void SocketClient::asFile()
{
	static char buf[FILE_BUF_SIZE];
	static long fileLength;
	static int length = 0;
	length = recv(mClientSocket, buf, FILE_BUF_SIZE,0);



}


void SocketClient::threadLoop() {

	int counter =0;
	bool ret;
	int length = 0;
	int msg_counter = 0;
	int state = 0;

	struct timeval timeout = { 1,0  };     // 1s

	setsockopt(mClientSocket, SOL_SOCKET, SO_RCVTIMEO,
			(const char*)&timeout, sizeof(timeout));
    int keepAlive = 1; // 开启keepalive属性
    int keepIdle = 3; // 如该连接在5秒内没有任何数据往来,则进行探测
    int keepInterval = 3; // 探测时发包的时间间隔为3 秒
    int keepCount = 3; // 探测尝试的次数.如果第1次探测包就收到响应了,则后2次的不再发.

    setsockopt(mClientSocket, SOL_SOCKET, SO_KEEPALIVE, (void *)&keepAlive, sizeof(keepAlive));
    setsockopt(mClientSocket, SOL_TCP, TCP_KEEPIDLE, (void*)&keepIdle, sizeof(keepIdle));
    setsockopt(mClientSocket, SOL_TCP, TCP_KEEPINTVL, (void *)&keepInterval, sizeof(keepInterval));
    setsockopt(mClientSocket, SOL_TCP, TCP_KEEPCNT, (void *)&keepCount, sizeof(keepCount));

    while (1)
	{

    	switch(this->mode )
    	{
    	case SocketClient::CmdMode:
    		asCmd();
    		break;
    	case SocketClient::FileMode:
    		asFile();
    		break;
    	default :
    		break;

    	}

		if(mClientSocket < 0)
		{
			//pthread_detach(pthread_self());
			break;
		}
//
	}

	LOGE("关闭接收数据的线程.\n");
}
