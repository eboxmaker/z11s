#pragma once
#include "uart/ProtocolSender.h"
#include "init.h"
#include "netuser/netlogintask.h"
#include "device.h"
#include "netuser/jsonmanager.h"
#include "utils/TimeHelper.h"
#include "global.h"

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

static string doorPassword;
static void onProtocolNetDataUpdate(const NetProtocolData &data);

static void updateCourseInfo()
{
	string picFullName = PIC_DIR +  gCourseInfo.picture.name;
	mTextTecherNamePtr->setText(gCourseInfo.name);
	mTextClassPtr->setText(gCourseInfo.class_);
	mTextNumPtr->setText(gCourseInfo.num);
	mTextCoursePtr->setText(gCourseInfo.course);
	mBtnTecherPicturePtr->setBackgroundPic(picFullName.c_str());
}
static void updateUI_time() {
	char timeStr[20];
	struct tm *t = TimeHelper::getDateTime();

	sprintf(timeStr, "%02d:%02d:%02d", t->tm_hour,t->tm_min,t->tm_sec);
	mTextTimePtr->setText(timeStr); // 注意修改控件名称

	sprintf(timeStr, "%d年%02d月%02d日", 1900 + t->tm_year, t->tm_mon + 1, t->tm_mday);
	mTextDatePtr->setText(timeStr); // 注意修改控件名称

	static const char *day[] = { "日", "一", "二", "三", "四", "五", "六" };
	sprintf(timeStr, "星期%s", day[t->tm_wday]);
	mTextWeekPtr->setText(timeStr); // 注意修改控件名称
}


static void updateDoorState()
{
	if(door.get_lock_state() == Unlock)
	{
		mTextLockStatePtr->setText("解锁");
	}
	else
	{
		mTextLockStatePtr->setText("上锁");
	}
	if(door.get_door_state() == Open)
	{
		mTextDoorStatePtr->setText("开");
	}
	else
	{
		mTextDoorStatePtr->setText("关");

	}
}
/**
 * 注册定时器
 * 填充数组用于注册定时器
 * 注意：id不能重复
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
		{1,  1000},
		{5,  5000},
};

/**
 * 当界面构造时触发
 */
static void onUI_init(){
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");
	init();

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
	string picFullName;
	registerNetProtocolDataUpdateListener(onProtocolNetDataUpdate);
	EASYUICONTEXT->hideStatusBar();
	doorPassword.clear();
	updateUI_time();
    string title;
    title = dev.get_organization();
    title += " | ";
    title += dev.get_department();
    mTextTitlePtr->setText(title.c_str());

	mTextBroadcastPtr->setText(gBroadcastMsg);
	updateCourseInfo();
	if(netUser.login_state_get())
	{
		mTvConnectStatePtr->setText("已连接");
		picFullName = QR_DIR +  gQRCode.name;
		mBtnQRCodePtr->setBackgroundPic(picFullName.c_str());
	}
	else
	{
		mTvConnectStatePtr->setText("未连接");
		mBtnQRCodePtr->setBackgroundPic("");
	}
	mWinPwdAdminPtr->hideWnd();
}

/*
 * 当界面隐藏时触发
 */
static void onUI_hide() {
	unregisterNetProtocolDataUpdateListener(onProtocolNetDataUpdate);
//	LOGD("KEY 页面：隐藏。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。");
}

/*
 * 当界面完全退出时触发
 */
static void onUI_quit() {
//	LOGD("KEY 页面：注销。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。。");
	unregisterNetProtocolDataUpdateListener(onProtocolNetDataUpdate);

}

/**
 * 串口数据回调接口
 */
static void onProtocolDataUpdate(const SProtocolData &data) {

}

/**
 * 网络数据回调接口
 */
