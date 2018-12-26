#pragma once
#include "uart/ProtocolSender.h"
#include "json_test.h"
#include "globalVar.h"
#include "storage/StoragePreferences.h"
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


/**
 * 注册定时器
 * 填充数组用于注册定时器
 * 注意：id不能重复
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	//{0,  6000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
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
    EASYUICONTEXT->showStatusBar();
    gServerIP = StoragePreferences::getString("gServerIP", "192.168.1.1");
    LOGD("gServerIP %s\n", gServerIP.c_str());
    gServerPort = StoragePreferences::getString("gServerPort", "6000");
    LOGD("gServerIP %s\n", gServerPort.c_str());
    mEditTextServerIPPtr->setText(gServerIP.c_str());
    mEditTextServerPortPtr->setText(gServerPort.c_str());
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
static bool onButtonClick_Button2(ZKButton *pButton) {
    //LOGD(" ButtonClick Button2 !!!\n");
//	char buf[10];
//	myfile = openfile(&len);
//
//	if(myfile != NULL)
//	{
//		fseek(myfile,0L,SEEK_SET);
//		fread(str,1,len,myfile);
//		sprintf(buf,"%d",len);
//		mTextview1Ptr->setText(buf);
		//mTextview1Ptr->setBackgroundPic("res/ui/yb.png");
		mTextview1Ptr->setBackgroundPic("/mnt/extsd/12345678.jpg");
//
//	}
//	else
//	{
//		mTextview1Ptr->setText("failed");
//	}
    return false;
}
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
	gServerIP = mEditTextServerIPPtr->getText();
	gServerPort = mEditTextServerPortPtr->getText();
	uint16_t port = atoi(gServerPort.c_str());
	// 设置一个socket地址结构serverAddr,代表服务器的internet地址, 端口
	bzero(&gServerAddr, sizeof(gServerAddr));
	gServerAddr.sin_family = AF_INET;
	gServerAddr.sin_port=htons(port); //服务器端口号


	if (inet_aton(gServerIP.c_str(), &gServerAddr.sin_addr) == 0) {     // 服务器的IP地址来自程序的参数
		LOGD("Server IP Address Error!\n");
		return false;
	}
	else
	{
		LOGD("Server IP Address OK!\n");
	    StoragePreferences::putString("gServerIP", gServerIP.c_str());
	    StoragePreferences::putString("gServerPort", gServerPort.c_str());
	}

	LOGE("%s:%s",gServerIP.c_str(),gServerPort.c_str());
    return true;
}
static void onEditTextChanged_EditTextServerIP(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditTextServerIP %s !!!\n", text.c_str());
}

static void onEditTextChanged_EditTextServerPort(const std::string &text) {
    //LOGD(" onEditTextChanged_ EditTextServerPort %s !!!\n", text.c_str());
}
