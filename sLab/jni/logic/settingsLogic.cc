#pragma once
#include "utils/BrightnessHelper.h"
#include "uart/ProtocolSender.h"
#include "device.h"
#include "network/netcontext.h"
#include "netuser/jsonmanager.h"
#include "netuser/netlogintask.h"
#include <sys/sysinfo.h>
#include "http/httpdownload.h"


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

static void onProtocolNetDataUpdate(const NetProtocolData &data);

static void onDownloadEvent(std::string msg){
	mTextMsgTitlePtr->setText("下载信息");
	if(msg == "")
		mTextMsgPtr->setText("成功");
	else
		mTextMsgPtr->setText(msg);
	mWindNotifyPtr->showWnd();
}

/**
 * 注册定时器
 * 填充数组用于注册定时器
 * 注意：id不能重复
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	{1,  1000},
};

/**
 * 当界面构造时触发
 */
static void onUI_init(){
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");

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
	registerNetProtocolDataUpdateListener(onProtocolNetDataUpdate);
	downloadThread.registerEvent(onDownloadEvent,1);

    EASYUICONTEXT->showStatusBar();
    mWindLocalPwdPtr->hideWnd();
    mWindAdSetPtr->hideWnd();

	mTextIDPtr->setText(dev.id);
	mTextVersionPtr->setText(VERSION);
	mTextVersionDatePtr->setText(VERSION_DATE);
	mSeekbarLightPtr->setProgress(BRIGHTNESSHELPER->getBrightness());
	mTextLightPtr->setText(BRIGHTNESSHELPER->getBrightness());


	if(NETCONTEXT->connected())
		mBtnServerStatePtr->setBackgroundPic("kai.png");
	else
		mBtnServerStatePtr->setBackgroundPic("guan.png");

    mEditTextServerIPPtr->setText(dev.get_serverIP());
    mEditTextServerPortPtr->setText(dev.get_serverPort());
    mEditOrgNamePtr->setText(dev.get_organization());
	mEditDevNamePtr->setText(dev.get_department());
}

/*
 * 当界面隐藏时触发
 */
static void onUI_hide() {
	unregisterNetProtocolDataUpdateListener(onProtocolNetDataUpdate);
	downloadThread.unregisterEvent(1);
	EASYUICONTEXT->hideStatusBar();

}

/*
 * 当界面完全退出时触发
 */
static void onUI_quit() {
	downloadThread.unregisterEvent(1);
	//	LOGD("KEY 页面：注销。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。");
	unregisterNetProtocolDataUpdateListener(onProtocolNetDataUpdate);

}

/**
 * 串口数据回调接口
 */
static void onProtocolDataUpdate(const SProtocolData &data) {

}

/**
 * 串口数据回调接口
 */

