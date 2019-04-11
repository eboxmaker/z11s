#pragma once
#include "uart/ProtocolSender.h"
#include "json_test.h"
#include "globalVar.h"
#include "storage/StoragePreferences.h"
#include "utils/TimeHelper.h"
#include "lib/itoa.h"
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
	gAdv.enable = StoragePreferences::getBool("gAdv.enable", gAdv.enable);
	gAdv.idleTime = StoragePreferences::getInt("gAdv.idleTime", gAdv.idleTime);
	if(gAdv.enable == true)
	{
		mBtnAdEnablePtr->setBackgroundPic("kai.png");
	}
	else
	{
		mBtnAdEnablePtr->setBackgroundPic("guan.png");
	}

	char buf[10];
	memset(buf,0,10);
	itoa(gAdv.idleTime,buf);
	mEditDisplayAdAfterTimePtr->setText(buf);

}


//static void updateDateEditText() {
//	struct tm *t = TimeHelper::getDateTime();
//	mYearEdittextPtr->setText(t->tm_year + 1900);
//	mMonthEdittextPtr->setText(t->tm_mon + 1);
//	mDayEdittextPtr->setText(t->tm_mday);
//}

//static void setSystemTime() {
//	struct tm t;
//	t.tm_year = atoi(mYearEdittextPtr->getText().c_str()) - 1900;		//年
//	t.tm_mon = atoi(mMonthEdittextPtr->getText().c_str()) - 1;			//月
//	t.tm_mday = atoi(mDayEdittextPtr->getText().c_str());				//日
//	t.tm_hour = 0;		//时
//	t.tm_min = 0;		//分
//	t.tm_sec = 0;		//秒
//
//	TimeHelper::setDateTime(&t);
//}


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

}
//网络数据回调接口
static void onNetWrokDataUpdate(JsonCmd_t cmd, JsonStatus_t status, string &msg)
{
	mTextStatusNotice2Ptr->setText("");
	switch(cmd)
	{
	case CMDSetHeartbeat:
	case CMDAdminPwd:
	case CMDSyncDateTime:
	case CMDAdSet:
	case CMDOrgName:
	case CMDDevName:
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
	//{1,  1000},
};

/**
 * 当界面构造时触发
 */
static void onUI_init(){
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");
	settingsCallback = onNetWrokDataUpdate;
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

    updateDisp();


    mWndModifyAdminPwdPtr->hideWnd();
    mWndAdSetPtr->hideWnd();


	if(gSocket->connected())
		mBtnServerStatePtr->setBackgroundPic("kai.png");
	else
		mBtnServerStatePtr->setBackgroundPic("guan.png");



//	mSeekbarMemUsagePtr->setProgress(gMemUsage);
//	sprintf(temp,"%0.1f%%",gMemUsage);
//	mTextMemUsagePtr->setText(temp);
}

/*
 * 当界面隐藏时触发
 */
static void onUI_hide() {
	EASYUICONTEXT->hideStatusBar();
}

/*
 * 当界面完全退出时触发
 */
static void onUI_quit() {
	settingsCallback = NULL;

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
	float memUsage;
	switch (id) {
	case 0:
		if(gSocket->connected())
			mBtnServerStatePtr->setBackgroundPic("kai.png");
		else
			mBtnServerStatePtr->setBackgroundPic("guan.png");

	     sysinfo(&dev.systemInfo);
	     char temp[30];
	     memUsage = (1 - ((float)dev.systemInfo.freeram/(float)dev.systemInfo.totalram))*100;
	     sprintf(temp,"%0.1f%%(%dM/%dM)",memUsage,dev.systemInfo.freeram/1024/1024,dev.systemInfo.totalram/1024/1024);
	     mSeekbarMemUsagePtr->setProgress(memUsage);
	     mTextMemUsagePtr->setText(temp);
	     break;
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
	struct sockaddr_in serverAddr;

	tempServerIP = mEditTextServerIPPtr->getText();
	tempServerPort = atoi(mEditTextServerPortPtr->getText().c_str());
	if((tempServerIP == dev.serverIP ) && (tempServerPort == dev.serverPort))
	{
//		LOGE("%s:%d",dev.serverIP.c_str(),tempServerPort);
	    mTextStatusNoticePtr->setText("无更改");
	    mWindStatusNoticePtr->showWnd();
		return true;
	}
	// 设置一个socket地址结构serverAddr,代表服务器的internet地址, 端口
	bzero(&serverAddr, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port=htons(tempServerPort); //服务器端口号


	if (inet_aton(tempServerIP.c_str(), &serverAddr.sin_addr) == 0) {     // 服务器的IP地址来自程序的参数
		LOGD("Server IP Address Error!\n");
	    mTextStatusNoticePtr->setText("服务器IP设置错误");
	    mWindStatusNoticePtr->showWnd();
		return false;
	}
	else
	{
		LOGD("Server IP Address OK!\n");
		dev.serverIP = tempServerIP;
		dev.serverPort = tempServerPort;

	    StoragePreferences::putString("dev.serverIP", dev.serverIP.c_str());
	    StoragePreferences::putInt("dev.serverPort", dev.serverPort);


		gSocket->disconnect();
		bool ret = gSocket->connect(dev.serverIP.c_str(),dev.serverPort);
		if(ret == true)
		{
//			LOGE("连接服务器成功!\n");
		    mTextStatusNoticePtr->setText("连接服务器成功!");

		}
		else
		{
			gSocket->disconnect();
			LOGE("连接服务器失败 !\n");
		    mTextStatusNoticePtr->setText("连接服务器失败!");
		}
	}

    mWindStatusNoticePtr->showWnd();
//	LOGE("%s:%d",dev.serverIP.c_str(),dev.serverPort);
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
	dev.pwdLocal = StoragePreferences::getString("dev.pwdLocal", "123456");
    mWindStatusNoticePtr->showWnd();
	if(temp == dev.pwdLocal)
	{
		if(mEdittextNewAdminPwd1Ptr->getText() == mEdittextNewAdminPwd2Ptr->getText())
		{
			dev.pwdLocal = mEdittextNewAdminPwd1Ptr->getText();
		    StoragePreferences::putString("dev.pwdLocal", dev.pwdLocal.c_str());
		   // mWndModifyAdminPwdPtr->hideWnd();
		    mTextStatusNoticePtr->setText("修改成功");

		    if(gSocket->connected())
		    {
				mTextStatusNoticePtr->setText("等待同步设置服务器");
			    string str ;
			    str = jm.makeAdminPwd(dev.pwdLocal,StatusSet);
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
    mWndModifyAdminPwdPtr->hideWnd();
    return false;
}
static bool onButtonClick_BtnModifyAdminPwd(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnModifyAdminPwd !!!\n");
    mWndModifyAdminPwdPtr->showWnd();
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



    mWndAdSetPtr->showWnd();

    return false;
}

static void onEditTextChanged_EditDisplayAdAfterTime(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditDisplayAdAfterTime %s !!!\n", text.c_str());
	string str = mEditDisplayAdAfterTimePtr->getText();
	int temp = atoi(str.c_str());
	if(temp > 100)
		temp = 100;
	else if(temp <= 10)
		temp = 10;
	else
	{

	}
	mEditDisplayAdAfterTimePtr->setText(temp);

}


static bool onButtonClick_BtnAdOK(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnAdOK !!!\n");
	string str = mEditDisplayAdAfterTimePtr->getText();
	int temp = atoi(str.c_str());
	gAdv.idleTime = temp;

    StoragePreferences::putBool("gAdv.enable", gAdv.enable);
    StoragePreferences::putInt("gAdv.idleTime", gAdv.idleTime);

    if(gSocket->connected())
    {
        mWindStatusNoticePtr->showWnd();
        mTextStatusNoticePtr->setText("设置成功");
        mTextStatusNoticePtr->setText("正在同步服务器设置");
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
	mWndAdSetPtr->hideWnd();
    return false;
}
static bool onButtonClick_BtnAdEnable(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnAdEnable !!!\n");
	if(gAdv.enable == true)
	{
		mBtnAdEnablePtr->setBackgroundPic("guan.png");
		gAdv.enable = false;
	}
	else
	{
		mBtnAdEnablePtr->setBackgroundPic("kai.png");
		gAdv.enable = true;
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
	dev.name = mEditDevNamePtr->getText();
    StoragePreferences::putString("dev.name", dev.name);
    if(gSocket->connected())
    {
        mWindStatusNoticePtr->showWnd();
        mTextStatusNoticePtr->setText("本地设置成功");
        mTextStatusNotice2Ptr->setText("正在同步服务器设置");

    	gSocket->updateTriger();
    	string msg;
    	msg = jm.makeDevName(dev.name, StatusSet);
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
	if(temp>0 && temp < 100)
	{
		dev.heartbeatInterval = temp;
	    StoragePreferences::putInt("dev.heartbeatInterval", dev.heartbeatInterval);
	}
    if(gSocket->connected())
    {
        mWindStatusNoticePtr->showWnd();
        mTextStatusNoticePtr->setText("设置成功");
        mTextStatusNoticePtr->setText("正在同步服务器设置");

    	gSocket->updateTriger();
    	string msg;
    	msg = jm.makeSetHeartbeat(dev.heartbeatInterval, StatusSet);
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
static void onProgressChanged_SeekbarMemUsage(ZKSeekBar *pSeekBar, int progress) {
    //LOGD(" ProgressChanged SeekbarMemUsage %d !!!\n", progress);
}

static bool onButtonClick_SoundButton(ZKButton *pButton) {
    //LOGD(" ButtonClick SoundButton !!!\n");
    return false;
}

static void onProgressChanged_SoundSeekbar(ZKSeekBar *pSeekBar, int progress) {
    //LOGD(" ProgressChanged SoundSeekbar %d !!!\n", progress);
}
static void onEditTextChanged_EditOrgName(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditOrgName %s !!!\n", text.c_str());
}

#include "httpDownload.h"

static bool onButtonClick_BtnDownload(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnDownload !!!\n");
    string url = dev.serverIP + "/download/update.img";
	downloadThread.settings(url,8080,"/mnt/extsd/temp","update.img");
    downloadThread.run("download-update");
   return false;
}
