#pragma once
#include "../global.h"
#include "uart/ProtocolSender.h"
#include "json_manager.h"
#include "utils/TimeHelper.h"
#include "lib/base64.h"
#include "door.h"
#include "lib/finger.h"
#include "httpdownload.h"

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
static PersonInfo_t lastPersonInfo;
static PersonInfo_t nowPersonInfo;
static long last_trans_time = 0;
static bool is_on_download_finger = false;
static long last_download_finger_time = 0;
class LongClickListener : public ZKBase::ILongClickListener {

          virtual void onLongClick(ZKBase *pBase) {
                 LOGD("触发长按事件");
                 static int count = 0;

                 char buf[128] = {0};
                 snprintf(buf, sizeof(buf), "长按事件触发次数 %d", ++count);
                 //每次触发长按事件，修改按键的文字
             	doorPassword = doorPassword.substr(0, doorPassword.length() - 1);
             	mEditTextDoorPasswordPtr->setText(doorPassword.c_str());
          }
 };

static LongClickListener longButtonClickListener;

static string QRCodeFullName = "/mnt/extsd/qr/qr.jpg";
static void updateDoorState();
static void updateUI_time();
static void updateCourseInfo();
static void onDownloadEvent(string &msg);

static void onNetConnect()
{
	mBtnQRCodePtr->setBackgroundPic(QRCodeFullName.c_str());
	mTvConnectStatePtr->setText("已连接");

}
void static onNetDisconnect()
{
	mTvConnectStatePtr->setText("未连接");
	mBtnQRCodePtr->setBackgroundPic("");
}

static void onFingerOver(unsigned char cmd,int cmdState,unsigned char *data, unsigned int len)
{
	string ack ;
	int finger_id;
	switch(cmd)
	{
	case CMD_GET_SERIAL:
		if(finger.is_online() == false)
		{
			mTextFingerOnlineStatePtr->setText("未连接");
		}
		{
			mTextFingerOnlineStatePtr->setText("已连接");
		}
//		LOGD("检查在线完成");
		break;
	case CMD_SEARCH:
		finger_id = (data[0]<<8) + (data[1]);
		if(finger_id == 0){
			mTextStatusNoticePtr->setText("指纹匹配失败");
			mTextStatusNotice2Ptr->setText("");
		}
		else{
			if(gPerson.get_person_by_finger_id(finger_id, &nowPersonInfo) == true)
			{
				mTextStatusNoticePtr->setText(nowPersonInfo.name);
				mTextStatusNotice2Ptr->setText(nowPersonInfo.id);
				if((time(NULL) - last_trans_time > 10) || (lastPersonInfo.id  != nowPersonInfo.id))
				{
					ack = jm.makeFingerKey(nowPersonInfo, StatusSet);
					gSocket->write_(ack);
				}
			}
			else
			{
				mTextStatusNoticePtr->setText("匹配到残留指纹");
				mTextStatusNotice2Ptr->setText("请联系管理员");
			}


//			string picFullName = PIC_DIR +  psInfo.picture_name;

//			LOGD("ID:%s,pic name:%s",psInfo.id.c_str(),psInfo.picture_name.c_str());
//			mBtnTecherPicturePtr->setBackgroundPic(picFullName.c_str());
		}
    	mWindStatusNoticePtr->showWnd();


		break;
	default :
		break;
	}



}

