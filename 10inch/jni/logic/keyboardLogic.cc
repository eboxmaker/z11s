#pragma once
#include "uart/ProtocolSender.h"
#include "globalVar.h"
#include "json_test.h"
#include "utils/TimeHelper.h"
#include "base64.h"
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

static string QRCodeFullName = "/mnt/extsd/qr/qr.jpg";


static void clearPlanText()
{

	mTextTeacher1Ptr->setText("");
	mTextClass1Ptr->setText("");
	mTextCourse1Ptr->setText("");

	mTextTeacher2Ptr->setText("");
	mTextClass2Ptr->setText("");
	mTextCourse2Ptr->setText("");


	mTextTeacher3Ptr->setText("");
	mTextClass3Ptr->setText("");
	mTextCourse3Ptr->setText("");


	mTextTeacher4Ptr->setText("");
	mTextClass4Ptr->setText("");
	mTextCourse4Ptr->setText("");

}
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
	char out[1024];
	string outstring;
	string err ;
	int id;
	switch(cmd)
	{
	case CMD_GET_CURRENT_FEATURE:
		if(cmdState == 1)
		{
			int value = ((data[0])<<8) + data[1];

			LOGE("获取指纹执行状态%d",value);
		}
		else if(cmdState == 0)
		{
			LOGE("获取指数据包%d",len);
			if(Base64::Encode(data, len, out, 1024) == true)
			{
				Person_t person;
				outstring = out;
				person.fingers.push_back(outstring);
		    	person.id = "";
		    	mWindStatusNoticePtr->showWnd();
		    	if(gSocket->connected())
		    	{
			        string x;
			        x = jm.makePerson(person, StatusRead);
			        gSocket->write_(x);
		    		mTextStatusNoticePtr->setText("指纹验证中");
		    		gSocket->updateTriger();
		    	}
		    	else
		    	{
		    		mTextStatusNoticePtr->setText("网络中断");
		    		mTextStatusNotice2Ptr->setText("请输入管理员密码");
		    	}

//
			}


		}

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

	switch(cmd)
	{
	case CMDPerson:
		if(status == StatusOK)
		{
			gSocket->disableTriger();
			mWindStatusNoticePtr->showWnd();
			mTextStatusNoticePtr->setText("查询成功");
			temp += gPerson.name;
			temp += "/";
			temp += gPerson.id;
			temp += "/";
			switch(gPerson.level)
			{
			case 0:
				temp += "管理员";
				break;
			case 1:
				temp += "教师";
				break;
			case 2:
				temp += "学生";
				break;
			}
			mTextStatusNotice2Ptr->setText(temp.c_str());

			sleep(3);
			mWindStatusNoticePtr->hideWnd();
		}
		for(int i = 0 ; i < gPerson.fingers.size();i++)
			LOGE("len:%d,%s",gPerson.fingers[i].length(),gPerson.fingers[i].c_str());

		finger.getFeatures();
		break;
	case CMDDelQRCode:

	//	break;
	case CMDQRCode:
		QRCodeFullName = msg;
		mBtnQRCodePtr->setBackgroundPic(msg.c_str());
		break;
	case CMDAdminPwd:
		if(status == StatusSet)
		{
			mWindStatusNoticePtr->showWnd();
			mTextStatusNoticePtr->setText("管理员密码已经更新");
		}
		break;
	case CMDDoorPwd:
		if(status == StatusOK)
		{
			gSocket->disableTriger();
			mWindStatusNoticePtr->showWnd();
			mTextStatusNoticePtr->setText("密码正确");
		}
		else if(status == StatusErr)
		{
			gSocket->disableTriger();
			mWindStatusNoticePtr->showWnd();
			mTextStatusNoticePtr->setText("密码错误");
		}
		break;
	case CMDDoorCtr:
		if(status == StatusSet)
		{
			mWindStatusNoticePtr->showWnd();
			if(msg == "unlock")
			{
				mTextStatusNoticePtr->setText("门正在打开");
			}
			else
			{
				mTextStatusNoticePtr->setText("门正在关闭");
			}
			sleep(2);
			if(GpioHelper::input(GPIO_PIN_B_03) == UnLock)
			{
				mTextStatusNoticePtr->setText("门状态：开");
				mTextDoorStatePtr->setText("开");
			}
			else
			{
				mTextStatusNoticePtr->setText("门状态：关");
				mTextDoorStatePtr->setText("关");
			}
		}

		break;

	case CMDPlan:
		if(status == StatusOK)
		{
			clearPlanText();
			gSocket->disableTriger();
			mWindStatusNoticePtr->hideWnd();
			LOGE("gplan size :%d",gPlan.size());
			for(int i = 0; i < gPlan.size(); i++)
			{
				switch(i)
				{
				case 0:
					mTextTeacher1Ptr->setText(gPlan.row[i].teacher);
					mTextClass1Ptr->setText(gPlan.row[i].class_);
					mTextCourse1Ptr->setText(gPlan.row[i].courser);
					break;
				case 1:
					mTextTeacher2Ptr->setText(gPlan.row[i].teacher);
					mTextClass2Ptr->setText(gPlan.row[i].class_);
					mTextCourse2Ptr->setText(gPlan.row[i].courser);

					break;
				case 2:
					mTextTeacher3Ptr->setText(gPlan.row[i].teacher);
					mTextClass3Ptr->setText(gPlan.row[i].class_);
					mTextCourse3Ptr->setText(gPlan.row[i].courser);

					break;
				case 3:
					mTextTeacher4Ptr->setText(gPlan.row[i].teacher);
					mTextClass4Ptr->setText(gPlan.row[i].class_);
					mTextCourse4Ptr->setText(gPlan.row[i].courser);

					break;
				}
			}
			mWindPlanPtr->showWnd();
		}
		break;
	case CMDBroadcast:
//		if(gBroadcastMsg != "")
//		{
//			mWindBroadcastPtr->showWnd();
//		}
//		else
//		{
//			mWindBroadcastPtr->hideWnd();
//		}
		mTextBroadcastPtr->setText(gBroadcastMsg);

		break;
	case 255:
		mWindStatusNoticePtr->showWnd();
		mTextStatusNoticePtr->setText("服务器响应超时");
		mTextStatusNotice2Ptr->setText("");
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
	{0,  1000}, //定时器id=0, 时间间隔6秒
	{1,  1000},
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
    gKeyboardLastActionTime = time(NULL);
    mBtnBackPtr->setLongClickListener(&longButtonClickListener);
    finger.getFeatures();
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
	mWindStatusNoticePtr->hideWnd();
	mWinPwdAdminPtr->hideWnd();
	mWindPlanPtr->hideWnd();
	lastDoorState = gDoorState;
	doorPwd.clear();
    gKeyboardLastActionTime = time(NULL);
    gSocket->attachOnConnect(onNetConnect, 1);
    gSocket->attachOnDisconnect(onNetDisconnect, 1);

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
    title = mTextTitlePtr->getText();
    title += " | ";
    title += dev.name;

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

}

/*
 * 当界面隐藏时触发
 */
static void onUI_hide() {
	EASYUICONTEXT->hideStatusBar();
	LOGE("隐藏");

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
	string  str = jm.makeDoorPwd(doorPwd, StatusSet);
	mWindStatusNoticePtr->showWnd();
	if(gSocket->connected())
	{
		gSocket->write_(str);
		mTextStatusNoticePtr->setText("密码验证中");
		gSocket->updateTriger();
	}
	else
	{
		mTextStatusNoticePtr->setText("网络中断");
		mTextStatusNotice2Ptr->setText("请输入管理员密码");
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
	if(temp == dev.pwdLocal)
    {
		//EASYUICONTEXT->goBack();
		EASYUICONTEXT->openActivity("mainActivity");
    }
	else
	{
		mWindStatusNoticePtr->showWnd();
		mTextStatusNoticePtr->setText("管理员密码错误");
		LOGE("管理员密码：%s",dev.pwdLocal.c_str());
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
	if(gSocket->connected())
	{
		mWindStatusNoticePtr->showWnd();
		mTextStatusNoticePtr->setText("正在获取课程表");
		string str = jm.makePlan(StatusRead);
		gSocket->write_(str);
	    gKeyboardLastActionTime = time(NULL);
	    gSocket->updateTriger();
	}
	else
	{
		mWindStatusNoticePtr->showWnd();
		mTextStatusNoticePtr->setText("网络中断");
		mTextStatusNoticePtr->setText("无法获取课程表");
	}

    return false;
}
static bool onButtonClick_BtnExitPlan(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnExitPlan !!!\n");
	mWindPlanPtr->hideWnd();
    gKeyboardLastActionTime = time(NULL);

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
