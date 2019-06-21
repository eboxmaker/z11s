#pragma once

#include "utils/BrightnessHelper.h"
#include "utils/TimeHelper.h"
#include "storage/StoragePreferences.h"
#include "uart/ProtocolSender.h"

#include "lib/itoa.h"
#include <sys/sysinfo.h>

#include "../global.h"
#include "json_manager.h"
#include "httpdownload.h"
#include "door.h"

/*
*此文件由GUI工具生成
*文件功能：用于处理用户的逻辑相应代码
*功能说明：
*========================onButtonClick_XXXX
当页面中的按键按下后系统会调用对应的函数，XXX代表GUI工具里面的[ID值]名称，
如Button1,当返回值为false的时候系统将不再处理这个按键，返回true的时候系统将会继续处理此按键。比如SYS_BACK.
*========================onSlideWindowItemClick_XXXX(int index) 
当页面中存在滑动窗口并且用户点击了滑动窗口的图标后系统会调用此函数,XXX代表GUI工具里面的[ID值]名称，
如slideWindow1;index 代表按下图标的偏移值
*========================onSeekBarChange_XXXX(int progress) 
当页面中存在滑动条并且用户改变了进度后系统会调用此函数,XXX代表GUI工具里面的[ID值]名称，
如SeekBar1;progress 代表当前的进度值
*========================ogetListItemCount_XXXX() 
当页面中存在滑动列表的时候，更新的时候系统会调用此接口获取列表的总数目,XXX代表GUI工具里面的[ID值]名称，
如List1;返回值为当前列表的总条数
*========================oobtainListItemData_XXXX(ZKListView::ZKListItem *pListItem, int index)
 当页面中存在滑动列表的时候，更新的时候系统会调用此接口获取列表当前条目下的内容信息,XXX代表GUI工具里面的[ID值]名称，
如List1;pListItem 是贴图中的单条目对象，index是列表总目的偏移量。具体见函数说明
*========================常用接口===============
*LOGD(...)  打印调试信息的接口
*mTextXXXPtr->setText("****") 在控件TextXXX上显示文字****
*mButton1Ptr->setSelected(true); 将控件mButton1设置为选中模式，图片会切换成选中图片，按钮文字会切换为选中后的颜色
*mSeekBarPtr->setProgress(12) 在控件mSeekBar上将进度调整到12
*mListView1Ptr->refreshListView() 让mListView1 重新刷新，当列表数据变化后调用
*mDashbroadView1Ptr->setTargetAngle(120) 在控件mDashbroadView1上指针显示角度调整到120度
*
* 在Eclipse编辑器中  使用 “alt + /”  快捷键可以打开智能提示
*/

static void updateAdSetWind()
{

	if(gAdv.get_enable() == true)
	{
		mBtnAdEnablePtr->setBackgroundPic("kai.png"); // @suppress("Symbol is not resolved")
	}
	else
	{
		mBtnAdEnablePtr->setBackgroundPic("guan.png");
	}

	mEditDisplayAdAfterTimePtr->setText(gAdv.get_idleTime());

}


