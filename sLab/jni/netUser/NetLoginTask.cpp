/*
 * NetCallback.cpp
 *
 *  Created on: 2020年4月13日
 *      Author: Administrator
 */

#include "NetLoginTask.h"
#include "Netcallback.h"

#include "network/netcontext.h"
#include "jsonmanager.h"
#include<unistd.h>
#include<sys/reboot.h>
#include "http/httpDownload.h"
#include "type.h"





NetUserApp::NetUserApp():
		login_state(false)
{

}
NetUserApp::~NetUserApp()
{

}
void NetUserApp::begin()
{
	if(!isRunning())
	{
		run();
	}
}
void NetUserApp::login_state_set(bool state)
{
	login_state = state;
}
bool NetUserApp::login_state_get()
{
	return login_state;
}
//int NetUserApp::write(NetProtocolData &data);
int NetUserApp::write(NetProtocolData &data)
{
//	if(login_state)
//	{
//		return writeProtocol(data);
//	}
//	else
//	{
//
//	}
//	return -1;


	return writeProtocol(data);

}

bool NetUserApp::readyToRun()
{
	registerNetProtocolDataUpdateListener(onNetDataToExeUpdate);
	registerNetProtocolDataUpdateListener(onNetDataServerAck);
	return true;
}
bool NetUserApp::threadLoop()
{
	NetProtocolData tmp;
	static uint32_t last_login_time = time(NULL);
	static uint32_t last_heart = time(NULL) - 5;
	static uint32_t last = 0;
	static uint32_t lost_times = 0;

	while(1)
	{
		if(NETCONTEXT->connected())
		{
			//心跳
			if(time(NULL) - last_heart >= 5)
			{
				last_heart = time(NULL);
				tmp = makeHeartbeat(Status::Set);
//				LOGD("心跳：%s",tmp.data.c_str());
				writeProtocol(tmp);//(tmp);
			}
			if(login_state == false)
			{
				if(time(NULL) - last_login_time >= 5)
				{
					last_login_time = time(NULL);
					tmp = makeLogin(Status::Set);
//					LOGD("login:%s",tmp.data.c_str());
					writeProtocol(tmp);
				}
			}
		}
		else
		{
			login_state = false;
			last_login_time = time(NULL);
		}
//		else
//		{
//
//
//			if(time(NULL) - last >= 60)
//			{
//				last = time(NULL);
////				tmp = makeDevInfo(dev.info,StatusSet);//(StatusOK,info);
////				writeProtocol(tmp);//(tmp);
//			}
//
//
//		}



		if (exitPending()) {
			return false;
		}

		Thread::sleep(100);
	}

	return false;
}
NetUserApp netUser;


