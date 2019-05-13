/*
 * player.h
 *
 *  Created on: 2019年5月13日
 *      Author: shentq
 */

#ifndef JNI_PLAYER_H_
#define JNI_PLAYER_H_

#include "media/ZKMediaPlayer.h"


class PlayerMessageListener : public ZKMediaPlayer::IPlayerMessageListener {
public:
    virtual void onPlayerMessage(ZKMediaPlayer *pMediaPlayer, int msg, void *pMsgData) ;
};

extern PlayerMessageListener sPlayerMessageListener;
extern ZKMediaPlayer sPlayer;
extern bool sIsPlayOK;


#endif /* JNI_PLAYER_H_ */
