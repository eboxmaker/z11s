#pragma once
#include "../global.h"
#include "uart/ProtocolSender.h"
#include "json_manager.h"
#include "lib/base64.h"
#include "lib/finger.h"

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
/*指纹模块ID规划
 * 0-9：录入当前职员指纹空间
 * 10-19：当前有权限开门老师的指纹
 * 20-39：管理员指纹空间
 * */

static int fingerInputState = 0;
static int fingerNum = 1;
static string para_err ;
static int para_len;

static void onFingerOver(unsigned char cmd,int cmdState,unsigned char *data, unsigned int len)
{
	char temp_buf[1024];
	char out[1024];
	int id;

//	for(int i = 0; i < len ; i++)
//		LOGD("RX %D:%X",i,data[i]);
	switch(cmd)
	{
	case CMD_GET_CURRENT_FEATURE:
		if(cmdState == 0)
		{
			para_len = ((data[0])<<8) + data[1];
			para_err = finger.errToString(data[2]);
			LOGE("获取ID指纹执行状态%s,len:%d",para_err.c_str(),para_len);
			mTextFingerStatePtr->setText(para_err.c_str());
		}
		else if(cmdState == 1)
		{
			LOGE("获取指纹特征长度：%d",len);
			if(len == 0)
			{
				mTextFingerStatePtr->setText("获取失败:" + para_err);
			}
			else if(Base64::Encode(data, len, out, 1024) == true)
			{
	//			gPersonDump.fingers.push_back(outstring);
	//			for(int i = 0 ; i < gPersonDump.fingers.size();i++)
	//				LOGE("len:%d,%s",gPersonDump.fingers[i].length(),gPersonDump.fingers[i].c_str());
				mTextFingerStatePtr->setText("获取当前指纹成功");
			}

		}


		break;

	case CMD_GET_ID_FEATURE://包含前三个字节为用户号和权限
		if(cmdState == 0)
		{
			para_len = ((data[0])<<8) + data[1];
			para_err = finger.errToString(data[2]);
			LOGE("获取ID指纹执行状态%s,len:%d",para_err.c_str(),para_len);
			mTextFingerStatePtr->setText(para_err.c_str());
		}
		else if(cmdState == 1)
		{
			id = ((data[0])<<8) + data[1];
			if(Base64::Encode(&data[3], len - 3, out, 1024) == true)
			{
				gPersonDump.fingers.push_back(out);
				for(int i = 0 ; i < gPersonDump.fingers.size();i++)
					LOGE("len:%d,%s",gPersonDump.fingers[i].length(),gPersonDump.fingers[i].c_str());

			}
			sprintf(temp_buf,"获取%d号指纹成功",id);
			mTextFingerStatePtr->setText(temp_buf);

		}
		break;

	case CMD_SET_ID_FEATURE:

		break;


	case CMD_TIMEOUT:
		para_err += finger.errToString(finger.ack);
		if(finger.ack == ACK_SUCCESS)
		{
			int time = ((data[0])<<8) + data[1];
			fingerInputState = 0;
			mTextFingerStatePtr->setText(time);
		}
		else
		{
			mTextFingerStatePtr->setText(para_err);
		}
		break;
	case CMD_CLEAR:
		para_err += finger.errToString(finger.ack);
		if(finger.ack == ACK_SUCCESS)
		{
			fingerInputState = 0;
			mTextFingerStatePtr->setText("清空指纹成功");
		}
		else if(finger.ack == ACK_USER_EXIST)
		{
			mTextFingerStatePtr->setText(para_err);
		}
		break;
	case CMD_ENROLL1:
		para_err = finger.errToString(finger.ack);
		if(finger.ack == ACK_SUCCESS)
		{
			fingerInputState++;
			LOGE("第1步完成");
			mTextFingerStatePtr->setText("第1次录入成功");
		}
		else
		{
			fingerInputState = 0;
			mTextFingerStatePtr->setText(para_err);
			LOGE("第1步失败:%d",finger.ack);
		}
		break;



	case CMD_ENROLL2:
		para_err = finger.errToString(finger.ack);
		if(finger.ack == ACK_SUCCESS)
		{
			fingerInputState++;
			LOGE("第2步完成");
			mTextFingerStatePtr->setText("第2次录入成功");
		}
		else
		{
			fingerInputState = 0;
			mTextFingerStatePtr->setText(para_err);
			LOGE("第2步失败:%d",finger.ack);
		}
		break;


	case CMD_ENROLL3:
		para_err = finger.errToString(finger.ack);
		if(finger.ack == ACK_SUCCESS)
		{
			fingerInputState = 0;
			LOGE("第3步完成");
			mTextFingerStatePtr->setText("指纹录入完成");
//			mWindStatusNoticePtr->showWnd();
//	        mTextStatusNoticePtr->setText("继续录入");
			finger.getFeatures(fingerNum);

			fingerNum++;//录入一个指纹成功

		}
		else
		{
			mTextFingerStatePtr->setText(para_err);
			LOGE("第3步失败:%d",finger.ack);
		}
		break;
	}



}
static void onNetWrokDataUpdate(JsonCmd_t cmd, JsonStatus_t status, string &msg)
{
	//LOGE("%s",msg.c_str());

	switch(cmd)
	{

	case CMDPerson:
		if(status == StatusOK)
		{
			gSocket->disableTriger();
			mWindStatusNoticePtr->showWnd();
			mTextStatusNoticePtr->setText("同步成功");
			mTextPersonNamePtr->setText(gPersonDump.name);
			mTextPersonIDPtr->setText(gPersonDump.id);
			mBtnPicturePtr->setBackgroundPic(msg.c_str());
			switch(gPersonDump.level)
			{
			case 0:
				mTextPersonLevelPtr->setText("管理员");
				break;
			case 1:
				mTextPersonLevelPtr->setText("教师");
				break;
			case 2:
				mTextPersonLevelPtr->setText("学生");
				break;
			}
			sleep(1);
			mWindStatusNoticePtr->hideWnd();
		}

		break;
	case 255:
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
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
//	{10,  GO_HOME_TIME},
};

/**
 * 当界面构造时触发
 */
static void onUI_init(){
    //Tips :添加 UI初始化的显示代码到这里,如:mText1Ptr->setText("123");
	PersonCallback = onNetWrokDataUpdate;
	fingerCallback =onFingerOver;
    gPersonDump.id = "";
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
	mWindStatusNoticePtr->hideWnd();
    EASYUICONTEXT->showStatusBar();

    string instruction;
    instruction = "\
1.输入人员ID，点击查询，确保查询成功。\n\n\
2.点击录入指纹，左下角显示“请放手指”，将手指放在指纹模块上,并保持不动，提示：“录入1次成功”，再次按录入指纹按钮\
提示：“录入2次成功”，第三次次按录入指纹按钮，提示：“录入指纹完成”，当前指纹则录入完成，若果出现失败，则\
需要重新重复第二步\n\n\
3.如果需要录入多个指纹，请重复第二步\n\n\
4.点击“更新服务器指纹数据库”，则将该人员的指纹信息保存至服务器上。\
失败请检查服务器连接状态。";
    mEditInstructionPtr->setText(instruction);
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
	PersonCallback = NULL;
	fingerCallback =NULL;

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
static bool onpersonActivityTouchEvent(const MotionEvent &ev) {
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
static bool onButtonClick_BtnQuaryPerson(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnQuaryPerson !!!\n");
	string temp = mEditPersonIDPtr->getText();
//	mTextNamePtr->setText(gPersonDump[temp].name);
	mWindStatusNoticePtr->showWnd();
	if(temp == "")
	{
        mTextStatusNoticePtr->setText("请输入ID号");
        return false;
	}
    if(gSocket->connected())
    {
        mTextStatusNoticePtr->setText("正在查询。。。");
        mTextStatusNotice2Ptr->setText("");

    	gSocket->updateTriger();


    	PersonDump_t person;
    	person.id = temp;
        string x;
        x = jm.makePerson(person, StatusRead);
        gSocket->write_(x);
    }
    else
    {
        mTextStatusNoticePtr->setText("");
        mTextStatusNotice2Ptr->setText("无法连接服务器");
    }

    finger.clear();
    fingerNum = 1;
	gPersonDump.fingers.clear();
	gPersonDump.id = "";
	gPersonDump.name = "";
	gPersonDump.level = 0;
	mTextPersonNamePtr->setText(gPersonDump.name);
	mTextPersonIDPtr->setText(gPersonDump.id);
	mTextPersonLevelPtr->setText("");


    return false;
}

static void onEditTextChanged_Edittext1(const std::string &text) {
    //LOGD(" onEditTextChanged_ Edittext1 %s !!!\n", text.c_str());
}
static void onEditTextChanged_EditNum(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditNum %s !!!\n", text.c_str());
}
static void onEditTextChanged_EditPersonID(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditPersonID %s !!!\n", text.c_str());
}

static bool onButtonClick_Button1(ZKButton *pButton) {
    //LOGD(" ButtonClick Button1 !!!\n");
    return false;
}

static bool onButtonClick_Button2(ZKButton *pButton) {
    //LOGD(" ButtonClick Button2 !!!\n");
	if(gPersonDump.id == "")
	{
		mWindStatusNoticePtr->showWnd();
		mTextStatusNoticePtr->setText("请先获取ID对应的人员");
		mTextStatusNotice2Ptr->setText("");
		return false;
	}
	bool ret = false;
	string err;
	string temp = mEditPersonIDPtr->getText();
	int u_id = fingerNum;
	mTextFingerStatePtr->setText("请放手指。。。");
		LOGE("--正在 第%d步",fingerInputState);
	switch(fingerInputState)
	{
		case 0:
			LOGE("正在 第%d步",fingerInputState);
			 finger.Enroll_Step1(u_id);
			break;
		case 1:
//		case 2:
//		case 3:
//		case 4:

			 finger.Enroll_Step2(u_id);
			LOGE("正在 第%d步",fingerInputState);
			Thread::sleep(100);
			break;
		default:

				finger.Enroll_Step3(u_id);
				LOGE("正在 第%d步",fingerInputState);
				Thread::sleep(100);

			break;
	}


    return false;
}

static bool onButtonClick_BtnFingerPic(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnFingerPic !!!\n");
    return false;
}
static bool onButtonClick_BtnClearFinger(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnClearFinger !!!\n");
	int ret;
	finger.clear();

    return false;
}
static bool onButtonClick_BtnReadTimeout(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnReadTimeout !!!\n");
	finger.getTimeout();
    return false;
}
static bool onButtonClick_BtnSetTimeout(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnSetTimeout !!!\n");
	finger.setTimeout(0);
    return false;
}
static bool onButtonClick_BtnUpdateServer(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnUpdateServer !!!\n");

    if(gSocket->connected())
    {
    	string str = jm.makePerson(gPersonDump, StatusSet);
    	gSocket->write_(str);
    	gSocket->updateTriger();
        mWindStatusNoticePtr->showWnd();
        mTextStatusNoticePtr->setText("正在更新服务器");
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
static bool onButtonClick_BtnReadCurrentFeature(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnReadCurrentFeature !!!\n");
	finger.getFeatures();
	mTextFingerStatePtr->setText("请放手指。。。");
    return false;
}
static bool onButtonClick_BtnGetIDFeature(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnGetIDFeature !!!\n");
	finger.getFeatures(1);
    return false;
}
static bool onButtonClick_BtnPicture(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnPicture !!!\n");
    return false;
}
static void onEditTextChanged_EditInstruction(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditInstruction %s !!!\n", text.c_str());
}
