/*
 * Udp.cpp
 *
 *  Created on: 2018年12月26日
 *      Author: shentq
 */

#include "Udp.h"
#include "utils/log.h"

#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



Udp::Udp() {
	// TODO 自动生成的构造函数存根

}

Udp::~Udp() {
	// TODO 自动生成的析构函数存根
}

bool Udp::start(uint16_t port)
{

	int len;

	struct sockaddr_in my_addr;   //服务器网络地址结构体

    //    struct sockaddr_in remote_addr; //客户端网络地址结构体

	int sin_size;

	char buf[BUFSIZ];  //数据传送的缓冲区

	memset(&my_addr,0,sizeof(my_addr)); //数据初始化--清零

	my_addr.sin_family=AF_INET; //设置为IP通信

	my_addr.sin_addr.s_addr=INADDR_ANY;//服务器IP地址--允许连接到所有本地地址上

	my_addr.sin_port=htons(port); //服务器端口号
	/*创建服务器端套接字--IPv4协议，面向无连接通信，UDP协议*/
	if((sock=socket(PF_INET,SOCK_DGRAM,0))<0)
	{
		LOGE("socket error");
		return false;
	}

	/*将套接字绑定到服务器的网络地址上*/

	if (bind(sock,(struct sockaddr *)&my_addr,sizeof(struct sockaddr))<0)
	{
		LOGE("bind error");
		return 1;
	}

}

int Udp::send(UDPMessage *msg)
{
	int byteNum = msg->len;
	int len;
	while(byteNum)
	{
		int size = (byteNum > 4096) ? 4096:byteNum;
		if((len=sendto(sock,msg->ptr,size,0,(struct sockaddr *)&msg->remote,sizeof(struct sockaddr)))<0)
		{
			LOGE("err\n");
			return 1;
		}
		byteNum -= len;
		usleep(10000);
	}
	LOGE("len:%d,bytenum%d\n",msg->len,byteNum);


}
int Udp::recv(UDPMessage *msg)
{
	int len;
	int sin_size=sizeof(struct sockaddr_in);
	/*接收客户端的数据并将其发送给客户端--recvfrom是无连接的*/
	if((len=recvfrom(sock,msg->ptr,msg->len,0,(struct sockaddr *)&(msg->remote),&sin_size))<0)
	{
		LOGE("recvfrom error");
		return 0;
	}
	else
	{
		//LOGE("%s",msg->buf);
		return len;
	}
}
bool Udp::stop()
{
	close(sock);
}
string Udp::parseIP(UDPMessage *msg)
{
	string temp = inet_ntoa(msg->remote.sin_addr);
	return temp;
}
uint16_t Udp::parsePort(UDPMessage *msg)
{
	return htons(msg->remote.sin_port);
}




#if 0
int main(int argc, char *argv[])

{











	printf("waiting for a packet.../n");



	/*接收客户端的数据并将其发送给客户端--recvfrom是无连接的*/

	if((len=recvfrom(server_sockfd,buf,BUFSIZ,0,(struct sockaddr *)&remote_addr,&sin_size))<0)

	{

		perror("recvfrom error");

		return 1;

	}

	printf("received packet from %s:/n",inet_ntoa(remote_addr.sin_addr));

	buf[len]='/0';

	printf("contents: %s/n",buf);



	/*关闭套接字*/

	close(server_sockfd);



        return 0;

}
#endif
