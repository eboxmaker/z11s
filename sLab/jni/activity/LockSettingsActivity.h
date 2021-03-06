/***********************************************
/gen auto by zuitools
***********************************************/
#ifndef __LOCKSETTINGSACTIVITY_H__
#define __LOCKSETTINGSACTIVITY_H__


#include "app/Activity.h"
#include "entry/EasyUIContext.h"

#include "uart/ProtocolData.h"
#include "uart/ProtocolParser.h"

#include "utils/Log.h"
#include "control/ZKDigitalClock.h"
#include "control/ZKButton.h"
#include "control/ZKCircleBar.h"
#include "control/ZKDiagram.h"
#include "control/ZKListView.h"
#include "control/ZKPointer.h"
#include "control/ZKQRCode.h"
#include "control/ZKTextView.h"
#include "control/ZKSeekBar.h"
#include "control/ZKEditText.h"
#include "control/ZKVideoView.h"
#include "window/ZKSlideWindow.h"

/*TAG:Macro宏ID*/
#define ID_LOCKSETTINGS_Textview7    50007
#define ID_LOCKSETTINGS_BtnDoorState    20006
#define ID_LOCKSETTINGS_SubItem3    20002
#define ID_LOCKSETTINGS_ListFeed2Logic    80004
#define ID_LOCKSETTINGS_Textview6    50006
#define ID_LOCKSETTINGS_SubItemAlarmType    20003
#define ID_LOCKSETTINGS_ListAlarm    80003
#define ID_LOCKSETTINGS_Textview3    50003
#define ID_LOCKSETTINGS_BtnEnable    20005
#define ID_LOCKSETTINGS_Button1    20004
#define ID_LOCKSETTINGS_BtnLock    20018
#define ID_LOCKSETTINGS_BtnLockState    20016
#define ID_LOCKSETTINGS_BtnUnLock    20019
#define ID_LOCKSETTINGS_Textview11    50009
#define ID_LOCKSETTINGS_SubItem2    20002
#define ID_LOCKSETTINGS_ListFeed1Logic    80002
#define ID_LOCKSETTINGS_Textview2    50002
#define ID_LOCKSETTINGS_Textview1    50001
#define ID_LOCKSETTINGS_SubItem1    20001
#define ID_LOCKSETTINGS_ListLockLogic    80001
/*TAG:Macro宏ID END*/

class LockSettingsActivity : public Activity, 
                     public ZKSeekBar::ISeekBarChangeListener, 
                     public ZKListView::IItemClickListener,
                     public ZKListView::AbsListAdapter,
                     public ZKSlideWindow::ISlideItemClickListener,
                     public EasyUIContext::ITouchListener,
                     public ZKEditText::ITextChangeListener,
                     public ZKVideoView::IVideoPlayerMessageListener
{
public:
    LockSettingsActivity();
    virtual ~LockSettingsActivity();

    /**
     * 注册定时器
     */
	void registerUserTimer(int id, int time);
	/**
	 * 取消定时器
	 */
	void unregisterUserTimer(int id);
	/**
	 * 重置定时器
	 */
	void resetUserTimer(int id, int time);

protected:
    /*TAG:PROTECTED_FUNCTION*/
    virtual const char* getAppName() const;
    virtual void onCreate();
    virtual void onClick(ZKBase *pBase);
    virtual void onResume();
    virtual void onPause();
    virtual void onIntent(const Intent *intentPtr);
    virtual bool onTimer(int id);

    virtual void onProgressChanged(ZKSeekBar *pSeekBar, int progress);

    virtual int getListItemCount(const ZKListView *pListView) const;
    virtual void obtainListItemData(ZKListView *pListView, ZKListView::ZKListItem *pListItem, int index);
    virtual void onItemClick(ZKListView *pListView, int index, int subItemIndex);

    virtual void onSlideItemClick(ZKSlideWindow *pSlideWindow, int index);

    virtual bool onTouchEvent(const MotionEvent &ev);

    virtual void onTextChanged(ZKTextView *pTextView, const string &text);

    void rigesterActivityTimer();

    virtual void onVideoPlayerMessage(ZKVideoView *pVideoView, int msg);
    void videoLoopPlayback(ZKVideoView *pVideoView, int msg, size_t callbackTabIndex);
    void startVideoLoopPlayback();
    void stopVideoLoopPlayback();
    bool parseVideoFileList(const char *pFileListPath, std::vector<string>& mediaFileList);
    int removeCharFromString(string& nString, char c);


private:
    /*TAG:PRIVATE_VARIABLE*/
    int mVideoLoopIndex;
    int mVideoLoopErrorCount;

};

#endif