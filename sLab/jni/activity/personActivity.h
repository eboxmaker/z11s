/***********************************************
/gen auto by zuitools
***********************************************/
#ifndef __PERSONACTIVITY_H__
#define __PERSONACTIVITY_H__


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
#define ID_PERSON_TextLockRight    50021
#define ID_PERSON_TextView1    50009
#define ID_PERSON_TextMsg    50027
#define ID_PERSON_TextMsgTitle    50026
#define ID_PERSON_WindNotify    110004
#define ID_PERSON_TextFingerOnlineState    50020
#define ID_PERSON_Textview8    50019
#define ID_PERSON_TvConnectState    50010
#define ID_PERSON_Textview6    50008
#define ID_PERSON_Textview9    50018
#define ID_PERSON_TextFingerState    50017
#define ID_PERSON_WindState    110002
#define ID_PERSON_TextFingerTotalNum    50016
#define ID_PERSON_BtnGetTotalFingerNum    20012
#define ID_PERSON_Textview10    50015
#define ID_PERSON_TextFingerIDList    50014
#define ID_PERSON_TextFingerNum    50013
#define ID_PERSON_Textview7    50012
#define ID_PERSON_BtnClearFinger1    20011
#define ID_PERSON_BtnDeleteUserFinger    20004
#define ID_PERSON_Textview5    50011
#define ID_PERSON_EditInstruction    51002
#define ID_PERSON_BtnUpdateServer    20008
#define ID_PERSON_BtnRollStep    20003
#define ID_PERSON_TextPersonLevel    50007
#define ID_PERSON_Textview4    50006
#define ID_PERSON_TextPersonID    50005
#define ID_PERSON_Textview3    50004
#define ID_PERSON_TextPersonName    50003
#define ID_PERSON_Textview2    50002
#define ID_PERSON_Textview1    50001
#define ID_PERSON_EditPersonID    51001
#define ID_PERSON_BtnQuaryPerson    20001
/*TAG:Macro宏ID END*/

class personActivity : public Activity, 
                     public ZKSeekBar::ISeekBarChangeListener, 
                     public ZKListView::IItemClickListener,
                     public ZKListView::AbsListAdapter,
                     public ZKSlideWindow::ISlideItemClickListener,
                     public EasyUIContext::ITouchListener,
                     public ZKEditText::ITextChangeListener,
                     public ZKVideoView::IVideoPlayerMessageListener
{
public:
    personActivity();
    virtual ~personActivity();

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