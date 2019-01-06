#pragma once
#include "uart/ProtocolSender.h"
#include "globalVar.h"
#include "json_test.h"
#include "utils/TimeHelper.h"

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
static string doorPwd;
static doorState_t lastDoorState;
class LongClickListener : public ZKBase::ILongClickListener {

          virtual void onLongClick(ZKBase *pBase) {
                 LOGD("触发长按事件");
                 static int count = 0;

                 char buf[128] = {0};
                 snprintf(buf, sizeof(buf), "长按事件触发次数 %d", ++count);
                 //每次触发长按事件，修改按键的文字
             	doorPwd = doorPwd.substr(0, doorPwd.length() - 1);
             	mEditTextDoorPasswordPtr->setText(doorPwd.c_str());
          }
 };

static LongClickListener longButtonClickListener;




//网络数据回调接口
static void onNetWrokDataUpdate(JsonCmd_t cmd,string &msg)
{
	//LOGE("%s",msg.c_str());
	Json::Reader reader;
	Json::Value root;
	switch(cmd)
	{
	case CMDQR:
		mBtnQRPtr->setText("");
		mBtnQRPtr->setBackgroundPic(msg.c_str());
		break;
	case CMDDoorPwd:
		mWindStatuNoticPtr->showWnd();
		if(msg == "1")
		{
			mTextStatuNoticePtr->setText("提示：密码正确");
		}
		else
		{
			mTextStatuNoticePtr->setText("提示：密码错误");
		}
		break;
	case CMDDoorCtr:
		mWindStatuNoticPtr->hideWnd();
		mWindStatuNoticPtr->showWnd();
		if(msg == "1")
		{
			mTextStatuNoticePtr->setText("门正在打开");
			sleep(2);
			if(GpioHelper::input(GPIO_PIN_B_02) == 1)
				mTextStatuNoticePtr->setText("门已经打开");
			else
				mTextStatuNoticePtr->setText("打开失败");

		}
		else
		{
			mTextStatuNoticePtr->setText("门正在关闭");
			sleep(2);
			if(GpioHelper::input(GPIO_PIN_B_02) == 0)
				mTextStatuNoticePtr->setText("门已经关闭");
			else
				mTextStatuNoticePtr->setText("关闭失败");
		}
		break;

	case CMDPlan:
		if (reader.parse(msg, root))  // reader将Json字符串解析到root，root将包含Json里所有子元素
		{
			Json::Value course = root["plan"];
			int course_size =  root["plan"].size();
			for(int i = 0; i < course_size; i++)
			{
				string x1 = course[i]["teacher"].asString();
				string x2 = course[i]["class"].asString();
				string x3 = course[i]["course"].asString();
				switch(i)
				{
				case 0:
					mTextTeacher1Ptr->setText(x1.c_str());
					mTextClass1Ptr->setText(x2.c_str());
					mTextCourse1Ptr->setText(x3.c_str());
					break;
				case 1:
					mTextTeacher2Ptr->setText(x1.c_str());
					mTextClass2Ptr->setText(x2.c_str());
					mTextCourse2Ptr->setText(x3.c_str());
					break;
				case 2:
					mTextTeacher3Ptr->setText(x1.c_str());
					mTextClass3Ptr->setText(x2.c_str());
					mTextCourse3Ptr->setText(x3.c_str());
					break;
				case 3:
					mTextTeacher4Ptr->setText(x1.c_str());
					mTextClass4Ptr->setText(x2.c_str());
					mTextCourse4Ptr->setText(x3.c_str());
					break;
				}
			}
		}
		mWindPlanPtr->showWnd();
		LOGE("课程表显示");
		break;
	case CMDBroadcast:
		if(msg != "")
		{
			mWindBroadcastPtr->showWnd();
			mTextBroadcastPtr->setText(msg);
		}
		else
		{
			mWindBroadcastPtr->hideWnd();
			mTextBroadcastPtr->setText(msg);
		}
		string str = MakeCMDBroadcastAck(msg);
		gSocket->write_(str);
		break;

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
/**
 * 注册定时器
 * 填充数组用于注册定时器
 * 注意：id不能重复
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	{0,  500}, //定时器id=0, 时间间隔6秒
	{1,  1000},
};

/**
 * 当界面构造时触发
 */
static void onUI_init(){
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");
    //注册按键长按监听
    mBtnBackPtr->setLongClickListener(&longButtonClickListener);
    keyboardCallback = onNetWrokDataUpdate;
    mTextStatuNoticePtr->setText("提示：...");
    gKeyboardLastActionTime = time(NULL);
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
	EASYUICONTEXT->hideStatusBar();
	mWindStatuNoticPtr->hideWnd();
	mWinPwdAdminPtr->hideWnd();
	mWindPlanPtr->hideWnd();
	lastDoorState = gDoorState;
	doorPwd.clear();
    gKeyboardLastActionTime = time(NULL);

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
    //取消按键长按监听
	mBtnBackPtr->setLongClickListener(NULL);
    keyboardCallback = NULL;

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
	switch (id) {
	case 0:
		if(getServerLiveState() == true)
		{
			mTvConnectStatePtr->setText("已连接");
		}
		else
		{
			mTvConnectStatePtr->setText("未连接");
		}

		break;
	case 1:
		updateUI_time();
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

static bool onButtonClick_Btn0(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn0 !!!\n");
	doorPwd.append("0");
	mEditTextDoorPasswordPtr->setText(doorPwd.c_str());
    gKeyboardLastActionTime = time(NULL);

    return false;
}
static bool onButtonClick_Btn1(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn1 !!!\n");
	doorPwd.append("1");
	mEditTextDoorPasswordPtr->setText(doorPwd.c_str());
    gKeyboardLastActionTime = time(NULL);
	return false;
}

static bool onButtonClick_Btn2(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn2 !!!\n");
	doorPwd.append("2");
	mEditTextDoorPasswordPtr->setText(doorPwd.c_str());
    gKeyboardLastActionTime = time(NULL);
   return false;
}

static bool onButtonClick_Btn3(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn3 !!!\n");
	doorPwd.append("3");
	mEditTextDoorPasswordPtr->setText(doorPwd.c_str());
    gKeyboardLastActionTime = time(NULL);
    return false;
}

static bool onButtonClick_Btn4(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn4 !!!\n");
	doorPwd.append("4");
	mEditTextDoorPasswordPtr->setText(doorPwd.c_str());
    gKeyboardLastActionTime = time(NULL);
    return false;
}

static bool onButtonClick_Btn5(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn5 !!!\n");
	doorPwd.append("5");
	mEditTextDoorPasswordPtr->setText(doorPwd.c_str());
    gKeyboardLastActionTime = time(NULL);
    return false;
}

static bool onButtonClick_Btn6(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn6 !!!\n");
	doorPwd.append("6");
	mEditTextDoorPasswordPtr->setText(doorPwd.c_str());
    gKeyboardLastActionTime = time(NULL);
  return false;
}

static bool onButtonClick_Btn7(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn7 !!!\n");
	doorPwd.append("7");
	mEditTextDoorPasswordPtr->setText(doorPwd.c_str());
    gKeyboardLastActionTime = time(NULL);
    return false;
}

static bool onButtonClick_Btn8(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn8 !!!\n");
	doorPwd.append("8");
	mEditTextDoorPasswordPtr->setText(doorPwd.c_str());
    gKeyboardLastActionTime = time(NULL);
    return false;
}


static bool onButtonClick_Btn9(ZKButton *pButton) {
    //LOGD(" ButtonClick Btn9 !!!\n");
	doorPwd.append("9");
	mEditTextDoorPasswordPtr->setText(doorPwd.c_str());
    gKeyboardLastActionTime = time(NULL);
    return false;
}


static bool onButtonClick_BtnOK(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnOK !!!\n");
	string  jstr = MakeCMDDoorPassword(doorPwd.c_str());
	mWindStatuNoticPtr->showWnd();
	if(updateServerLiveState())
	{
		gSocket->write_(jstr.c_str());
		mTextStatuNoticePtr->setText("提示：密码验证中");
	}
	else
	{
		mTextStatuNoticePtr->setText("提示：网络中断，请联系管理员");
	}
	doorPwd.clear();
	mEditTextDoorPasswordPtr->setText(doorPwd.c_str());
    gKeyboardLastActionTime = time(NULL);
    return false;
}

static bool onButtonClick_BtnBack(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnBackUp !!!\n");
	doorPwd = doorPwd.substr(0, doorPwd.length() - 1);
	mEditTextDoorPasswordPtr->setText(doorPwd.c_str());
    gKeyboardLastActionTime = time(NULL);
    return false;
}



static void onEditTextChanged_Edittext1(const std::string &text) {
    //LOGD(" onEditTextChanged_ Edittext1 %s !!!\n", text.c_str());
}

static void onEditTextChanged_EditTextKey(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditTextKey %s !!!\n", text.c_str());
}



static bool onButtonClick_BtnCancel(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnCancel !!!\n");
	mWinPwdAdminPtr->hideWnd();
    gKeyboardLastActionTime = time(NULL);
    return false;
}
static void onEditTextChanged_EdittextPassword(const std::string &text) {
    //LOGD(" onEditTextChanged_ EdittextPassword %s !!!\n", text.c_str());
}

static bool onButtonClick_BtnConfirm(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnConfirm !!!\n");
	string temp = mEditTextAdminPasswordPtr->getText();
	if(temp == gAdminPwd)
    {
		EASYUICONTEXT->openActivity("mainActivity");
    }
	else
	{
		mWindStatuNoticPtr->showWnd();
		mTextStatuNoticePtr->setText("提示：管理员密码错误");
		LOGE("管理员密码：%s",gAdminPwd.c_str());
	}
    gKeyboardLastActionTime = time(NULL);
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
    gKeyboardLastActionTime = time(NULL);
	return false;
}
static bool onButtonClick_BtnBackMain2(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnBackMain2 !!!\n");

	//WindInAdminPwd->showWnd();
	mWinPwdAdminPtr->showWnd();
    gKeyboardLastActionTime = time(NULL);
	return false;}

static bool onButtonClick_BtnPlan(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnPlan !!!\n");
	mWindStatuNoticPtr->showWnd();
	mTextStatuNoticePtr->setText("提示：正在获取课程表");
	string str = MakeCMDPlan();
	gSocket->write_(str);
    gKeyboardLastActionTime = time(NULL);

    return false;
}
static bool onButtonClick_BtnExitPlan(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnExitPlan !!!\n");
	mWindPlanPtr->hideWnd();
    gKeyboardLastActionTime = time(NULL);

    return false;
}