static void onProtocolNetDataUpdate(const NetProtocolData &data){
	HttpInfo_t info;

	mTextMsgTitlePtr->setText(data.cmd);

	if(data.err == -1)
	{
		mTextMsgPtr->setText("服务器响应超时");
		mWindNotifyPtr->showWnd();
		return ;
	}
	if(data.cmd == Cmd::Update)
	{
		parseUpdate(data, info);
		mTextMsgPtr->setText(info.url);
		mWindNotifyPtr->showWnd();
	}
	if(data.cmd == Cmd::Department)
	{
		mEditDevNamePtr->setText(dev.get_department());

	}
	if(data.cmd == Cmd::Organization)
	{
	    mEditOrgNamePtr->setText(dev.get_organization());

	}
	if(data.cmd == Cmd::DateTime)
	{
	    mEditOrgNamePtr->setText(dev.get_organization());
		mTextMsgPtr->setText("同步成功");
		mWindNotifyPtr->showWnd();
	}
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

	     break;
	case 1:
		if(NETCONTEXT->connected())
			mBtnServerStatePtr->setBackgroundPic("kai.png");
		else
			mBtnServerStatePtr->setBackgroundPic("guan.png");

		mSeekbarLightPtr->setProgress(BRIGHTNESSHELPER->getBrightness());
		mTextLightPtr->setText(BRIGHTNESSHELPER->getBrightness());



	     sysinfo(&systemInfo);
	     char temp[30];
	     memUsage = (1 - ((float)systemInfo.freeram/(float)systemInfo.totalram))*100;
	     sprintf(temp,"%0.1f%%(%0.1fM/%0.1fM)",memUsage,\
	    		 (systemInfo.totalram - systemInfo.freeram)/1024.0/1024.0,\
				 systemInfo.totalram/1024.0/1024.0);
	     mSeekbarMemUsagePtr->setProgress(memUsage);
	     mTextMemUsagePtr->setText(temp);

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
    switch (ev.mActionStatus) {
		case MotionEvent::E_ACTION_DOWN://触摸按下
			//LOGD("时刻 = %ld 坐标  x = %d, y = %d", ev.mEventTime, ev.mX, ev.mY);
			break;
		case MotionEvent::E_ACTION_MOVE://触摸滑动
			break;
		case MotionEvent::E_ACTION_UP:  //触摸抬起
			break;
		default:
			break;
	}
	return false;
}
static bool onButtonClick_BtnNetWork(ZKButton *pButton) {
	EASYUICONTEXT->openActivity("NetSettingActivity");
    return false;
}

static bool onButtonClick_BtnSetLanguage(ZKButton *pButton) {
	EASYUICONTEXT->openActivity("LanguageSettingActivity");
    return false;
}

static bool onButtonClick_BtnServer(ZKButton *pButton) {
	string tempServerIP ;
	int tempServerPort = 0;

	tempServerIP = mEditTextServerIPPtr->getText();
	tempServerPort = atoi(mEditTextServerPortPtr->getText().c_str());
	if((tempServerIP == dev.get_serverIP() ) && (tempServerPort == dev.get_serverPort()))
	{
	    mTextMsgTitlePtr->setText("无更改");
	    mTextMsgPtr->setText("");
	    mWindNotifyPtr->showWnd();
		return true;
	}

	dev.set_serverIP(tempServerIP);
	dev.set_serverPort(tempServerPort);

	LOGD("server ip:%s",dev.get_serverIP().c_str());
	LOGD("server port : %d",dev.get_serverPort());

    mTextMsgTitlePtr->setText("");
	mTextMsgPtr->setText("设置成功！");

    //断开当前连接。守护进程会重新连接新的服务器
    NETCONTEXT->Close();
    netUser.login_state_set(false);
    NETCONTEXT->begin(dev.get_serverIP(),(uint16_t)dev.get_serverPort());

    mWindNotifyPtr->showWnd();
    return false;
}

static void onEditTextChanged_EditTextServerIP(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditTextServerIP %s !!!\n", text.c_str());
}

static void onEditTextChanged_EditTextServerPort(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditTextServerPort %s !!!\n", text.c_str());
}

static bool onButtonClick_BtnLocalPwd(ZKButton *pButton) {
	mWindLocalPwdPtr->showWnd();
    return false;
}

static bool onButtonClick_BtnSyncDateTime(ZKButton *pButton) {

	NetProtocolData msg;
    msg = makeDateTime(Status::Get);
    netUser.write(msg);
    return false;
}

static bool onButtonClick_BtnAdSet(ZKButton *pButton) {
    LOGD(" ButtonClick BtnAdSet !!!\n");

    return false;
}

static bool onButtonClick_BtnServerState(ZKButton *pButton) {
    LOGD(" ButtonClick BtnServerState !!!\n");
    return false;
}

static void onEditTextChanged_EditOrgName(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditOrgName %s !!!\n", text.c_str());
}

static bool onButtonClick_BtnOrgNameSet(ZKButton *pButton) {
    LOGD(" ButtonClick BtnOrgNameSet !!!\n");
    dev.set_organization(mEditOrgNamePtr->getText());
    return false;
}

