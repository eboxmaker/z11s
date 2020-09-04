/*
 * NetProtocolParser.cpp
 *
 *  Created on: 2020年4月12日
 *      Author: Administrator
 */

#include <vector>
#include <system/Mutex.h>
#include "netProtocolParser.h"
#include "netProtocolData.h"
#include "utils/Log.h"
#include "json/json.h"
static Mutex sLock;
static std::vector<OnNetProtocolDataUpdateFun> netProtocolDataUpdateListenerList;



void registerNetProtocolDataUpdateListener(OnNetProtocolDataUpdateFun pListener) {
	Mutex::Autolock _l(sLock);
//	LOGD("registerProtocolDataUpdateListener\n");
	if (pListener != NULL) {
		netProtocolDataUpdateListenerList.push_back(pListener);
	}
	LOGD("注册网络回调函数:size = %d\n",netProtocolDataUpdateListenerList.size());
}

void unregisterNetProtocolDataUpdateListener(OnNetProtocolDataUpdateFun pListener) {
	Mutex::Autolock _l(sLock);
//	LOGD("unregisterProtocolDataUpdateListener\n");
	if (pListener != NULL) {
		std::vector<OnNetProtocolDataUpdateFun>::iterator iter = netProtocolDataUpdateListenerList.begin();
		for (; iter != netProtocolDataUpdateListenerList.end(); iter++) {
			if ((*iter) == pListener) {
				netProtocolDataUpdateListenerList.erase(iter);
				return;
			}
		}
	}
}

void notifyNetProtocolDataUpdate(const NetProtocolData &data) {
	Mutex::Autolock _l(sLock);
	std::vector<OnNetProtocolDataUpdateFun>::const_iterator iter = netProtocolDataUpdateListenerList.begin();
	for (; iter != netProtocolDataUpdateListenerList.end(); iter++) {
		(*iter)(data);
	}
}


static bool jsonPreDeal(std::string &js,NetProtocolData &msg)
{
	Json::Reader reader;
	Json::Value root;
	Json::ValueType  item_type;

#if AESMD5_ENABLE

//	LOGD("执行AES解密");
	bool ret;

	ret = unPack(js, msg.data);
	LOGD("AES解析结果：%s",msg.data.c_str());
	if(ret){
		if (reader.parse(msg.data, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
		{
			  if(root.isMember("cmd"))
			  {
				  if(root["cmd"].type() == Json::stringValue)
				  {
					  msg.cmd = root["cmd"].asString();
				  }
				  else
				  {
					  LOGE(" cmd 类型错误");
				  }
			  }
			  else{
				  LOGE("不存在CMD");
				  return false;
			  }

			  if(root.isMember("status"))
			  {
				  if(root["status"].type() == Json::stringValue)
				  {
					  msg.status = root["status"].asString();
				  }
				  else
				  {
					  LOGE(" status 类型错误");
				  }
			  }
			  else{
				  LOGE("不存在 status");
				  return false;
			  }
			msg.err = 0;
			return true;
		}
		else
		{
			msg.cmd = Cmd::Unknown;
			msg.err = -1;
			msg.data = "";
		}
	}
	else
	{
		msg.cmd = Cmd::Unknown;
		msg.err = -1;
		msg.data = "";
	}
#else
//	LOGD("不执行AES解密");
	if (reader.parse(js, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
	{

		msg.cmd = (JsonCmd_t)root["cmd"].asInt();
		msg.status = (JsonStatus_t)root["status"].asInt();
		msg.err = 0;
		msg.data = js;
		return true;
	}
	else
	{
		msg.cmd = CMDUnkonw;
		msg.err = -1;
		msg.data = js;
	}
#endif



	return false;

}

bool parseNetProtocol(char *data,NetProtocolData &msg)
{

	bool ret;
	std::string str = data;
	//MD5  AES解析
	//解析命令和status
	LOGD("网络接收完成一帧数据");
	ret = jsonPreDeal(str,msg);
//	LOGD("msg.data:%s",msg.data.c_str());
	if(ret){
		LOGD("cmd=%s status=%s err=%d",msg.cmd.c_str(),msg.status.c_str(),msg.err);
		notifyNetProtocolDataUpdate(msg);
	}else{
		LOGE("cmd=%s status=%s err=%d",msg.cmd.c_str(),msg.status.c_str(),msg.err);
	}
    return ret;
}
int notifyProtocolDataTimeout(NetProtocolDataList &msg) {
	int cnt = 0;
	for (NetProtocolData *iter  = msg.begin(); iter != msg.end(); ) {
		notifyNetProtocolDataUpdate(*iter);

//		LOGD("删除：%d:cmd:%d,err = %d,status = %d,time = %d\n(%s)",\
//				cnt,(*iter).cmd, (*iter).err, (*iter).status,iter->time,iter->data.c_str());
		cnt++;
		iter++;
	}
    return cnt;
}

