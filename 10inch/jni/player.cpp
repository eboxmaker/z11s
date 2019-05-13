/*
 * player.cpp
 *
 *  Created on: 2019年5月13日
 *      Author: shentq
 */
#include "player.h"
#include "utils/log.h"

bool sIsPlayOK = false;
void PlayerMessageListener::onPlayerMessage(ZKMediaPlayer *pMediaPlayer, int msg, void *pMsgData) {
	switch (msg) {
	case ZKMediaPlayer::E_MSGTYPE_ERROR_INVALID_FILEPATH:
	case ZKMediaPlayer::E_MSGTYPE_ERROR_MEDIA_ERROR:
		// 出错消息
		LOGD("ERR");
		sIsPlayOK = false;
		break;

	case ZKMediaPlayer::E_MSGTYPE_PLAY_STARTED:
		// 开始播放消息
		LOGD("START");
		sIsPlayOK = true;
		break;

	case ZKMediaPlayer::E_MSGTYPE_PLAY_COMPLETED:
		// 播放结束消息
		LOGD("END");
	sIsPlayOK = false;
		break;
	}
}
PlayerMessageListener sPlayerMessageListener;
ZKMediaPlayer sPlayer(ZKMediaPlayer::E_MEDIA_TYPE_AUDIO);