static void onEditTextChanged_EditDevName(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditDevName %s !!!\n", text.c_str());
}

static bool onButtonClick_BtnDevNameSet(ZKButton *pButton) {
    dev.set_department(mEditDevNamePtr->getText());
    return false;
}

static void onEditTextChanged_EditHeartbeat(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditHeartbeat %s !!!\n", text.c_str());
}

static bool onButtonClick_BtnSetHeartbeat(ZKButton *pButton) {
    LOGD(" ButtonClick BtnSetHeartbeat !!!\n");
    return false;
}

static void onProgressChanged_SeekbarMemUsage(ZKSeekBar *pSeekBar, int progress) {
    //LOGD(" ProgressChanged SeekbarMemUsage %d !!!\n", progress);
}

static bool onButtonClick_BtnDownload(ZKButton *pButton) {

	HttpInfo_t info;
	NetProtocolData msg;
	info.port = 0;
	info.url = "";
	msg = makeUpdate(info,  Status::Get);
	netUser.write(msg);
    return false;
}

static void onProgressChanged_SeekbarLight(ZKSeekBar *pSeekBar, int progress) {
    //LOGD(" ProgressChanged SeekbarLight %d !!!\n", progress);
	BRIGHTNESSHELPER->setBrightness(progress);
	mTextLightPtr->setText(progress);

}

static bool onButtonClick_BtnDevEnable(ZKButton *pButton) {
    LOGD(" ButtonClick BtnDevEnable !!!\n");
    return false;
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
	mTextMsgTitlePtr->setText(Cmd::LocalPassword.c_str());
	mWindNotifyPtr->showWnd();
	if(temp == dev.get_pwdLocal())
	{
		if(mEdittextNewAdminPwd1Ptr->getText() == mEdittextNewAdminPwd2Ptr->getText())
		{
			dev.set_pwdLocal(mEdittextNewAdminPwd1Ptr->getText());// = StoragePreferences::getString("dev.pwdLocal", "123456");
		    if(NETCONTEXT->connected())
		    {
		    	mTextMsgPtr->setText("等待同步设置服务器");
				NetProtocolData msg ;
				msg = makeLocalPassword(Status::Set,dev.para.pwdLocal);
				netUser.write(msg);
		    }
		    else
		    {
		    	mTextMsgPtr->setText("无法同步设置服务器");
		    }

		}
		else
		{
			mTextMsgPtr->setText("两次新密码不同");
		}
	}
	else
	{
		mTextMsgPtr->setText("旧密码错误");
	}
	return false;
}

static bool onButtonClick_BtnCancel(ZKButton *pButton) {
    LOGD(" ButtonClick BtnCancel !!!\n");
    mWindLocalPwdPtr->hideWnd();
    return false;
}

static bool onButtonClick_BtnAdEnable(ZKButton *pButton) {
    LOGD(" ButtonClick BtnAdEnable !!!\n");
    return false;
}

static void onEditTextChanged_EditDisplayAdAfterTime(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditDisplayAdAfterTime %s !!!\n", text.c_str());
}

static bool onButtonClick_BtnAdOK(ZKButton *pButton) {
    LOGD(" ButtonClick BtnAdOK !!!\n");
    return false;
}

static bool onButtonClick_BtnAdCancel(ZKButton *pButton) {
    LOGD(" ButtonClick BtnAdCancel !!!\n");
    return false;
}

static void onEditTextChanged_EditAdNum(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditAdNum %s !!!\n", text.c_str());
}
#include <sys/reboot.h>

static bool onButtonClick_BtnRebot(ZKButton *pButton) {
	Thread::sleep(2000);
    reboot(RB_AUTOBOOT);
    return false;
}
//static bool onButtonClick_BtnRestartBetwork(ZKButton *pButton) {
//
//    string cmd = "ifconfig eth0 down";
//    system(cmd.c_str());
//    cmd = "ifconfig eth0 up";
//    system(cmd.c_str());
//    return false;
//}