static void updateDisp()
{
	int interval = 0;
	string org,name;
	string serverIP;
	int serverPort;

    serverIP = StoragePreferences::getString("dev.serverIP", "192.168.1.1");
    serverPort = StoragePreferences::getInt("dev.serverPort", 6000);
    org = StoragePreferences::getString("dev.organization","none");
	name = StoragePreferences::getString("dev.name","none");
	interval = StoragePreferences::getInt("dev.heartbeatInterval", 5);


    mEditTextServerIPPtr->setText(serverIP.c_str());
    mEditTextServerPortPtr->setText(serverPort);
    mEditOrgNamePtr->setText(org);
	mEditDevNamePtr->setText(name);
	mEditHeartbeatPtr->setText(interval);
	mTextVersionPtr->setText(dev.version);
	mTextIDPtr->setText(dev.id);

}
static void onDownloadEvent(string &msg)
{
	mWindStatusNoticePtr->showWnd();
	mTextStatusNotice2Ptr->setText("");
	if(msg.empty())
	{
		mTextStatusNoticePtr->setText("下载成功");
	}
	else
	{
		mTextStatusNoticePtr->setText("下载失败");
		mTextStatusNotice2Ptr->setText(msg);
	}
}
//网络数据回调接口
static void onNetWrokDataUpdate(JsonCmd_t cmd, JsonStatus_t status, string &msg)
{
//	mTextStatusNotice2Ptr->setText("");
	switch(cmd)
	{
	case CMDSetHeartbeat:
	case CMDLocalPwd:
	case CMDSyncDateTime:
	case CMDAdSet:
	case CMDOrgName:
	case CMDDevName:
		mTextStatusNotice2Ptr->setText("");
		mWindStatusNoticePtr->showWnd();
		if(status == StatusSet)
		{
			mTextStatusNoticePtr->setText("响应服务器设置");
			updateAdSetWind();
		}
		else if(status == StatusOK)
		{
			gSocket->disableTriger();
			mTextStatusNoticePtr->setText("服务器同步成功");
			updateDisp();
		}
		sleep(1);
		mWindStatusNoticePtr->hideWnd();
		break;
	case CMDUpdate:
		mWindStatusNoticePtr->showWnd();
		mTextStatusNotice2Ptr->setText("开始下载文件...");
		if(status == StatusSet)
		{
			mTextStatusNoticePtr->setText("获得更新路径成功");
		}
		else if(status == StatusOK)
		{
			gSocket->disableTriger();
			mTextStatusNoticePtr->setText("获得更新路径成功");
			updateDisp();
		}
		break;
	case CMDAdAdd:
	case CMDAdDel:
	case CMDAdClear:
		mEditAdNumPtr->setText(gAdv.getNum());
		break;
	case 255:
		mWindStatusNoticePtr->showWnd();
		mTextStatusNoticePtr->setText("服务器超时!!!");
		mTextStatusNotice2Ptr->setText("");
		sleep(1);
		mWindStatusNoticePtr->hideWnd();

		break;

	}

}

/**
 * 注册定时器
 * 填充数组用于注册定时器
 * 注意：id不能重复
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	{0,  1000}, //定时器id=0, 时间间隔6秒
	{1,  3000},
//	{10, GO_HOME_TIME},
};

/**
 * 当界面构造时触发
 */
static void onUI_init(){
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");
	settingsCallback = onNetWrokDataUpdate;
	downloadEvent = onDownloadEvent;
}

/**
 * 当切换到该界面时触发
 */
static void onUI_intent(const Intent *intentPtr) {
    if (intentPtr != NULL) {
        //TODO
    }
}

/*
 * 当界面显示时触发
 */
static void onUI_show() {
    EASYUICONTEXT->showStatusBar();
    mWindLocalPwdPtr->hideWnd();
    mWindAdSetPtr->hideWnd();
    updateDisp();

	if(dev.get_enable() == true)
		mBtnDevEnablePtr->setBackgroundPic("kai.png");
	else
		mBtnDevEnablePtr->setBackgroundPic("guan.png");


	if(gSocket->connected())
		mBtnServerStatePtr->setBackgroundPic("kai.png");
	else
		mBtnServerStatePtr->setBackgroundPic("guan.png");


	//
	mSeekbarLightPtr->setProgress(BRIGHTNESSHELPER->getBrightness());
	mTextLightPtr->setText(BRIGHTNESSHELPER->getBrightness());
	mSeekbarVolumePtr->setProgress(dev.get_volume());
	mTextVolumePtr->setText(dev.get_volume());

//	mSeekbarMemUsagePtr->setProgress(gMemUsage);
//	sprintf(temp,"%0.1f%%",gMemUsage);
//	mTextMemUsagePtr->setText(temp);
}

/*
 * 当界面隐藏时触发
 */
static void onUI_hide() {
	EASYUICONTEXT->hideStatusBar();
	LOGD("隐藏settings");
}

/*
 * 当界面完全退出时触发
 */
static void onUI_quit() {
	settingsCallback = NULL;
	downloadEvent = NULL;
	LOGD("注销settings");

}

/**
 * 串口数据回调接口
 */
static void onProtocolDataUpdate(const SProtocolData &data) {

}

