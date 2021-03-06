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
#define ID_KEYBOARD_BtnConfirm    20030
#define ID_KEYBOARD_BtnCancel    20029
#define ID_KEYBOARD_TextView1    50020
#define ID_KEYBOARD_BtnOpenCancel    20019
#define ID_KEYBOARD_BtnOpenYes    20025
#define ID_KEYBOARD_WindOpenLock    110007
#define ID_KEYBOARD_TextMsg    50027
#define ID_KEYBOARD_TextMsgTitle    50026
#define ID_KEYBOARD_WindNotify    110005
#define ID_KEYBOARD_Textview5    50041
#define ID_KEYBOARD_BtnUnLock    20027
#define ID_KEYBOARD_BtnLock    20026
#define ID_KEYBOARD_Textview1    50040
#define ID_KEYBOARD_WindDoorControl    110006
#define ID_KEYBOARD_Textview2    50002
#define ID_KEYBOARD_EditTextAdminPassword    51002
#define ID_KEYBOARD_WinPwdAdmin    110001
#define ID_KEYBOARD_TextFingerOnlineState    50019
#define ID_KEYBOARD_Textview10    50018
#define ID_KEYBOARD_TextLockState    50017
#define ID_KEYBOARD_Textview9    50016
#define ID_KEYBOARD_Textview12    50037
#define ID_KEYBOARD_TextDoorState    50036
#define ID_KEYBOARD_TextWeek    50006
#define ID_KEYBOARD_TextTime    50010
#define ID_KEYBOARD_TextDate    50009
#define ID_KEYBOARD_TvConnectState    50004
#define ID_KEYBOARD_Textview3    50003
#define ID_KEYBOARD_WindState    110002
#define ID_KEYBOARD_BtnTecherPicture    20017
#define ID_KEYBOARD_BtnPlan    20018
#define ID_KEYBOARD_Textview13    50039
#define ID_KEYBOARD_TextCourse    50015
#define ID_KEYBOARD_Textview8    50014
#define ID_KEYBOARD_TextClass    50013
#define ID_KEYBOARD_Textview6    50012
#define ID_KEYBOARD_TextTecherName    50011
#define ID_KEYBOARD_Textview4    50008
#define ID_KEYBOARD_TextNum    50001
#define ID_KEYBOARD_BtnBackMain    20014
#define ID_KEYBOARD_EditTextDoorPassword    51001
#define ID_KEYBOARD_TextTitle    50038
#define ID_KEYBOARD_Btn0    20013
#define ID_KEYBOARD_BtnBack    20012
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
#define ID_KEYBOARD_BtnQRCode    20001
#define ID_KEYBOARD_TextBroadcast    50007
#define ID_KEYBOARD_WindBroadcast    110004
#define ID_KEYBOARD_Button5    20024
#define ID_KEYBOARD_Button4    20023
#define ID_KEYBOARD_Button3    20022
#define ID_KEYBOARD_Button2    20021
#define ID_KEYBOARD_Button1    20020
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