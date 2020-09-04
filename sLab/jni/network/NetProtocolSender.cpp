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
int writeProtocol_NoLock(NetProtocolData data);

NetProtocolDataList msgList ;
void printMsgList()
{
	int i = 0;
	for (NetProtocolData *iter  = msgList.begin(); iter != msgList.end();iter++ )
	{
		i++;
		LOGD("%d:cmd:%S,err = %d,status = %s,time = %d\n(%s)",\
			i,(*iter).cmd.c_str(), (*iter).err, (*iter).status.c_str(),iter->time,iter->data.c_str());
	}
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
int getNetProtocolDataTimeout(NetProtocolDataList *timeout_list)
{
	Mutex::Autolock _l(msgListLock);
	int cnt = 0;
	timeout_list->clear();
//	printMsgList();
	for (NetProtocolData *iter  = msgList.begin(); iter != msgList.end(); ) {
		if(time(NULL) - (*iter).time >= 5)
		{
			(*iter).err = -1;
			timeout_list->push_back((*iter));
			if((*iter).retryTimes > 1)//需要重发的消息继续重发
			{
				LOGE("%s消息失败，重发%d\n%s\n",(*iter).cmd.c_str(),(*iter).retryTimes,iter->data.c_str());
				(*iter).retryTimes -= 1;
				writeProtocol_NoLock((*iter));
			}
			iter = msgList.erase(iter);
			cnt++;
			break;
		}else{
			iter++;
		}
	}
	return cnt;
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
		LOGD("====消息队列数量：%d====",msgList.size());
		for(int i = 0; i < msgList.size(); i++)
		{
			LOGD("%s,%s,retry:%d",msgList[i].cmd.c_str(),msgList[i].status.c_str(),msgList[i].retryTimes);
		}
	}
#if AESMD5_ENABLE
	pack(data);
#endif
	return NETCONTEXT->Write(data.data);

}

int writeProtocol_NoLock(NetProtocolData data)
{
	if(!NETCONTEXT->connected()){
		return -1;
	}

	data.time = time(NULL);
	data.err = 0;

	if(data.status == Status::Set || data.status == Status::Get)
	{
		msgList.push_back(data);
		LOGD("====消息队列数量：%d====",msgList.size());
		for(int i = 0; i < msgList.size(); i++)
		{
			LOGD("%s",msgList[i].cmd.c_str());
		}
	}
#if AESMD5_ENABLE
	pack(data);
#endif
	return NETCONTEXT->Write(data.data);

}

