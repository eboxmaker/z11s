/*
 * globalVar.cpp
 *
 *  Created on: 2018年12月26日
 *      Author: shentq
 */
#include "global.h"

#include <sys/reboot.h>
#include "utils/TimeHelper.h"
#include "httpDownload.h"
#include "utils/Log.h"

#include "json_manager.h"
#include "lib/fileOpt.h"
#include "door.h"
#include "plan.h"
#include "ad.h"
#include "alarm.h"


bool isShowKeyboard = true;


SocketClient* gSocket= new SocketClient();


long gKeyboardLastActionTime = 0;
Person gPerson;
PersonTrans_t gPersonTrans;
CourseInfo_t gCourseInfo;

string gBroadcastMsg;



Device dev;

myNotify_t keyboardCallback;
myNotify_t AdvertisementCallback;
myNotify_t networkTestCallback;
myNotify_t settingsCallback;
myNotify_t PersonCallback;

void exeCMD(char *ptr)
{
	string js;
	js = ptr;
	exeCMD(js);
}
void exeCMD(string &package)
{
	HttpInfo_t info;

	string fileName = "";
	string msg;
	string dataout;
	string ack ;
	DevicePara_t tempDevPara;

	int fingers_size = 0;

	int counter =0;
	bool ret = false;
	JsonStatus_t status = StatusErr;
	JsonCmd_t cmd = CMDErr;
	int cStatus = -1;
	msg = "";
	char msgBuf[50];
	string js;
	int level;
	int num;
	if(package == "triggerTimeout")
	{
		//LOGE("发出超时通知");
		if(networkTestCallback != NULL)
			networkTestCallback(CMDTimeout,status,msg);
		if(keyboardCallback != NULL)
			keyboardCallback(CMDTimeout,status,msg);
		if(settingsCallback != NULL)
			settingsCallback(CMDTimeout,status,msg);
		if(AdvertisementCallback != NULL)
			AdvertisementCallback(CMDTimeout,status,msg);
		if(PersonCallback != NULL)
			PersonCallback(CMDTimeout,status,msg);
		return;
	}
	else
	{
		ret = jm.unPack(package, js);;
	}
	if(ret == true)
	{

		cmd = getJsonCMD(js);
		LOGE("CMD:%d",cmd);
		switch(cmd)
		{
		case CMDHeartbeat:
//			LOGE("CMDHeartbeat:%d",cmd);
			status = jm.parseHeartbeat(js,msg);
			if(status == StatusSet || status == StatusGet)
			{
				ack = jm.makeHeartbeat(StatusOK);
				gSocket->write_(ack);
			}

			break;
		case CMDSetHeartbeat:
			int tempInterval;
			status = jm.parseSetHeartbeat(js,tempInterval);
			if(status == StatusSet)
			{
				dev.set_heartbeatInterval(tempInterval);
				ack = jm.makeSetHeartbeat(dev.get_heartbeatInterval(), StatusOK);
				gSocket->write_(ack);
			}
			if(status == StatusGet)
			{
				ack = jm.makeSetHeartbeat(dev.get_heartbeatInterval(), StatusOK);
				gSocket->write_(ack);
			}
			break;
		case CMDRegister:
			cStatus = jm.parseRegister(js,tempDevPara,msg);
			//LOGE("%s",js.c_str());
			if(cStatus == StatusParaSer2Dev)
			{
				if(tempDevPara.id == dev.id)
				{
					//LOGE("服务器匹配设备正确！");
					//更新四个参数
					TimeHelper::setDateTime(msg.c_str());
					dev.set_heartbeatInterval(tempDevPara.heartbeatInterval);
					dev.set_organization(tempDevPara.organization);
					dev.set_name(tempDevPara.name);


				    ack = jm.makeRegister(dev,StatusAckDev2Ser );
					gSocket->write_(ack);
					//LOGE("回复:%s:%s",dev.organization.c_str(),dev.name.c_str());

				}
				else
				{
					dev.confirmState = StatusErrSer2Dev;
					LOGE("服务器匹配设备ID错误！");

				}

			}
			else if(cStatus == StatusOKSer2Dev)
			{
				dev.confirmState = true;
			}
			else
			{

			}
			break;
		case CMDOrgName:
			status = jm.parseOrgName(js,msg);
			if(status == StatusSet)
			{
				dev.set_organization(msg);
				msg = dev.get_organization();

				ack = jm.makeOrgName(msg, StatusOK);
				gSocket->write_(ack);
			}
			else if(status == StatusGet)
			{
				msg = dev.get_organization();

				ack = jm.makeOrgName(msg, StatusOK);
				gSocket->write_(ack);
			} else if(status == StatusOK)
			{
				dev.set_organization(msg);

			}
			break;
		case CMDDevName:
			status = jm.parseDevName(js,msg);
			if(status == StatusSet)
			{

				dev.set_name(msg);
				msg = dev.get_name();

				ack = jm.makeDevName(msg, StatusOK);
				gSocket->write_(ack);
			}
			else if(status == StatusGet)
			{
				msg = dev.get_name();

				ack = jm.makeDevName( msg, StatusOK);
				gSocket->write_(ack);
			}
			break;
		case CMDDevID:
			status = jm.parseDevID(js);
			if(status == StatusSet || status == StatusGet)
			{
				//LOGE("回复:%s",gDevID.c_str());
				ack = jm.makeDevID(dev.id, StatusOK);
				gSocket->write_(ack);
			}
			break;
		case CMDLocalPassword:
			status = jm.parseLocalPwd(js,msg);
			if(status == StatusSet)
			{
				dev.set_pwdLocal(msg);
				msg = dev.get_pwdLocal();
				ack = jm.makeLocalPwd(msg,StatusOK);
				gSocket->write_(ack);
			}
			else if(status == StatusGet)
			{
				msg = dev.get_pwdLocal();

				ack = jm.makeLocalPwd(msg,StatusOK);
				gSocket->write_(ack);
			}
			break;
		case CMDFingerKey:
			status = jm.parseFingerKey(js);
			if(status == StatusOK)
			{

			}
			break;
		case CMDDoorLockControl:
			DoorLockState_t tempDoorLockState;
			status = jm.parseDoorCtr(js,tempDoorLockState);
			if(status == StatusSet )
			{
				if(tempDoorLockState == Unlock)
				{
					msg = "unlock";
					door.set_lock_ctr(Unlock);
				}
				else
				{
					msg = "lock";
					door.set_lock_ctr(Lock);
				}
//				tempDoorLockState = door.get_lock_state();;
				ack = jm.makeDoorCtr(tempDoorLockState, StatusOK);
				gSocket->write_(ack);
			}
//			else if(status == StatusRead)
//			{
//				tempDoorLockState = door.get_lock_state();
//				ack = jm.makeDoorCtr(tempDoorLockState, StatusOK);
//				gSocket->write_(ack);
//			}
			//应该触发一个定时器，两秒之后返回该值

			break;
		case CMDDoorState:
			DoorState_t tempDoorState;
			status = jm.parseDoorState(js);
			if(status == StatusGet)
			{
				tempDoorState = door.get_state();
				ack = jm.makeDoorState(tempDoorState, StatusOK);
				gSocket->write_(ack);
			}

			break;
		case CMDQRCode:
			status = jm.parseFile(js,QR_DIR,msg,dataout);
			ack = jm.makeQRCodeAck(msg,StatusErr);
			if(status == StatusSet || status == StatusGet)
			{
				if(creat_file(msg,dataout.c_str(),dataout.size()))
					ack = jm.makeQRCodeAck(msg,StatusOK);
			}
			gSocket->write_(ack);
			LOGE("接收到二维码!%d:%s\n",status,msg.c_str());
			break;
		case CMDDelQRCode:
			status = jm.parseDeleteFile(js,QR_DIR,fileName,msg);
			if(status == StatusSet || status == StatusGet)
			{
				rm_file(msg);
				ack = jm.makeDeleteFile(msg,StatusOK);
				gSocket->write_(ack);
			}
			else if(status == StatusErr)
			{
				ack = jm.makeQRCodeAck(msg,StatusErr);
				gSocket->write_(ack);
			}
			break;
		case CMDAdAdd:
			status = jm.parseAdAdd(js,msg);

			if(status == StatusSet || status == StatusGet)
			{
				if(gAdv.add(js))
				{
					ack = jm.makeAdAdd(msg,StatusOK);
				}
				else
				{
					ack = jm.makeAdAdd(msg,StatusErr);
				}
			}

			gSocket->write_(ack);
			break;
		case CMDAdRead:
			status = jm.parseAdRead(js);
			if(status == StatusSet || status == StatusGet)
			{

				ack = jm.makeAdRead(gAdv,StatusOK);
				gSocket->write_(ack);

			}
			break;
		case CMDAdDel:
			status = jm.parseAdDelet(js,fileName);
			if(status == StatusSet || status == StatusGet)
			{
				gAdv.remove(fileName);
				ack = jm.makeDeleteFile(fileName,StatusOK);
				gSocket->write_(ack);
			}
			else if(status == StatusErr)
			{
				gSocket->write_(ack);
			}
			break;
		case CMDAdClear:
			status = jm.parseAdClear(js);//(js,AD_DIR,fileName,msg);
			if(status == StatusSet || status == StatusGet)
			{
				gAdv.clear();
				ack = jm.makeAdClear(StatusOK);
				gSocket->write_(ack);
			}
			else if(status == StatusErr)
			{
				ack = jm.makeAdClear(StatusErr);
				gSocket->write_(ack);
			}
			gAdv.logDBList();
			gAdv.logFileList();
			//LOGO("")
			break;
		case CMDAdSet:
			status = jm.parseAdSet(js,gAdv);
			if(status == StatusSet)
			{
				ack = jm.makeAdSet(gAdv, StatusOK);
				gSocket->write_(ack);
			}
			break;

		case CMDDoorPassword:
			status = jm.parseDoorPwd(js, msg);
			//下位机不存储开门密码
//			if(status == StatusSet)
//			{
//				gDoorPwd = msg;
//			}
//			ack = jm.makeDoorPwd(gDoorPwd, StatusOK);
//			gSocket->write_(ack);
			break;
		case CMDSyncDateTime:
			status = jm.parseSyncDateTime(js, msg);
			if(status == StatusSet)
			{
				TimeHelper::setDateTime(msg.c_str());
				ack = jm.makeSyncDateTime(msg, StatusOK);
				gSocket->write_(ack);
			}
			else if(status == StatusGet)
			{

			}
			else if(status == StatusOK)
			{
				TimeHelper::setDateTime(msg.c_str());
			}
			//回复

			break;


		case CMDPlan:
			LOGE("CMD:CMDPlan");
			status = jm.parsePlan(js, gPlan);
			if(status == StatusSet)
			{
				string str = jm.makePlan(StatusOK);
				myAlarm.syncPlan();
				gSocket->write_(str);
			}
			break;
		case CMDBroadcast:
			status = jm.parseBroadcast(js, msg);
			if(status == StatusSet)
			{
				gBroadcastMsg = msg;
			}
			else if(status == StatusGet)
			{

			}
			ack = jm.makeBroadcast(gBroadcastMsg, StatusOK);
			gSocket->write_(ack);
			break;


		case CMDCourseInfo:
			LOGE("CMD:CMDCourseInfo");
			status = jm.parseCourseInfo(js, gCourseInfo);
			if(status == StatusSet)
			{
				msg = PIC_DIR + gCourseInfo.picture.name;
				if(creat_file(msg,gCourseInfo.picture.data.c_str(),gCourseInfo.picture.data.size()))
				{
					ack = jm.makeCourseInfo(gCourseInfo,StatusOK);
					gSocket->write_(ack);
				}
			}
			//LOGE("CMD:CMDCourseInfo:s=%d",status);
			//LOGE("%s，%s",gCourseInfo.name.c_str(),gCourseInfo.course.c_str());

			break;

		case CMDPersonAdd:
//			LOGD("收到person命令：");
			status = jm.parsePersonAdd(js, gPersonTrans);
			if(keyboardCallback != NULL)
				keyboardCallback(cmd,status,msg);
			if(status == StatusOK)
			{
				msg = PIC_DIR + gPersonTrans.picture.name;
				creat_file(msg,gPersonTrans.picture.data.c_str(),gPersonTrans.picture.data.size());
				gPersonTrans.picture.data = "";
				//LOGE("%s，%s",gPersonDump.name.c_str(),gPersonDump.course.c_str());

			}
			else if(status == StatusSet)
			{
				gPerson.add(gPersonTrans);
				msg = PIC_DIR + gPersonTrans.picture.name;
				creat_file(msg,gPersonTrans.picture.data.c_str(),gPersonTrans.picture.data.size());
				gPersonTrans.picture.data = "";

				ack = jm.makePersonAdd(gPersonTrans, StatusOK);
				gSocket->write_(ack);
			}
			break;

		case CMDPersonDel:
			LOGD("收到personDel命令：");
			LOGD("数据：%s",js.c_str());
			status = jm.parsePersonDel(js);
			if(status == StatusOK || status == StatusSet)
			{
				ack = jm.makePersonDel(status);
				gSocket->write_(ack);
			}
			break;

		case CMDPersonByLevel:
			status = jm.parsePersonGetByLevel(js,&level,&num);
			LOGD("收到接收人员命令：level：%d，num：%d",level,num);
			if(status == StatusOK)
			{

			}
			else if(status == StatusSet || status == StatusGet)
			{
				int num = gPerson.size(level);
				ack = jm.makePersonGetByLevel(level,num,StatusOK);
				gSocket->write_(ack);
			}
			break;
		case CMDFingerGet:
			LOGD("收到FingerGet");
			status = jm.parseFingerGet(js, gPersonTrans);
			if(status == StatusOK)
			{
				uint16_t id;
//				gPersonTrans.picture.name += ".jpg";
				msg = PIC_DIR + gPersonTrans.picture.name;
				creat_file(msg,gPersonTrans.picture.data.c_str(),gPersonTrans.picture.data.size());
				gPersonTrans.picture.data = "";
				for(int i = 0; i < gPersonTrans.fingers.size(); i++)
				{
					if(finger.add_featurs_sync(&id, gPersonTrans.fingers[i]))
						LOGD("添加临时成功");
					else
						LOGD("添加临时失败");
				}
			}
			break;
		case CMDFingerSet:
			LOGD("收到FingerSet");
			status = jm.parseFingerSet(js,&fingers_size);
			if(status == StatusOK)
			{
				LOGD("服务器回复指纹数量：%d",fingers_size);
			}
			break;
		case CMDVersion:
			status = jm.parseVersion(js);
			if(status == StatusGet)
			{
				ack = jm.makeVersion(StatusOK);
				gSocket->write_(ack);
			}
			break;
		case CMDUpdate:
			status = jm.parseUpdate(js,info);
			if(status == StatusSet)
			{
			    string filename = info.url.substr(info.url.find_last_of('/') + 1);
				msg = filename;
			    if(downloadThread.isRunning())
				{
					ack = jm.makeUpdate(info,StatusErr);
					gSocket->write_(ack);
				}
				else
				{
					ack = jm.makeUpdate(info,StatusOK);
					gSocket->write_(ack);
					downloadThread.settings(info.url,info.port,"/mnt/extsd/temp",filename);
				    downloadThread.run("download-file");
				}
			}
			else if( status == StatusOK)
			{
			    string filename = info.url.substr(info.url.find_last_of('/') + 1);
				msg = filename;
			    downloadThread.settings(info.url,info.port,"/mnt/extsd/temp",filename);
			    downloadThread.run("download-update");
			}
			break;
		case CMDReboot:
			status = jm.parseReboot(js);
			if(status == StatusSet)
			{
				ack = jm.makeReboot(StatusOK);
				gSocket->write_(ack);
				Thread::sleep(2000);
			    reboot(RB_AUTOBOOT);
			}
			break;
		default:
			break;
		}
		if(networkTestCallback != NULL)
			networkTestCallback(cmd,status,msg);
		if(keyboardCallback != NULL && cmd != CMDPersonAdd)//person 命令提前触发了
			keyboardCallback(cmd,status,msg);
		if(settingsCallback != NULL)
			settingsCallback(cmd,status,msg);
		if(AdvertisementCallback != NULL)
			AdvertisementCallback(cmd,status,msg);
		if(PersonCallback != NULL)
			PersonCallback(cmd,status,msg);

	}
}

