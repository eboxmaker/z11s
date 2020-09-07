/*
 * NetProtocolSender.cpp
 *
 *  Created on: 2020年4月12日
 *      Author: Administrator
 */
#include "NetProtocolSender.h"
#include <system/Mutex.h>
#include "utils/Log.h"
#include "netContext.h"
#include <vector>

static Mutex msgListLock;

NetProtocolDataList	msgList ;
void printMsgList()
{
	int i = 0;
	LOGD("=======消息队列数量：%d==========",msgList.size());
	for(int i = 0; i < msgList.size(); i++)
	{
		LOGD("%d:%s,%s,retry:%d",i,msgList[i].cmd.c_str(),msgList[i].status.c_str(),msgList[i].retryTimes);
	}
	LOGD("======================",msgList.size());
}
bool deletDataFromList(NetProtocolData &data)
{
	Mutex::Autolock _l(msgListLock);

	if(data.status == Status::OK || data.status == Status::Err){
		for (NetProtocolData *iter  = msgList.begin(); iter != msgList.end(); )
		{
			if((*iter).cmd == data.cmd)
			{
				iter = msgList.erase(iter);
//				LOGD("删除1条命令成功，等待回复的命令还有%d条",msgList.size());
//				LOGD("共有%d条数据，但是没有找到要删除的数据CMD:%d,stuts:%d",msgList.size(),data.cmd,data.status);
				return true;
				break;
			}
			else
			{
				iter++;
			}
		}
//		for(int i = 0; i < msgList.size(); i++)
//		{
//			if(msgList[i].cmd == data.cmd)
//			{
//				msgList.erase(&msgList[i]);
//			}
//		}
//		LOGD("共有%d条数据，但是没有找到要删除的数据CMD:%s,stuts:%s",msgList.size(),data.cmd.c_str(),data.status.c_str());
//		LOGD("接收到的：CMD:%s,stuts:%s",data.cmd.c_str(),data.status.c_str());
//		LOGD("接收到的：CMD:%s,stuts:%s",msgList[0].cmd,msgList[0].status);
		printMsgList();
	}
	else
	{
//		LOGD("收到需要执行的命令");
	}
	return false;
}

int writeProtocol(NetProtocolData data)
{
	Mutex::Autolock _l(msgListLock);
	if(!NETCONTEXT->connected()){
		return -1;
	}

	data.time = time(NULL);
	data.err = 0;

	if(data.status == Status::Set || data.status == Status::Get)
	{
		msgList.push_back(data);
		printMsgList();
	}
#if AESMD5_ENABLE
	pack(data);
#endif
	return NETCONTEXT->Write(data.data);
}

static int writeProtocol_NoLock(NetProtocolData data)
{
	if(!NETCONTEXT->connected()){
		return -1;
	}

	data.time = time(NULL);
	data.err = 0;

	if(data.status == Status::Set || data.status == Status::Get)
	{
		msgList.push_back(data);
		printMsgList();
	}
#if AESMD5_ENABLE
	pack(data);
#endif
	return NETCONTEXT->Write(data.data);

}

void tx_loop()
{
	Mutex::Autolock _l(msgListLock);
	int cnt = 0;
	for (NetProtocolData *iter  = msgList.begin(); iter != msgList.end(); ) {
		if(time(NULL) - (*iter).time >= 5)
		{
			(*iter).err = -1;
			if((*iter).retryTimes >= 1)//需要重发的消息继续重发
			{
				LOGE("%s消息失败，重发%d\n%s\n",(*iter).cmd.c_str(),(*iter).retryTimes,iter->data.c_str());
				(*iter).retryTimes -= 1;
				writeProtocol_NoLock((*iter));
			}
			notifyNetProtocolDataUpdate(*iter);
			iter = msgList.erase(iter);
			cnt++;
			break;
		}else{
			iter++;
		}
	}
}