/**
 * 定时器触发函数
 * 不建议在此函数中写耗时操作，否则将影响UI刷新
 * 参数： id
 *         当前所触发定时器的id，与注册时的id相同
 * 返回值: true
 *             继续运行当前定时器
 *         false
 *             停止运行当前定时器
 */

static bool onUI_Timer(int id){

	struct sysinfo systemInfo;
	float memUsage;
	switch (id) {
	case 0:
	     sysinfo(&systemInfo);
	     char temp[30];
	     memUsage = (1 - ((float)systemInfo.freeram/(float)systemInfo.totalram))*100;
	     sprintf(temp,"%0.1f%%(%0.1fM/%0.1fM)",memUsage,\
	    		 systemInfo.freeram/1024.0/1024.0,\
				 systemInfo.totalram/1024.0/1024.0);
	     mSeekbarMemUsagePtr->setProgress(memUsage);
	     mTextMemUsagePtr->setText(temp);
	     break;
	case 1:
		if(dev.get_enable() == true)
			mBtnDevEnablePtr->setBackgroundPic("kai.png");
		else
			mBtnDevEnablePtr->setBackgroundPic("guan.png");


		if(gSocket->connected())
			mBtnServerStatePtr->setBackgroundPic("kai.png");
		else
			mBtnServerStatePtr->setBackgroundPic("guan.png");

		mSeekbarLightPtr->setProgress(BRIGHTNESSHELPER->getBrightness());
		mTextLightPtr->setText(BRIGHTNESSHELPER->getBrightness());
		mSeekbarVolumePtr->setProgress(dev.get_volume());
		mTextVolumePtr->setText(dev.get_volume());
//	case 10:
//		EASYUICONTEXT->goHome();
//		isShowKeyboard = true;
//		break;
		default:
			break;
	}
    return true;
}

/**
 * 有新的触摸事件时触发
 * 参数：ev
 *         新的触摸事件
 * 返回值：true
 *            表示该触摸事件在此被拦截，系统不再将此触摸事件传递到控件上
 *         false
 *            触摸事件将继续传递到控件上
 */
static bool onsettingsActivityTouchEvent(const MotionEvent &ev) {

	return false;
}


FILE *myfile;
char str[4096000];
uint32_t len;

static bool onButtonClick_BtnSetLanguage(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnSetLanguage !!!\n");
	EASYUICONTEXT->openActivity("LanguageSettingActivity");
   return false;
}
static bool onButtonClick_BtnNetWork(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnNetWork !!!\n");
	EASYUICONTEXT->openActivity("NetSettingActivity");
    return false;
}

static bool onButtonClick_BtnServer(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnServer !!!\n");
	string tempServerIP ;
	int tempServerPort = 0;

	tempServerIP = mEditTextServerIPPtr->getText();
	tempServerPort = atoi(mEditTextServerPortPtr->getText().c_str());
	if((tempServerIP == dev.get_serverIP() ) && (tempServerPort == dev.get_serverPort()))
	{
	    mTextStatusNoticePtr->setText("无更改");
	    mTextStatusNotice2Ptr->setText("");
	    mWindStatusNoticePtr->showWnd();
		return true;
	}

	dev.set_serverIP(tempServerIP);
	dev.set_serverPort(tempServerPort);


    mTextStatusNoticePtr->setText("设置成功！");
    mTextStatusNotice2Ptr->setText("");

    //断开当前连接。守护进程会重新连接新的服务器
	gSocket->disconnect();

    mWindStatusNoticePtr->showWnd();
    return true;
}

static void onEditTextChanged_EditTextServerIP(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditTextServerIP %s !!!\n", text.c_str());
}

static void onEditTextChanged_EditTextServerPort(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditTextServerPort %s !!!\n", text.c_str());
}

static void onEditTextChanged_EdittextOldAdminPwd(const std::string &text) {
    //LOGD(" onEditTextChanged_ EdittextOldAdminPwd %s !!!\n", text.c_str());
}

static void onEditTextChanged_EdittextNewAdminPwd1(const std::string &text) {
    //LOGD(" onEditTextChanged_ EdittextNewAdminPwd1 %s !!!\n", text.c_str());
}

