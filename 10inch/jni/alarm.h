/*
 * alarm.h
 *
 *  Created on: 2019年5月13日
 *      Author: shentq
 */

#ifndef JNI_ALARM_H_
#define JNI_ALARM_H_
#include "objectType.h"
#include "enum_def.h"
#include "media/ZKMediaPlayer.h"

namespace std {

DECLARE_ENUM(AlarmType)
	None 	 = 0,
	OnClass 	,
    OffClass	,
	Arrangement	,
END_ENUM()

typedef struct {
	string time;
	AlarmType alarmType;
	string alarmTypeStr;
}AlarmNode_t;

typedef std::vector<AlarmNode_t> AlarmList_t;

class AlarmClass: public ZKMediaPlayer::IPlayerMessageListener {
public:
	AlarmClass();
	virtual ~AlarmClass();

	void loop();
	void syncPlan();
	bool checkAlarm(string timeStr,AlarmType &type);
	void play(AlarmType type);

	AlarmList_t alarmList;


	public:
	    virtual void onPlayerMessage(ZKMediaPlayer *pMediaPlayer, int msg, void *pMsgData) ;


};
extern AlarmClass myAlarm;

} /* namespace std */

#endif /* JNI_ALARM_H_ */
