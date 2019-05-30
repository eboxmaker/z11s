#pragma once
#include "uart/ProtocolSender.h"
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
#include "global.h"
#include "door.h"
#include "player.h"
#include "alarm.h"
#define	getArraySize(__ARR)									(sizeof(__ARR)/sizeof(__ARR[0]))		// 获取数组大小

static bool editEnable = false;

typedef struct {
	const char* mainText;
	bool bOn;
} LockData_t;

static LockData_t ListLockStr[] = {
		{"高电平锁门",false},
		{"高电平开门",false}
};
static LockData_t ListFeed1Data[] = {
	{"高电平锁门",false},
	{"高电平开门",false},
};

/**
 * 注册定时器
 * 填充数组用于注册定时器
 * 注意：id不能重复
 */
static S_ACTIVITY_TIMEER REGISTER_ACTIVITY_TIMER_TAB[] = {
	{0,  1000}, //定时器id=0, 时间间隔6秒
	//{1,  1000},
//	{10,  GO_HOME_TIME},
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
    ListLockStr[door.LockLogic].bOn = true;
    ListFeed1Data[door.Feed1Logic].bOn = true;

	if(door.get() == UnLock)
	{
		mBtnLockStatePtr->setBackgroundPic("kai.png");
		mBtnLockStatePtr->setText("开");
	}
	else
	{
		mBtnLockStatePtr->setBackgroundPic("guan.png");
		mBtnLockStatePtr->setText("关 ");
	}
	editEnable = false;
	mBtnEnablePtr->setText("不允许编辑锁选项");

	myAlarm.syncPlan();

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
static int i = 0;
static bool onUI_Timer(int id){
	switch (id) {
	case 0:

		if(door.get() == UnLock)
		{
			mBtnLockStatePtr->setBackgroundPic("kai.png");
			mBtnLockStatePtr->setText("开");
		}
		else
		{
			mBtnLockStatePtr->setBackgroundPic("guan.png");
			mBtnLockStatePtr->setText("关 ");
		}
	    break;
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
static bool onLockSettingsActivityTouchEvent(const MotionEvent &ev) {
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

static int getListItemCount_ListLockLogic(const ZKListView *pListView) {
    //LOGD("getListItemCount_ListLockLogic !\n");
    return getArraySize(ListLockStr);
}

static void obtainListItemData_ListLockLogic(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index) {
    //LOGD(" obtainListItemData_ ListLockLogic  !!!\n");
	ZKListView::ZKListSubItem* psubButton = pListItem->findSubItemByID(ID_LOCKSETTINGS_SubItem1);
	pListItem->setText(ListLockStr[index].mainText);
	psubButton->setSelected(ListLockStr[index].bOn);

//    LOGD("Lock:lock=%d\ntong=%d\nmag = %d",door.LockLogic,door.TongueLogic,door.MagnetLogic);
}

static void onListItemClick_ListLockLogic(ZKListView *pListView, int index, int id) {
    LOGD(" onListItemClick_ ListLockLogic  !!!index=%d;id=%d\n",index,id);
    if(editEnable)
    {
        for(int i = 0; i <  getArraySize(ListLockStr); i++ )
        {
        	ListLockStr[i].bOn = false;
        }
        ListLockStr[index].bOn = true;
        door.LockLogic = index;

        StoragePreferences::putInt("door.LockLogic", door.LockLogic);

    }

}







static int getListItemCount_ListFeed1Logic(const ZKListView *pListView) {
    //LOGD("getListItemCount_ListFeed1Logic !\n");
    return getArraySize(ListFeed1Data);
}

static void obtainListItemData_ListFeed1Logic(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index) {
    //LOGD(" obtainListItemData_ ListFeed1Logic  !!!\n");
	ZKListView::ZKListSubItem* psubButton = pListItem->findSubItemByID(ID_LOCKSETTINGS_SubItem2);
	pListItem->setText(ListFeed1Data[index].mainText);
	psubButton->setSelected(ListFeed1Data[index].bOn);
}

static void onListItemClick_ListFeed1Logic(ZKListView *pListView, int index, int id) {
    //LOGD(" onListItemClick_ ListFeed1Logic  !!!\n");
    if(editEnable)
    {
    	for(int i = 0; i <  getArraySize(ListFeed1Data); i++ )
		{
			ListFeed1Data[i].bOn = false;
		}
		ListFeed1Data[index].bOn = true;
		door.Feed1Logic = index;
        StoragePreferences::putInt("door.Feed1Logic", door.Feed1Logic);

	}
}


static bool onButtonClick_BtnUnLock(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnUnLock !!!\n");
	door.set(UnLock);
	if(door.get() == UnLock)
	{
		mBtnLockStatePtr->setBackgroundPic("kai.png");
		mBtnLockStatePtr->setText("开");
	}
	else
	{
		mBtnLockStatePtr->setBackgroundPic("guan.png");
		mBtnLockStatePtr->setText("关 ");
	}
	return false;}

static bool onButtonClick_BtnLockState(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnLockState !!!\n");
    return false;
}

static bool onButtonClick_BtnLock(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnLock !!!\n");
	door.set(Lock);
	if(door.get() == UnLock)
	{
		mBtnLockStatePtr->setBackgroundPic("kai.png");
		mBtnLockStatePtr->setText("开");
	}
	else
	{
		mBtnLockStatePtr->setBackgroundPic("guan.png");
		mBtnLockStatePtr->setText("关 ");
	}
    return false;
}
static bool onButtonClick_Button1(ZKButton *pButton) {
    //LOGD(" ButtonClick Button1 !!!\n");
	if (!sIsPlayOK) {
	    LOGD(" OK !!!\n");
		sPlayer.play("/mnt/extsd/success.mp3");
	    LOGD(" OK2 !!!\n");

	} else {
		sPlayer.resume();
	    LOGD(" failed !!!\n");

	}

    return false;
}
static bool onButtonClick_BtnEnable(ZKButton *pButton) {
    //LOGD(" ButtonClick BtnEnable !!!\n");
	editEnable = !editEnable;
	if(editEnable == true)
	{
		mBtnEnablePtr->setText("允许编辑锁选项");
	}
	else
	{
		mBtnEnablePtr->setText("不允许编辑锁选项");
	}
    return false;
}
static int getListItemCount_ListAlarm(const ZKListView *pListView) {
    //LOGD("getListItemCount_ListAlarm !\n");
    return myAlarm.alarmList.size();
}

static void obtainListItemData_ListAlarm(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index) {
    //LOGD(" obtainListItemData_ ListAlarm  !!!\n");
	ZKListView::ZKListSubItem* psubText = pListItem->findSubItemByID(ID_LOCKSETTINGS_SubItemAlarmType);
	pListItem->setText(myAlarm.alarmList[index].time);
	psubText->setText(myAlarm.alarmList[index].alarmTypeStr);
}

static void onListItemClick_ListAlarm(ZKListView *pListView, int index, int id) {
    //LOGD(" onListItemClick_ ListAlarm  !!!\n");
}
