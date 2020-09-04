/*
 * NetCallback.h
 *
 *  Created on: 2020年4月13日
 *      Author: Administrator
 */

#ifndef JNI_NETLOGINTASK_H_
#define JNI_NETLOGINTASK_H_
#include "system/thread.h"
#include "network/netContext.h"

class NetUserApp : public Thread {
public:
	virtual NetUserApp();
	virtual ~NetUserApp();

	void begin();
	void login_state_set(bool state);
	bool login_state_get();
	int write(NetProtocolData &data);
protected:
	virtual bool readyToRun();
	virtual bool threadLoop();
private:
	bool login_state;

};
extern NetUserApp netUser;

#endif /* JNI_NETCALLBACK_H_ */