static void onEditTextChanged_EdittextNewAdminPwd2(const std::string &text) {
    //LOGD(" onEditTextChanged_ EdittextNewAdminPwd2 %s !!!\n", text.c_str());
}

static bool onButtonClick_BtnOK(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnOK !!!\n");
	string temp = mEdittextOldAdminPwdPtr->getText();
    mWindStatusNoticePtr->showWnd();
	if(temp == dev.get_pwdLocal())
	{
		if(mEdittextNewAdminPwd1Ptr->getText() == mEdittextNewAdminPwd2Ptr->getText())
		{
			dev.set_pwdLocal(mEdittextNewAdminPwd1Ptr->getText());// = StoragePreferences::getString("dev.pwdLocal", "123456");

		   // mWndModifyAdminPwdPtr->hideWnd();
		    mTextStatusNoticePtr->setText("修改成功");
		    mTextStatusNotice2Ptr->setText("");

		    if(gSocket->connected())
		    {
				mTextStatusNoticePtr->setText("等待同步设置服务器");
			    string str ;
			    str = jm.makeLocalPwd(dev.get_pwdLocal(),StatusSet);
				gSocket->write_(str);
			    gSocket->updateTriger();
		    }
		    else
		    {
			    mTextStatusNotice2Ptr->setText("无法同步设置服务器");

		    }

		}
		else
		{
			mTextStatusNoticePtr->setText("两次新密码不同");
		}
	}
	else
	{
		mTextStatusNoticePtr->setText("旧密码错误");
	}
    return false;
}

