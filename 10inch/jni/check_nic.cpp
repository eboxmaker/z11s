/*
 * check_nic.cpp
 *
 *  Created on: 2018年12月26日
 *      Author: shentq
 */




#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include "utils/log.h"
#include <net/if.h>  // IFF_RUNNING



//如果网卡已脸上网线，返回0，否则返回-1.

int check_nic(char *nic)

{

    struct ifreq ifr;

    int skfd = socket(AF_INET, SOCK_DGRAM, 0);



    strcpy(ifr.ifr_name, nic);

    if (ioctl(skfd, SIOCGIFFLAGS, &ifr) < 0)

    {

        return -1;

    }

    if(ifr.ifr_flags & IFF_RUNNING)

        return 0;  // 网卡已插上网线

    else
    	return -1;

}
