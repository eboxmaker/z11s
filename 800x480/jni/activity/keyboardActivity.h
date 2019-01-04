/***********************************************
/gen auto by zuitools
***********************************************/
#ifndef __KEYBOARDACTIVITY_H__
#define __KEYBOARDACTIVITY_H__


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
#define ID_KEYBOARD_BtnQR    20001
#define ID_KEYBOARD_TVNote    50005
#define ID_KEYBOARD_TvConnectState    50004
#define ID_KEYBOARD_Textview3    50003
#define ID_KEYBOARD_Window1    110002
#define ID_KEYBOARD_EditTextAdminPassword    51002
#define ID_KEYBOARD_EditTextDoorPassword    51001
#define ID_KEYBOARD_BtnConfirm    20015
#define ID_KEYBOARD_WinPwdAdmin    110001
#define ID_KEYBOARD_BtnCancel    20016
#define ID_KEYBOARD_Textview2    50002
#define ID_KEYBOARD_BtnBackMain    20014
#define ID_KEYBOARD_BtnBack    20012
#define ID_KEYBOARD_Btn0    20013
#define ID_KEYBOARD_BtnOK    20011
#define ID_KEYBOARD_Btn7    20010
#define ID_KEYBOARD_Btn9    20009
#define ID_KEYBOARD_Btn8    20008
#define ID_KEYBOARD_Btn4    20007
#define ID_KEYBOARD_Btn6    20006
#define ID_KEYBOARD_Btn5    20005
#define ID_KEYBOARD_Btn3    20004
#define ID_KEYBOARD_Btn2    20003
#define ID_KEYBOARD_Btn1    20002
#define ID_KEYBOARD_Textview1    50001
/*TAG:Macro宏ID END*/

class keyboardActivity : public Activity, 
                     public ZKSeekBar::ISeekBarChangeListener, 
                     public ZKListView::IItemClickListener,
                     public ZKListView::AbsListAdapter,
                     public ZKSlideWindow::ISlideItemClickListener,
                     public EasyUIContext::ITouchListener,
                     public ZKEditText::ITextChangeListener,
                     public ZKVideoView::IVideoPlayerMessageListener
{
public:
    keyboardActivity();
    virtual ~keyboardActivity();

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
    void videoLoopPlayback(ZKVideoView *pVideoView, int msg, int callbackTabIndex);
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