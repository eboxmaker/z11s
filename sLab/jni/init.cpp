/*
 * init.cpp
 *
 *  Created on: 2020年8月27日
 *      Author: shentq
 */

#include "init.h"
#include "device.h"
#include "lib/fileopt.h"

#include "netUser/netLoginTask.h"

void init()
{

	LOGD("==============用户系统初始化=============");
	dev.load();
//    gAdv.load();

    make_dir(PIC_DIR);
    make_dir(QR_DIR);
    make_dir(AD_DIR);
//    make_dir(DIR_TEMP);

    NETCONTEXT->begin(dev.para.serverIP, dev.para.serverPort);

	if(!netUser.isRunning())
	{
	    netUser.run("NetUserTask");
	}
}
