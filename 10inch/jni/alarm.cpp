/*
 * alarm.cpp
 *
 *  Created on: 2019年5月13日
 *      Author: shentq
 */
#include "utils/TimeHelper.h"
#include "utils/log.h"
#include "alarm.h"
#include "plan.h"
#include "player.h"
namespace std {


AlarmClass::AlarmClass() {
	// TODO 自动生成的构造函数存根

}

AlarmClass::~AlarmClass() {
	// TODO 自动生成的析构函数存根
}

void AlarmClass::loop()
{
	bool ret;
	AlarmType type;
	char timeBuf[20];
	string timeStr;
	struct tm *t = TimeHelper::getDateTime();

	sprintf(timeBuf, "%02d:%02d",t->tm_hour, t->tm_min);
	timeStr = timeBuf;
	//LOGE("%s",timeStr);
	if(t->tm_sec <= 5){
		ret = checkAlarm(timeStr, type);
		if(ret == true){
			play(type);
		}
	}

}
void AlarmClass::syncPlan()
{
	AlarmNode_t node;
	LOGE("执行 syncPlan");
	int size = 0;
	alarmList.clear();
	LOGE("执行 1");
	for(int i = 0; i < gPlan.size();i++ )
	{
		LOGE("执行i = %d",i);

		node.time = gPlan.row[i].startTime;
		node.alarmType = AlarmType::OnClass;
		node.alarmTypeStr = "上课";
		alarmList.push_back(node);
		node.time = gPlan.row[i].endTime;
		node.alarmType = AlarmType::OffClass;
		node.alarmTypeStr = "下课";
		alarmList.push_back(node);
	}
	for(int i = 0; i < size; i++)
	{
		LOGE("TIME:%s,type:%d",alarmList[i].time.c_str(),alarmList[i].alarmType);
	}
}
bool AlarmClass::checkAlarm(string timeStr,AlarmType &type)
{
	type = AlarmType::None;
	for(int i = 0; i < alarmList.size(); i++)
	{
		if(timeStr == alarmList[i].time)
		{
			type =  alarmList[i].alarmType;
			return true;
		}
	}
	return false;
}
void AlarmClass::play(AlarmType type)
{
	switch(type)
	{
	case AlarmType::OnClass:
		if (!sIsPlayOK) {
			sPlayer.play("/mnt/extsd/success.mp3");
		} else {
			sPlayer.resume();
		}
		break;
	case AlarmType::OffClass:
		if (!sIsPlayOK) {
			sPlayer.play("/mnt/extsd/success.mp3");
		} else {
			sPlayer.resume();
		}
		break;
	case AlarmType::Arrangement:
		if (!sIsPlayOK) {
			sPlayer.play("/mnt/extsd/success.mp3");
		} else {
			sPlayer.resume();
		}
		break;
	}
}
void AlarmClass::onPlayerMessage(ZKMediaPlayer *pMediaPlayer, int msg, void *pMsgData)
{
	switch (msg) {
	case ZKMediaPlayer::E_MSGTYPE_ERROR_INVALID_FILEPATH:
	case ZKMediaPlayer::E_MSGTYPE_ERROR_MEDIA_ERROR:
		// 出错消息
		LOGD("ERR");
		sIsPlayOK = false;
		break;

	case ZKMediaPlayer::E_MSGTYPE_PLAY_STARTED:
		// 开始播放消息
		LOGD("NEW START");
		sIsPlayOK = true;
		break;

	case ZKMediaPlayer::E_MSGTYPE_PLAY_COMPLETED:
		// 播放结束消息
		LOGD("NEW END");
	sIsPlayOK = false;
		break;
	}
}
AlarmClass myAlarm;
} /* namespace std */