//网络数据回调接口
static void onNetWrokDataUpdate(JsonCmd_t cmd, JsonStatus_t status, string &msg)
{
	//LOGE("%s",msg.c_str());
	string temp ;
    string title;

	switch(cmd)
	{
	case CMDDevName:
	case CMDOrgName:
	case CMDRegister:
	    title = dev.get_organization();
	    title += " | ";
	    title += dev.get_name();
	    mTextTitlePtr->setText(title.c_str());
		break;
	case CMDDelQRCode:
	//	break;
	case CMDQRCode:
		QRCodeFullName = msg;
		mBtnQRCodePtr->setBackgroundPic(msg.c_str());
		break;
	case CMDLocalPassword:
		if(status == StatusSet)
		{
			mWindStatusNoticePtr->showWnd();
			mTextStatusNoticePtr->setText("管理员密码已经更新");
			mTextStatusNoticePtr->setText("");
		}
		break;
	case CMDDoorPassword:
		if(status == StatusOK)
		{
			gSocket->disableTrigger();
			mWindStatusNoticePtr->hideWnd();
//			mTextStatusNoticePtr->setText("密码正确");
//			mTextStatusNotice2Ptr->setText("");
			mWindDoorControlPtr->showWnd();
		}
		else if(status == StatusErr)
		{
			gSocket->disableTrigger();
			mWindStatusNoticePtr->showWnd();
			mTextStatusNoticePtr->setText("密码错误");
			mTextStatusNotice2Ptr->setText("");

		}
		break;
	case CMDFingerKey:
		LOGD("指纹权限验证成功");
		lastPersonInfo = nowPersonInfo;
		last_trans_time = time(NULL);
		break;
	case CMDDoorLockControl:
		if(status == StatusSet)
		{
			updateDoorState();
		}
		break;
	case CMDCourseInfo:
		if(status == StatusSet)
		{
			updateCourseInfo();
			LOGE("更新课程表:%s",msg.c_str());
		}
		break;
	case CMDPlan://不需要执行
		if(status == StatusOK)
		{
//			LOGE("tirger :%d",gSocket->trigerTime);
				gSocket->disableTrigger();
		}
		break;
	case CMDBroadcast:
		mTextBroadcastPtr->setText(gBroadcastMsg);

		break;
	case CMDPersonAdd:

		is_on_download_finger = true;
		last_download_finger_time = time(NULL);

		mWinNoExitPtr->showWnd();
		mTextNoExitNotic1Ptr->setText("更新人员信息");
		mTextNoExitNotic2Ptr->setText("请等待");

		break;
	case CMDUpdate:
		mWinNoExitPtr->showWnd();
		mTextNoExitNotic1Ptr->setText("系统更新中。。。");
		mTextNoExitNotic2Ptr->setText("请等待");
		break;
	case CMDTimeout:
		mWindStatusNoticePtr->showWnd();
		mTextStatusNoticePtr->setText("服务器响应超时");
		mTextStatusNotice2Ptr->setText("");

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
	{1,  10000},
};

/**
 * 当界面构造时触发
 */
static void onUI_init(){
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");
    //注册按键长按监听
	fingerCallback =onFingerOver;
    keyboardCallback = onNetWrokDataUpdate;
    mTextStatusNoticePtr->setText("提示：...");
	mBtnQRCodePtr->setBackgroundPic(QRCodeFullName.c_str());
    mBtnBackPtr->setLongClickListener(&longButtonClickListener);
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
//	LOGO("显示:key");
    finger.check_online_async();

    EASYUICONTEXT->hideStatusBar();
	mWindStatusNoticePtr->hideWnd();
	mWinNoExitPtr->hideWnd();
	mWinPwdAdminPtr->hideWnd();
	mWindDoorControlPtr->hideWnd();
	doorPassword.clear();
    gKeyboardLastActionTime = time(NULL);
    gSocket->attachOnConnect(onNetConnect, 1);
    gSocket->attachOnDisconnect(onNetDisconnect, 1);
	downloadEvent = onDownloadEvent;


    if(gSocket->connected())
    {
    	mBtnQRCodePtr->setBackgroundPic(QRCodeFullName.c_str());
    	mTvConnectStatePtr->setText("已连接");
    }
    else
    {
    	mBtnQRCodePtr->setBackgroundPic("");
    	mTvConnectStatePtr->setText("未连接");
    }

    string title;
    title = dev.get_organization();
    title += " | ";
    title += dev.get_name();

    mTextTitlePtr->setText(title.c_str());

//	if(gBroadcastMsg != "")
//	{
//		mWindBroadcastPtr->showWnd();
//	}
//	else
//	{
//		mWindBroadcastPtr->hideWnd();
//	}
	mTextBroadcastPtr->setText(gBroadcastMsg);

	updateUI_time();

	updateCourseInfo();
	updateDoorState();
    finger.search_async();
}

/*
 * 当界面隐藏时触发
 */
static void onUI_hide() {
	EASYUICONTEXT->hideStatusBar();
	LOGO("隐藏:key");

}

/*
 * 当界面完全退出时触发
 */
static void onUI_quit() {
    //取消按键长按监听
	fingerCallback =NULL;
    keyboardCallback = NULL;
	mBtnBackPtr->setLongClickListener(NULL);
    gSocket->deattachOnConnect(1);
    gSocket->deattachOnDisconnect(1);
	downloadEvent = NULL;
	//	LOGO("注销:key");


}

/**
 * 串口数据回调接口
 */
static void onProtocolDataUpdate(const SProtocolData &data) {

}

static void adLoop()
{
	string cAppName;
	long  timeNow;
	timeNow = time(NULL);
	string cApp = EASYUICONTEXT->currentAppName();
	string target = "keyboardActivity";
	if(cApp != "keyboardActivity")
	{
		return;
	}

	if(gAdv.get_enable() && (gAdv.dbList.size() > 0))
	{
		const char *ptr;
		ptr = EASYUICONTEXT->currentAppName();
		cAppName = ptr;

		if(timeNow - gKeyboardLastActionTime > gAdv.get_idleTime())
		{
			EASYUICONTEXT->openActivity("AdvertisementActivity");
			//LOGE("切换成功");
		}
		else
		{
			//LOGE("TIME:%D",timeNow - gKeyboardLastActionTime);
		}
	}
	else
	{
		//LOGE("enable:%d,ad size:%d,TIME:%D",gAdv.enable,\
				gAdv.list.size(),\
				timeNow - gKeyboardLastActionTime);
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
//#include "readdir.h"
static bool onUI_Timer(int id){
	switch (id) {
	case 0:
		updateDoorState();
		updateUI_time();
		adLoop();
//	    if(finger.is_online())
//	    	mTextFingerStatePtr->setText("已连接");
//	    else{
//	    	mTextFingerStatePtr->setText("未连接");
//	    }

//		if(finger.is_on_search() == false)
//		{
//			finger.wait_busy();
//    		finger.search_async();
//    		LOGE("重新触发指纹");
//		}
		if(is_on_download_finger == false)
		{

			if(finger.is_on_search() == false)
			{
//				LOGD("开启指纹检测");
				finger.search_async();
			}
		}
		else
		{
			if(time(NULL) - last_download_finger_time > 3)
			{
				is_on_download_finger = false;
				mWinNoExitPtr->hideWnd();
			}
			else
			{
			}

		}
		break;
	case 1:

		if(is_on_download_finger == false)
		{
			if(finger.get_busy() == false){
				mTextFingerOnlineStatePtr->setText("未连接");
//				LOGD("检测在线状态");
				finger.check_online_async();
			}
			else
			{

			}
		}

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
    gKeyboardLastActionTime = time(NULL);
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


static bool onButtonClick_BtnOK(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnOK !!!\n");

	if(doorPassword == "3302389")
	{
		EASYUICONTEXT->openActivity("mainActivity");
		return false;
	}
	if(gSocket->connected())
	{
		if(doorPassword != "")
		{
			string  str = jm.makeDoorPwd(doorPassword, StatusSet);
			mWindStatusNoticePtr->showWnd();
			gSocket->write_(str);
			mTextStatusNoticePtr->setText("密码验证中");
			gSocket->updateTriger();
		}
		else
		{
			mWindStatusNoticePtr->showWnd();
			mTextStatusNoticePtr->setText("请输入密码");
		}
	}
	else if(doorPassword == dev.get_pwdLocal())
	{
		mWindDoorControlPtr->showWnd();
	}
	else
	{
		mWindStatusNoticePtr->showWnd();
		mTextStatusNoticePtr->setText("网络中断");
		mTextStatusNotice2Ptr->setText("请输入管理员密码");
	}
	doorPassword.clear();
	mEditTextDoorPasswordPtr->setText(doorPassword.c_str());

    return false;
}

static bool onButtonClick_BtnBack(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnBackUp !!!\n");
	doorPassword = doorPassword.substr(0, doorPassword.length() - 1);
	mEditTextDoorPasswordPtr->setText(doorPassword.c_str());

    return false;
}



static bool onButtonClick_BtnCancel(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnCancel !!!\n");
	mWinPwdAdminPtr->hideWnd();

    return false;
}
static void onEditTextChanged_EdittextPassword(const std::string &text) {
    //LOGD(" onEditTextChanged_ EdittextPassword %s !!!\n", text.c_str());
}

static bool onButtonClick_BtnConfirm(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnConfirm !!!\n");
	string temp = mEditTextAdminPasswordPtr->getText();
	if(temp == dev.get_pwdLocal())
    {
		EASYUICONTEXT->goBack();
		//EASYUICONTEXT->openActivity("mainActivity");
    }
	else
	{
		mWindStatusNoticePtr->showWnd();
		mTextStatusNoticePtr->setText("管理员密码错误");
		LOGE("管理员密码：%s",dev.get_pwdLocal().c_str());
	}

	return false;

}
static void onEditTextChanged_EditTextOpenPassword(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditTextOpenPassword %s !!!\n", text.c_str());
}

static void onEditTextChanged_EdittextAdminPassword(const std::string &text) {
    //LOGD(" onEditTextChanged_ EdittextAdminPassword %s !!!\n", text.c_str());
}
static void onEditTextChanged_EditTextDoorPassword(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditTextDoorPassword %s !!!\n", text.c_str());
}

static void onEditTextChanged_EditTextAdminPassword(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditTextAdminPassword %s !!!\n", text.c_str());
}
static bool onButtonClick_BtnQR(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnQR !!!\n");
    return false;
}

static bool onButtonClick_BtnBackMain(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnBackMain !!!\n");

	//WindInAdminPwd->showWnd();
	mWinPwdAdminPtr->showWnd();

	return false;
}
static bool onButtonClick_BtnBackMain2(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnBackMain2 !!!\n");

	//WindInAdminPwd->showWnd();
	mWinPwdAdminPtr->showWnd();

	return false;
}

static bool onButtonClick_BtnPlan(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnPlan !!!\n");
	if(gSocket->connected())
	{
		mWindStatusNoticePtr->showWnd();
		mTextStatusNoticePtr->setText("正在获取课程表");
		string str = jm.makePlan(StatusGet);
		gSocket->write_(str);

	    gSocket->updateTriger();
		EASYUICONTEXT->openActivity("planActivity");

	}
	else
	{
		mWindStatusNoticePtr->showWnd();
		mTextStatusNoticePtr->setText("网络中断");
		mTextStatusNoticePtr->setText("无法获取课程表");
	}

    return false;
}

static bool onButtonClick_BtnQRCode(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnQRCode !!!\n");
    return false;
}
static bool onButtonClick_Button1(ZKButton *pButton) {
    //LOGD(" ButtonClick Button1 !!!\n");
    return false;
}
static bool onButtonClick_Button2(ZKButton *pButton) {
    //LOGD(" ButtonClick Button2 !!!\n");
    return false;
}
static bool onButtonClick_Button3(ZKButton *pButton) {
    //LOGD(" ButtonClick Button3 !!!\n");
    return false;
}
static bool onButtonClick_Button4(ZKButton *pButton) {
    //LOGD(" ButtonClick Button4 !!!\n");
    return false;
}
static bool onButtonClick_Button5(ZKButton *pButton) {
    //LOGD(" ButtonClick Button5 !!!\n");
    return false;
}

static bool onButtonClick_Button6(ZKButton *pButton) {
    //LOGD(" ButtonClick Button6 !!!\n");
    return false;
}
static bool onButtonClick_BtnTecherPicture(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnTecherPicture !!!\n");
    return false;
}
static bool onButtonClick_BtnLockState(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnLockState !!!\n");
    return false;
}

static bool onButtonClick_BtnLock(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnLock !!!\n");

	door.set_lock_ctr(Lock);

    return false;
}

static bool onButtonClick_BtnUnLock(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnUnLock !!!\n");
    //LOGD(" ButtonClick BtnUnLock !!!\n");

	door.set_lock_ctr(Unlock);
	return false;
}











static void updateDoorState()
{
	if(door.get_lock_state() == Unlock)
	{
		mTextLockStatePtr->setText("解锁");
//		mBtnLockStatePtr->setText("解锁");
//		mBtnLockStatePtr->setBackgroundPic("kai.png");
	}
	else
	{
		mTextLockStatePtr->setText("上锁");
//		mBtnLockStatePtr->setText("上锁");
//		mBtnLockStatePtr->setBackgroundPic("guan.png");
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
static void updateCourseInfo()
{
	string picFullName = PIC_DIR +  gCourseInfo.picture.name;
	mTextTecherNamePtr->setText(gCourseInfo.name);
	mTextClassPtr->setText(gCourseInfo.class_);
	mTextNumPtr->setText(gCourseInfo.num);
	mTextCoursePtr->setText(gCourseInfo.course);
	mBtnTecherPicturePtr->setBackgroundPic(picFullName.c_str());
	if(gSocket->connected())
		mBtnQRCodePtr->setBackgroundPic(QRCodeFullName.c_str());

}
static void onDownloadEvent(string &msg)
{
	mWinNoExitPtr->showWnd();
	mTextNoExitNotic1Ptr->setText("");
	if(msg.empty())
	{
		mTextNoExitNotic2Ptr->setText("下载成功");
	}
	else
	{
		mTextNoExitNotic1Ptr->setText("下载失败");
		mTextNoExitNotic2Ptr->setText(msg);
		sleep(2);
		mWinNoExitPtr->hideWnd();
	}
}