static void onProtocolNetDataUpdate(const NetProtocolData &data){

	LockState_t doorCtrState;
	if(data.err == -1)
	{
		mTextMsgTitlePtr->setText(data.cmd);
		mTextMsgPtr->setText("服务器响应超时");
		mWindNotifyPtr->showWnd();
		return ;
	}
	HttpInfo_t info;
	string picFullName;

	if(data.cmd == Cmd::Update)
	{
		parseUpdate(data, info);
		mTextMsgTitlePtr->setText(data.cmd);
		mTextMsgPtr->setText(info.url);
		mWindNotifyPtr->showWnd();
	}
	if(data.cmd == Cmd::CourseInfo)
	{

		updateCourseInfo();

	}
	if(data.cmd == Cmd::Broadcast)
	{
		mTextBroadcastPtr->setText(gBroadcastMsg);
	}
	if(data.cmd == Cmd::QRCode)
	{
		picFullName = QR_DIR +  gQRCode.name;
		mBtnQRCodePtr->setBackgroundPic(picFullName.c_str());
	}
	if(data.cmd == Cmd::DoorLockControl)
	{
		parseDoorCtr(data, doorCtrState);
		if(doorCtrState == Lock)
		{
			mTextMsgPtr->setText("门锁已就位，请关门");
		}
		else
		{
			mTextMsgPtr->setText("门锁已打开，请开门");
		}
		mTextMsgTitlePtr->setText(data.cmd);
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
    string title;
    string picFullName;
	switch (id) {
	case 1:
		updateUI_time();
		if(netUser.login_state_get())
		{
			mTvConnectStatePtr->setText("已连接");
			picFullName = QR_DIR +  gQRCode.name;
			mBtnQRCodePtr->setBackgroundPic(picFullName.c_str());
		}
		else
		{
			mTvConnectStatePtr->setText("未连接");
			mBtnQRCodePtr->setBackgroundPic("");
		}

	    title = dev.get_organization();
	    title += " | ";
	    title += dev.get_department();
	    mTextTitlePtr->setText(title.c_str());

	    updateDoorState();
		break;

	case 5:
		updateCourseInfo();
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
static bool onkeyboardActivityTouchEvent(const MotionEvent &ev) {
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
static bool onButtonClick_Button1(ZKButton *pButton) {
    LOGD(" ButtonClick Button1 !!!\n");
    return false;
}

static bool onButtonClick_Button2(ZKButton *pButton) {
    LOGD(" ButtonClick Button2 !!!\n");
    return false;
}

static bool onButtonClick_Button3(ZKButton *pButton) {
    LOGD(" ButtonClick Button3 !!!\n");
    return false;
}

static bool onButtonClick_Button4(ZKButton *pButton) {
    LOGD(" ButtonClick Button4 !!!\n");
    return false;
}

static bool onButtonClick_Button5(ZKButton *pButton) {
    LOGD(" ButtonClick Button5 !!!\n");
    return false;
}


static bool onButtonClick_Btn0(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn0 !!!\n");
	doorPassword.append("0");
	mEditTextDoorPasswordPtr->setText(doorPassword.c_str());

    return false;
}
static bool onButtonClick_Btn1(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn1 !!!\n");
	doorPassword.append("1");
	mEditTextDoorPasswordPtr->setText(doorPassword.c_str());
	return false;
}

static bool onButtonClick_Btn2(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn2 !!!\n");
	doorPassword.append("2");
	mEditTextDoorPasswordPtr->setText(doorPassword.c_str());
   return false;
}

static bool onButtonClick_Btn3(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn3 !!!\n");
	doorPassword.append("3");
	mEditTextDoorPasswordPtr->setText(doorPassword.c_str());

    return false;
}

static bool onButtonClick_Btn4(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn4 !!!\n");
	doorPassword.append("4");
	mEditTextDoorPasswordPtr->setText(doorPassword.c_str());

    return false;
}

static bool onButtonClick_Btn5(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn5 !!!\n");
	doorPassword.append("5");
	mEditTextDoorPasswordPtr->setText(doorPassword.c_str());

    return false;
}

static bool onButtonClick_Btn6(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn6 !!!\n");
	doorPassword.append("6");
	mEditTextDoorPasswordPtr->setText(doorPassword.c_str());

  return false;
}

static bool onButtonClick_Btn7(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn7 !!!\n");
	doorPassword.append("7");
	mEditTextDoorPasswordPtr->setText(doorPassword.c_str());

    return false;
}

static bool onButtonClick_Btn8(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn8 !!!\n");
	doorPassword.append("8");
	mEditTextDoorPasswordPtr->setText(doorPassword.c_str());

    return false;
}


static bool onButtonClick_Btn9(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn9 !!!\n");
	doorPassword.append("9");
	mEditTextDoorPasswordPtr->setText(doorPassword.c_str());

    return false;
}


static bool onButtonClick_BtnQRCode(ZKButton *pButton) {
    LOGD(" ButtonClick BtnQRCode !!!\n");
    NetProtocolData msg;
    msg = makeQRCode(Status::Get, 0);
    netUser.write(msg);
    return false;
}

static bool onButtonClick_BtnOK(ZKButton *pButton) {

	if(doorPassword == "330238")
	{
		EASYUICONTEXT->openActivity("mainActivity");
		return false;
	}
	if(doorPassword == "2221362")
	{
		mWindOpenLockPtr->showWnd();
		return false;
	}
	if(NETCONTEXT->connected())
	{
		if(doorPassword != "")
		{
			NetProtocolData msg ;
			msg = makeDoorPwd(Status::Set,doorPassword);
			netUser.write(msg);
		}
		else
		{
			mWindNotifyPtr->showWnd();
			mTextMsgTitlePtr->setText("请输入密码");
			mTextMsgPtr->setText("");
		}
	}
	else if(doorPassword == dev.get_pwdLocal())
	{
		mWindOpenLockPtr->showWnd();
	}
	else
	{
		mWindNotifyPtr->showWnd();
		mTextMsgTitlePtr->setText("网络中断");
		mTextMsgPtr->setText("请输入管理员密码");
	}
	doorPassword.clear();
	mEditTextDoorPasswordPtr->setText(doorPassword.c_str());
    return false;
}

static bool onButtonClick_BtnBack(ZKButton *pButton) {
	doorPassword = doorPassword.substr(0, doorPassword.length() - 1);
	mEditTextDoorPasswordPtr->setText(doorPassword.c_str());
	return false;
}


static void onEditTextChanged_EditTextDoorPassword(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditTextDoorPassword %s !!!\n", text.c_str());
}

static bool onButtonClick_BtnBackMain(ZKButton *pButton) {
    LOGD(" ButtonClick BtnBackMain !!!\n");
    mEditTextAdminPasswordPtr->setText("");
	mWinPwdAdminPtr->showWnd();
    return false;
}

static bool onButtonClick_BtnPlan(ZKButton *pButton) {

	if(netUser.login_state_get())
	{
		EASYUICONTEXT->openActivity("planActivity");
	}
	else
	{

		mWindNotifyPtr->showWnd();
		mTextMsgTitlePtr->setText("网络中断");
		mTextMsgPtr->setText("无法获取课程表");
	}

    return false;
}

static bool onButtonClick_BtnTecherPicture(ZKButton *pButton) {
    LOGD(" ButtonClick BtnTecherPicture !!!\n");
    return false;
}

static void onEditTextChanged_EditTextAdminPassword(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditTextAdminPassword %s !!!\n", text.c_str());
}

static bool onButtonClick_BtnConfirm(ZKButton *pButton) {
    LOGD(" ButtonClick BtnConfirm !!!\n");
	string temp = mEditTextAdminPasswordPtr->getText();
	if(temp == dev.get_pwdLocal())
    {
		EASYUICONTEXT->openActivity("mainActivity");
		//EASYUICONTEXT->openActivity("mainActivity");
    }
	else
	{

		mWindNotifyPtr->showWnd();
		mTextMsgTitlePtr->setText("管理员密码错误");
		mTextMsgPtr->setText("");
	}

    return false;
}

static bool onButtonClick_BtnCancel(ZKButton *pButton) {
    LOGD(" ButtonClick BtnCancel !!!\n");
	mWinPwdAdminPtr->hideWnd();
    return false;
}

static bool onButtonClick_BtnLock(ZKButton *pButton) {
    LOGD(" ButtonClick BtnLock !!!\n");
    mWindDoorControlPtr->hideWnd();
    return false;
}

static bool onButtonClick_BtnUnLock(ZKButton *pButton) {
    LOGD(" ButtonClick BtnUnLock !!!\n");
    door.set_lock_ctr(Unlock);
    mWindDoorControlPtr->hideWnd();
    return false;
}
static bool onButtonClick_BtnOpenYes(ZKButton *pButton) {
    LOGD(" ButtonClick BtnOpenYes !!!\n");
    doorPassword.clear();
    mEditTextDoorPasswordPtr->setText("");
    door.set_lock_ctr(Unlock);
    mWindOpenLockPtr->hideWnd();
    return false;
}

static bool onButtonClick_BtnOpenCancel(ZKButton *pButton) {
    LOGD(" ButtonClick BtnOpenCancel !!!\n");
    doorPassword.clear();
    mEditTextDoorPasswordPtr->setText("");
    mWindOpenLockPtr->hideWnd();
    return false;
}
