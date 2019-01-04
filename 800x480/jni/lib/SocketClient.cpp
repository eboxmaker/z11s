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

#define BUFFER_SIZE 				409600
#define FILENAME_MAX_SIZE 			512
char buffer[BUFFER_SIZE] = { 0 };

static int rtcSetTime(const struct tm *tm_time) {
    int rtc_handle = -1;
	int ret = 0;
	struct rtc_time rtc_tm;
	if (tm_time == NULL) {
	    return  -1;
	}

    rtc_handle = open("/dev/rtc0", O_RDWR);
	if (rtc_handle < 0) {
		printf("open /dev/rtc0 fail\n");
		return  -1;
	}

	memset(&rtc_tm, 0, sizeof(rtc_tm));
	rtc_tm.tm_sec   = tm_time->tm_sec;
	rtc_tm.tm_min   = tm_time->tm_min;
	rtc_tm.tm_hour  = tm_time->tm_hour;
	rtc_tm.tm_mday  = tm_time->tm_mday;
	rtc_tm.tm_mon   = tm_time->tm_mon;
	rtc_tm.tm_year  = tm_time->tm_year;
	rtc_tm.tm_wday  = tm_time->tm_wday;
	rtc_tm.tm_yday  = tm_time->tm_yday;
	rtc_tm.tm_isdst = tm_time->tm_isdst;
	ret = ioctl(rtc_handle, RTC_SET_TIME, &rtc_tm);
    if (ret < 0) {
        printf("rtcSetTime fail\n");
        close(rtc_handle);
        return -1;
    }

	printf("rtc_set_time ok\n");
	close(rtc_handle);

	return 0;
}

static int setDateTime(struct tm* ptm) {
	time_t timep;
	struct timeval tv;
	ptm->tm_wday = 0;
	ptm->tm_yday = 0;
	ptm->tm_isdst = 0;
	timep = mktime(ptm);
	tv.tv_sec = timep;
	tv.tv_usec = 0;

	if (settimeofday(&tv, NULL) < 0) {
		printf("Set system date and time error, errno(%d)", errno);
		return -1;
	}

	time_t t = time(NULL);
	struct tm *local = localtime(&t);

	rtcSetTime(local);

	return 0;
}

static int setDateTime(const char *pDate) {
	LOGE("setDateTime pDate: %s\n", pDate);

	struct tm _tm;
	struct timeval tv;
	time_t timep;

	sscanf(pDate, "%d-%d-%d %d:%d:%d",
			&_tm.tm_year, &_tm.tm_mon,
			&_tm.tm_mday, &_tm.tm_hour, &_tm.tm_min, &_tm.tm_sec);

	_tm.tm_mon -= 1;
	_tm.tm_year -= 1900;

	timep = mktime(&_tm);
	tv.tv_sec = timep;
	tv.tv_usec = 0;

	return setDateTime(&_tm);
}

static void* socketThreadRx(void *lParam) {
	((SocketClient *) lParam)->threadLoop();
	return NULL;
}

static void* socketThreadHeatbeat(void *lParam) {
	((SocketClient *) lParam)->timer_thread();
	return NULL;
}

SocketClient::SocketClient() :
	conncetState(false),
	mClientSocket(-1){
	rxbuf.begin(409600);
}

SocketClient::~SocketClient() {
	disconnect();
	free(hearbeatMsg);
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

		LOGE("create socket thread ok, erro=%d\n",threadID);
	}

	LOGE("create socket thread success!\n");

	conncetState = true;

	return true;
}
//bool SocketClient::connected()
//{
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
//	return conncetState;
//}

bool SocketClient::disconnect() {
	LOGE("SocketClient disconnect\n");
	conncetState = false;
//	if (mClientSocket > 0) {
//		write_("");
//		LOGE("SocketClient close socket...\n");
//	}
	// 关闭socket
	close(mClientSocket);
	mClientSocket = -1;
	return true;
}
void SocketClient::write_(char *msg)
{
	write(mClientSocket,msg, strlen(msg));
	return ;
}
void SocketClient::write_(char *msg,size_t length)
{
	write(mClientSocket,msg, length);
	return ;
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
size_t SocketClient::available()
{
	return rxbuf.available();
}

void SocketClient::timer_thread()
{
	while(1)
	{

		sleep(heartbeatTime);
		if(mClientSocket > 0)
		{
			write_(hearbeatMsg);
			LOGE("timer thread running");
		}
	}

}
bool SocketClient::setHeartbeat(int timeout)
{
	heartbeatTime = timeout;
	string str = MakeCMDHeatbeat();
	memset(hearbeatMsg,0,sizeof(hearbeatMsg));
	memcpy(hearbeatMsg,str.c_str(),str.length());

	pthread_t threadID = 0;
	pthread_attr_t attr; 		// 线程属性
	pthread_attr_init(&attr);  	// 初始化线程属性
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);      // 设置线程属性
	int ret = pthread_create(&threadID, &attr, socketThreadHeatbeat, this);
	pthread_attr_destroy(&attr);
	if (ret || !threadID) {
		LOGE("create socket thread error, erro=%s\n", strerror(errno));
		return false;
	}
	else
	{
		LOGE("create timer thread ok, erro=%d\n",threadID);
	}
}
void SocketClient::threadLoop() {

	int counter =0;
	bool ret;
	int length = 0;
	int len;
	bool flag = false;

	struct timeval timeout = { 1,0  };     // 1s

	setsockopt(mClientSocket, SOL_SOCKET, SO_RCVTIMEO,
			(const char*)&timeout, sizeof(timeout));
	while (1)
	{
		length = recv(mClientSocket, buffer, BUFFER_SIZE,0);
		if(length > 0)
		{
			for(int i = 0; i < length; i++)
			{
				rxbuf.write(buffer[i]);
				if(buffer[i] == '}')
					flag = true;
			}
		}
		else
		{

				string x = cutOneJsonString(&rxbuf);
				if(x != "")
				{
					exeCMD(&x);
				}
				flag = false;
				//LOGE("缓冲区可用数据:%d",rxbuf.available());

			//LOGE("剩余:%d;len = %d",rxbuf.available(),length);
		}
		if(mClientSocket < 0)
			break;

	}

	LOGE("socket thread end.\n");
}