static bool onButtonClick_BtnCancel(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnCancel !!!\n");
	mWindLocalPwdPtr->hideWnd();
    return false;
}
static bool onButtonClick_BtnLocalPwd(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnLocalPwd !!!\n");
	mWindLocalPwdPtr->showWnd();
    return false;
}
static bool onButtonClick_BtnSyncDateTime(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnSyncDateTime !!!\n");
	char temp[20];
	string timeStr;
	struct tm *t = TimeHelper::getDateTime();
	sprintf(temp, "%d-%02d-%02d %02d:%02d:%02d", 1900 + t->tm_year, t->tm_mon + 1, t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
	timeStr = temp;
    if(gSocket->connected())
    {
    	string str = jm.makeSyncDateTime(timeStr, StatusSet);
		gSocket->write_(str);
    	gSocket->updateTriger();
        mWindStatusNoticePtr->showWnd();
        mTextStatusNoticePtr->setText("等待服务器响应");
        mTextStatusNotice2Ptr->setText("");
    }
    else
    {
        mWindStatusNoticePtr->showWnd();
        mTextStatusNoticePtr->setText("网络中断");
        mTextStatusNotice2Ptr->setText("无法同步服务器设置");
        mTextStatusNotice2Ptr->setText("");
    }

    return false;
}


static bool onButtonClick_BtnAdSet(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnAdSet !!!\n");

	updateAdSetWind();

	mWindAdSetPtr->showWnd();
    mEditAdNumPtr->setText(gAdv.getNum());

    return false;
}
static bool onButtonClick_BtnDownload(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnDownload !!!\n");
    if(gSocket->connected())
    {
    	HttpInfo_t info;

    	string str = jm.makeUpdate(info,  StatusRead);
		gSocket->write_(str);
    	gSocket->updateTriger();
        mWindStatusNoticePtr->showWnd();
        mTextStatusNoticePtr->setText("等待服务器响应");
        mTextStatusNotice2Ptr->setText("");
    }
    else
    {
        mWindStatusNoticePtr->showWnd();
        mTextStatusNoticePtr->setText("网络中断");
        mTextStatusNotice2Ptr->setText("无法同步服务器设置");
        mTextStatusNotice2Ptr->setText("");
    }



   return false;
}

static void onEditTextChanged_EditDisplayAdAfterTime(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditDisplayAdAfterTime %s !!!\n", text.c_str());
	string str = mEditDisplayAdAfterTimePtr->getText();
	int temp = atoi(str.c_str());
	if(temp > 1000)		temp = 1000;
	if(temp <= 10)		temp = 10;

	mEditDisplayAdAfterTimePtr->setText(temp);

}


static bool onButtonClick_BtnAdOK(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnAdOK !!!\n");
	string str = mEditDisplayAdAfterTimePtr->getText();
	int temp = atoi(str.c_str());
	gAdv.set_idleTime(temp);
	gAdv.set_enable(gAdv.get_enable());

    if(gSocket->connected())
    {
        mWindStatusNoticePtr->showWnd();
        mTextStatusNoticePtr->setText("设置成功");
        mTextStatusNotice2Ptr->setText("正在同步服务器设置");
        string str = jm.makeAdSet(gAdv,StatusSet);
		gSocket->write_(str);
        gSocket->updateTriger();
    }
    else
    {
        mWindStatusNoticePtr->showWnd();
        mTextStatusNoticePtr->setText("设置成功");
        mTextStatusNotice2Ptr->setText("无法同步设置服务器");

    }

    return false;
}

static bool onButtonClick_BtnAdCancel(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnAdCancel !!!\n");
	mWindAdSetPtr->hideWnd();
    return false;
}
static bool onButtonClick_BtnAdEnable(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnAdEnable !!!\n");
	if(gAdv.get_enable() == true)
	{
		mBtnAdEnablePtr->setBackgroundPic("guan.png");
		gAdv.set_enable_temp( false);
	}
	else
	{
		mBtnAdEnablePtr->setBackgroundPic("kai.png");
		gAdv.set_enable_temp(true);
	}
    return false;
}

static bool onButtonClick_BtnOrgNameSet(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnOrgNameSet !!!\n");
    //LOGD(" ButtonClick BtnNameSet !!!\n");
	string organization;
	organization = mEditOrgNamePtr->getText();
    StoragePreferences::putString("dev.organization", organization);
    if(gSocket->connected())
    {
        mWindStatusNoticePtr->showWnd();
        mTextStatusNoticePtr->setText("本地设置成功");
        mTextStatusNotice2Ptr->setText("正在同步服务器设置");

    	gSocket->updateTriger();
    	string msg;
    	msg = jm.makeOrgName(organization, StatusSet);
		gSocket->write_(msg);
    }
    else
    {
        mWindStatusNoticePtr->showWnd();
        mTextStatusNoticePtr->setText("本地设置成功");
        mTextStatusNotice2Ptr->setText("无法同步设置服务器");
    }
    return false;
}
static bool onButtonClick_BtnDevNameSet(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnNameSet !!!\n");
	string temp;
	dev.set_name(mEditDevNamePtr->getText());

    if(gSocket->connected())
    {
        mWindStatusNoticePtr->showWnd();
        mTextStatusNoticePtr->setText("本地设置成功");
        mTextStatusNotice2Ptr->setText("正在同步服务器设置");

    	gSocket->updateTriger();
    	string msg;
    	msg = jm.makeDevName(dev.get_name(), StatusSet);
		gSocket->write_(msg);
    }
    else
    {
        mWindStatusNoticePtr->showWnd();
        mTextStatusNoticePtr->setText("本地设置成功");
        mTextStatusNotice2Ptr->setText("无法同步设置服务器");
    }
    return false;
}
static bool onButtonClick_BtnDevEnable(ZKButton *pButton) {
//    LOGD(" ButtonClick BtnDevEnable (%d%d)!!!\n",dev.get_enable(),!dev.get_enable());
	dev.set_enable(!dev.get_enable());

	if(dev.get_enable() == true)
		mBtnDevEnablePtr->setBackgroundPic("kai.png");
	else{
		gSocket->disconnect();
		mBtnDevEnablePtr->setBackgroundPic("guan.png");

	}

	if(gSocket->connected())
		mBtnServerStatePtr->setBackgroundPic("kai.png");
	else
		mBtnServerStatePtr->setBackgroundPic("guan.png");
    return false;
}
static bool onButtonClick_BtnServerState(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnServerState !!!\n");
    return false;
}

static void onEditTextChanged_EditDevName(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditDevName %s !!!\n", text.c_str());
}


static void onEditTextChanged_Edittext1(const std::string &text) {
    //LOGD(" onEditTextChanged_ Edittext1 %s !!!\n", text.c_str());
}
static bool onButtonClick_BtnSetHeartbeat(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnSetHeartbeat !!!\n");
    //LOGD(" ButtonClick BtnNameSet !!!\n");
	int temp;
	temp = atoi(mEditHeartbeatPtr->getText().c_str());

	dev.set_heartbeatInterval(temp);// = temp;
    if(gSocket->connected())
    {
        mWindStatusNoticePtr->showWnd();
        mTextStatusNoticePtr->setText("设置成功");
        mTextStatusNotice2Ptr->setText("正在同步服务器设置");

    	gSocket->updateTriger();
    	string msg;
    	msg = jm.makeSetHeartbeat(dev.get_heartbeatInterval(), StatusSet);
		gSocket->write_(msg);
    }
    else
    {
        mWindStatusNoticePtr->showWnd();
        mTextStatusNoticePtr->setText("设置成功");
        mTextStatusNotice2Ptr->setText("无法同步设置服务器");
    }
    return false;
}
static void onEditTextChanged_EditHeartbeat(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditHeartbeat %s !!!\n", text.c_str());
	string str = mEditHeartbeatPtr->getText();
	int temp = atoi(str.c_str());
	if(temp > 100)
		temp = 100;
	else if(temp <= 3)
		temp = 3;
	mEditHeartbeatPtr->setText(temp);

}

static void onEditTextChanged_EditOrgName(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditOrgName %s !!!\n", text.c_str());
}



static bool onButtonClick_Button1(ZKButton *pButton) {
    //LOGD(" ButtonClick Button1 !!!\n");
    return false;
}

static void onProgressChanged_SeekbarLight(ZKSeekBar *pSeekBar, int progress) {
    //LOGD(" ProgressChanged SeekbarLight %d !!!\n", progress);
//	if(progress < 30)
//		progress = 30;
	BRIGHTNESSHELPER->setBrightness(progress);
	mTextLightPtr->setText(progress);

}
static void onProgressChanged_SeekbarMemUsage(ZKSeekBar *pSeekBar, int progress) {
    //LOGD(" ProgressChanged SeekbarMemUsage %d !!!\n", progress);
}
static void onEditTextChanged_EditAdNum(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditAdNum %s !!!\n", text.c_str());
}

static int getListItemCount_ListLockType(const ZKListView *pListView) {
    //LOGD("getListItemCount_ListLockType !\n");
    return 1;
}

static void obtainListItemData_ListLockType(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index) {
    //LOGD(" obtainListItemData_ ListLockType  !!!\n");
}

static void onListItemClick_ListLockType(ZKListView *pListView, int index, int id) {
    //LOGD(" onListItemClick_ ListLockType  !!!\n");
}
static bool onButtonClick_BtnLockState(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnLockState !!!\n");
    return false;
}

static bool onButtonClick_BtnLock(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnLock !!!\n");
    return false;
}

static bool onButtonClick_BtnUnLock(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnUnLock !!!\n");
    return false;
}
static void onProgressChanged_SeekbarVolume(ZKSeekBar *pSeekBar, int progress) {
    //LOGD(" ProgressChanged SeekbarVolume %d !!!\n", progress);
	sPlayer.setVolume((float) progress / 10, (float) progress / 10);
	mTextVolumePtr->setText(progress);
	dev.set_volume(progress);//
}
static bool onButtonClick_ButtonVolumeTest(ZKButton *pButton) {
    //LOGD(" ButtonClick ButtonVolumeTest !!!\n");

	sPlayer.setVolume((float)dev.get_volume()/10,(float)dev.get_volume()/10);
	if (!sIsPlayOK) {
		LOGD(" OK !!!\n");
		sPlayer.play("/mnt/extsd/test.mp3");

	} else {
		sPlayer.resume();
		LOGD(" failed !!!\n");
	}
	sPlayer.setVolume((float)dev.get_volume()/10,(float)dev.get_volume()/10);

	return false;
}
static bool onButtonClick_BtnStop(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnStop !!!\n");
	sPlayer.stop();
	sIsPlayOK = false;
	return false;
}

