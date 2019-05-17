/***********************************************
/gen auto by zuitools
***********************************************/
#ifndef __SETTINGSACTIVITY_H__
#define __SETTINGSACTIVITY_H__


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
#define ID_SETTINGS_BtnDevEnable    20019
#define ID_SETTINGS_Textview15    50023
#define ID_SETTINGS_BtnStop    20018
#define ID_SETTINGS_ButtonVolumeTest    20016
#define ID_SETTINGS_TextVolume    50025
#define ID_SETTINGS_SeekbarVolume    91002
#define ID_SETTINGS_Textview11    50009
#define ID_SETTINGS_WindAdSet    110002
#define ID_SETTINGS_WindLocalPwd    110001
#define ID_SETTINGS_BtnLocalPwd    20005
#define ID_SETTINGS_EditAdNum    51010
#define ID_SETTINGS_Textview16    50024
#define ID_SETTINGS_TextLight    50022
#define ID_SETTINGS_SeekbarLight    91001
#define ID_SETTINGS_Textview14    50021
#define ID_SETTINGS_TextID    50020
#define ID_SETTINGS_Textview13    50019
#define ID_SETTINGS_TextVersion    50013
#define ID_SETTINGS_Textview12    50010
#define ID_SETTINGS_BtnDownload    20017
#define ID_SETTINGS_Textview6    50001
#define ID_SETTINGS_BtnOrgNameSet    20015
#define ID_SETTINGS_EditOrgName    51007
#define ID_SETTINGS_TextMemUsage    50018
#define ID_SETTINGS_SeekbarMemUsage    90000
#define ID_SETTINGS_Textview10    50016
#define ID_SETTINGS_EditHeartbeat    51009
#define ID_SETTINGS_BtnSetHeartbeat    20014
#define ID_SETTINGS_Textview8    50003
#define ID_SETTINGS_BtnDevNameSet    20013
#define ID_SETTINGS_EditDevName    51008
#define ID_SETTINGS_Textview9    50015
#define ID_SETTINGS_TextStatusNotice2    50008
#define ID_SETTINGS_WindStatusNotice    110003
#define ID_SETTINGS_TextStatusNotice    50017
#define ID_SETTINGS_BtnServerState    20012
#define ID_SETTINGS_BtnAdEnable    20009
#define ID_SETTINGS_BtnAdCancel    20011
#define ID_SETTINGS_BtnAdOK    20010
#define ID_SETTINGS_Textview7    50014
#define ID_SETTINGS_EditDisplayAdAfterTime    51006
#define ID_SETTINGS_Textview1    50012
#define ID_SETTINGS_TextAdEnavle    50011
#define ID_SETTINGS_BtnAdSet    20008
#define ID_SETTINGS_BtnSyncDateTime    20002
#define ID_SETTINGS_Textview5    50007
#define ID_SETTINGS_BtnCancel    20007
#define ID_SETTINGS_BtnOK    20006
#define ID_SETTINGS_EdittextNewAdminPwd2    51005
#define ID_SETTINGS_Textview4    50006
#define ID_SETTINGS_EdittextNewAdminPwd1    51004
#define ID_SETTINGS_Textview3    50005
#define ID_SETTINGS_Textview2    50004
#define ID_SETTINGS_EdittextOldAdminPwd    51003
#define ID_SETTINGS_EditTextServerPort    51002
#define ID_SETTINGS_EditTextServerIP    51001
#define ID_SETTINGS_TvServerIP    50002
#define ID_SETTINGS_BtnServer    20004
#define ID_SETTINGS_BtnNetWork    20001
#define ID_SETTINGS_BtnSetLanguage    20003
/*TAG:Macro宏ID END*/

class settingsActivity : public Activity, 
                     public ZKSeekBar::ISeekBarChangeListener, 
                     public ZKListView::IItemClickListener,
                     public ZKListView::AbsListAdapter,
                     public ZKSlideWindow::ISlideItemClickListener,
                     public EasyUIContext::ITouchListener,
                     public ZKEditText::ITextChangeListener,
                     public ZKVideoView::IVideoPlayerMessageListener
{
public:
    settingsActivity();
    virtual ~settingsActivity();

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