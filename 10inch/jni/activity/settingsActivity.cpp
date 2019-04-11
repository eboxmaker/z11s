/***********************************************
/gen auto by zuitools
***********************************************/
#include "settingsActivity.h"

/*TAG:GlobalVariable全局变量*/
static ZKButton* mBtnDownloadPtr;
static ZKTextView* mTextview6Ptr;
static ZKButton* mBtnOrgNameSetPtr;
static ZKEditText* mEditOrgNamePtr;
static ZKTextView* mTextMemUsagePtr;
static ZKSeekBar* mSeekbarMemUsagePtr;
static ZKTextView* mTextview10Ptr;
static ZKEditText* mEditHeartbeatPtr;
static ZKButton* mBtnSetHeartbeatPtr;
static ZKTextView* mTextview8Ptr;
static ZKButton* mBtnDevNameSetPtr;
static ZKEditText* mEditDevNamePtr;
static ZKTextView* mTextview9Ptr;
static ZKTextView* mTextStatusNotice2Ptr;
static ZKWindow* mWindStatusNoticePtr;
static ZKTextView* mTextStatusNoticePtr;
static ZKButton* mBtnServerStatePtr;
static ZKButton* mBtnAdEnablePtr;
static ZKButton* mBtnAdCancelPtr;
static ZKButton* mBtnAdOKPtr;
static ZKTextView* mTextview7Ptr;
static ZKEditText* mEditDisplayAdAfterTimePtr;
static ZKTextView* mTextview1Ptr;
static ZKTextView* mTextAdEnavlePtr;
static ZKWindow* mWndAdSetPtr;
static ZKButton* mBtnAdSetPtr;
static ZKButton* mBtnSyncDateTimePtr;
static ZKTextView* mTextview5Ptr;
static ZKButton* mBtnModifyAdminPwdPtr;
static ZKWindow* mWndModifyAdminPwdPtr;
static ZKButton* mBtnCancelPtr;
static ZKButton* mBtnOKPtr;
static ZKEditText* mEdittextNewAdminPwd2Ptr;
static ZKTextView* mTextview4Ptr;
static ZKEditText* mEdittextNewAdminPwd1Ptr;
static ZKTextView* mTextview3Ptr;
static ZKTextView* mTextview2Ptr;
static ZKEditText* mEdittextOldAdminPwdPtr;
static ZKEditText* mEditTextServerPortPtr;
static ZKEditText* mEditTextServerIPPtr;
static ZKTextView* mTvServerIPPtr;
static ZKButton* mBtnServerPtr;
static ZKButton* mBtnNetWorkPtr;
static ZKButton* mBtnSetLanguagePtr;
static settingsActivity* mActivityPtr;

/*register activity*/
REGISTER_ACTIVITY(settingsActivity);

typedef struct {
	int id; // 定时器ID ， 不能重复
	int time; // 定时器  时间间隔  单位 毫秒
}S_ACTIVITY_TIMEER;

#include "logic/settingsLogic.cc"

/***********/
typedef struct {
    int id;
    const char *pApp;
} SAppInfo;

/**
 *点击跳转window
 */
static SAppInfo sAppInfoTab[] = {
//  { ID_MAIN_TEXT, "TextViewActivity" },
};

/***************/
typedef bool (*ButtonCallback)(ZKButton *pButton);
/**
 * button onclick表
 */
typedef struct {
    int id;
    ButtonCallback callback;
}S_ButtonCallback;

/*TAG:ButtonCallbackTab按键映射表*/
static S_ButtonCallback sButtonCallbackTab[] = {
    ID_SETTINGS_BtnDownload, onButtonClick_BtnDownload,
    ID_SETTINGS_BtnOrgNameSet, onButtonClick_BtnOrgNameSet,
    ID_SETTINGS_BtnSetHeartbeat, onButtonClick_BtnSetHeartbeat,
    ID_SETTINGS_BtnDevNameSet, onButtonClick_BtnDevNameSet,
    ID_SETTINGS_BtnServerState, onButtonClick_BtnServerState,
    ID_SETTINGS_BtnAdEnable, onButtonClick_BtnAdEnable,
    ID_SETTINGS_BtnAdCancel, onButtonClick_BtnAdCancel,
    ID_SETTINGS_BtnAdOK, onButtonClick_BtnAdOK,
    ID_SETTINGS_BtnAdSet, onButtonClick_BtnAdSet,
    ID_SETTINGS_BtnSyncDateTime, onButtonClick_BtnSyncDateTime,
    ID_SETTINGS_BtnModifyAdminPwd, onButtonClick_BtnModifyAdminPwd,
    ID_SETTINGS_BtnCancel, onButtonClick_BtnCancel,
    ID_SETTINGS_BtnOK, onButtonClick_BtnOK,
    ID_SETTINGS_BtnServer, onButtonClick_BtnServer,
    ID_SETTINGS_BtnNetWork, onButtonClick_BtnNetWork,
    ID_SETTINGS_BtnSetLanguage, onButtonClick_BtnSetLanguage,
};
/***************/


typedef void (*SeekBarCallback)(ZKSeekBar *pSeekBar, int progress);
typedef struct {
    int id;
    SeekBarCallback callback;
}S_ZKSeekBarCallback;
/*TAG:SeekBarCallbackTab*/
static S_ZKSeekBarCallback SZKSeekBarCallbackTab[] = {
    ID_SETTINGS_SeekbarMemUsage, onProgressChanged_SeekbarMemUsage,
};


typedef int (*ListViewGetItemCountCallback)(const ZKListView *pListView);
typedef void (*ListViewobtainListItemDataCallback)(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index);
typedef void (*ListViewonItemClickCallback)(ZKListView *pListView, int index, int id);
typedef struct {
    int id;
    ListViewGetItemCountCallback getListItemCountCallback;
    ListViewobtainListItemDataCallback obtainListItemDataCallback;
    ListViewonItemClickCallback onItemClickCallback;
}S_ListViewFunctionsCallback;
/*TAG:ListViewFunctionsCallback*/
static S_ListViewFunctionsCallback SListViewFunctionsCallbackTab[] = {
};


typedef void (*SlideWindowItemClickCallback)(ZKSlideWindow *pSlideWindow, int index);
typedef struct {
    int id;
    SlideWindowItemClickCallback onSlideItemClickCallback;
}S_SlideWindowItemClickCallback;
/*TAG:SlideWindowFunctionsCallbackTab*/
static S_SlideWindowItemClickCallback SSlideWindowItemClickCallbackTab[] = {
};


typedef void (*EditTextInputCallback)(const std::string &text);
typedef struct {
    int id;
    EditTextInputCallback onEditTextChangedCallback;
}S_EditTextInputCallback;
/*TAG:EditTextInputCallback*/
static S_EditTextInputCallback SEditTextInputCallbackTab[] = {
    ID_SETTINGS_EditOrgName, onEditTextChanged_EditOrgName,
    ID_SETTINGS_EditHeartbeat, onEditTextChanged_EditHeartbeat,
    ID_SETTINGS_EditDevName, onEditTextChanged_EditDevName,
    ID_SETTINGS_EditDisplayAdAfterTime, onEditTextChanged_EditDisplayAdAfterTime,
    ID_SETTINGS_EdittextNewAdminPwd2, onEditTextChanged_EdittextNewAdminPwd2,
    ID_SETTINGS_EdittextNewAdminPwd1, onEditTextChanged_EdittextNewAdminPwd1,
    ID_SETTINGS_EdittextOldAdminPwd, onEditTextChanged_EdittextOldAdminPwd,
    ID_SETTINGS_EditTextServerPort, onEditTextChanged_EditTextServerPort,
    ID_SETTINGS_EditTextServerIP, onEditTextChanged_EditTextServerIP,
};

typedef void (*VideoViewCallback)(ZKVideoView *pVideoView, int msg);
typedef struct {
    int id; //VideoView ID
    bool loop; // 是否是轮播类型
    int defaultvolume;//轮播类型时,默认视频音量
    VideoViewCallback onVideoViewCallback;
}S_VideoViewCallback;
/*TAG:VideoViewCallback*/
static S_VideoViewCallback SVideoViewCallbackTab[] = {
};


settingsActivity::settingsActivity() {
	//todo add init code here
	mVideoLoopIndex = 0;
	mVideoLoopErrorCount = 0;
}

settingsActivity::~settingsActivity() {
	//todo add init file here
    // 退出应用时需要反注册
    EASYUICONTEXT->unregisterGlobalTouchListener(this);
    onUI_quit();
    unregisterProtocolDataUpdateListener(onProtocolDataUpdate);
}

const char* settingsActivity::getAppName() const{
	return "settings.ftu";
}

//TAG:onCreate
void settingsActivity::onCreate() {
	Activity::onCreate();
    mBtnDownloadPtr = (ZKButton*)findControlByID(ID_SETTINGS_BtnDownload);
    mTextview6Ptr = (ZKTextView*)findControlByID(ID_SETTINGS_Textview6);
    mBtnOrgNameSetPtr = (ZKButton*)findControlByID(ID_SETTINGS_BtnOrgNameSet);
    mEditOrgNamePtr = (ZKEditText*)findControlByID(ID_SETTINGS_EditOrgName);if(mEditOrgNamePtr!= NULL){mEditOrgNamePtr->setTextChangeListener(this);}
    mTextMemUsagePtr = (ZKTextView*)findControlByID(ID_SETTINGS_TextMemUsage);
    mSeekbarMemUsagePtr = (ZKSeekBar*)findControlByID(ID_SETTINGS_SeekbarMemUsage);if(mSeekbarMemUsagePtr!= NULL){mSeekbarMemUsagePtr->setSeekBarChangeListener(this);}
    mTextview10Ptr = (ZKTextView*)findControlByID(ID_SETTINGS_Textview10);
    mEditHeartbeatPtr = (ZKEditText*)findControlByID(ID_SETTINGS_EditHeartbeat);if(mEditHeartbeatPtr!= NULL){mEditHeartbeatPtr->setTextChangeListener(this);}
    mBtnSetHeartbeatPtr = (ZKButton*)findControlByID(ID_SETTINGS_BtnSetHeartbeat);
    mTextview8Ptr = (ZKTextView*)findControlByID(ID_SETTINGS_Textview8);
    mBtnDevNameSetPtr = (ZKButton*)findControlByID(ID_SETTINGS_BtnDevNameSet);
    mEditDevNamePtr = (ZKEditText*)findControlByID(ID_SETTINGS_EditDevName);if(mEditDevNamePtr!= NULL){mEditDevNamePtr->setTextChangeListener(this);}
    mTextview9Ptr = (ZKTextView*)findControlByID(ID_SETTINGS_Textview9);
    mTextStatusNotice2Ptr = (ZKTextView*)findControlByID(ID_SETTINGS_TextStatusNotice2);
    mWindStatusNoticePtr = (ZKWindow*)findControlByID(ID_SETTINGS_WindStatusNotice);
    mTextStatusNoticePtr = (ZKTextView*)findControlByID(ID_SETTINGS_TextStatusNotice);
    mBtnServerStatePtr = (ZKButton*)findControlByID(ID_SETTINGS_BtnServerState);
    mBtnAdEnablePtr = (ZKButton*)findControlByID(ID_SETTINGS_BtnAdEnable);
    mBtnAdCancelPtr = (ZKButton*)findControlByID(ID_SETTINGS_BtnAdCancel);
    mBtnAdOKPtr = (ZKButton*)findControlByID(ID_SETTINGS_BtnAdOK);
    mTextview7Ptr = (ZKTextView*)findControlByID(ID_SETTINGS_Textview7);
    mEditDisplayAdAfterTimePtr = (ZKEditText*)findControlByID(ID_SETTINGS_EditDisplayAdAfterTime);if(mEditDisplayAdAfterTimePtr!= NULL){mEditDisplayAdAfterTimePtr->setTextChangeListener(this);}
    mTextview1Ptr = (ZKTextView*)findControlByID(ID_SETTINGS_Textview1);
    mTextAdEnavlePtr = (ZKTextView*)findControlByID(ID_SETTINGS_TextAdEnavle);
    mWndAdSetPtr = (ZKWindow*)findControlByID(ID_SETTINGS_WndAdSet);
    mBtnAdSetPtr = (ZKButton*)findControlByID(ID_SETTINGS_BtnAdSet);
    mBtnSyncDateTimePtr = (ZKButton*)findControlByID(ID_SETTINGS_BtnSyncDateTime);
    mTextview5Ptr = (ZKTextView*)findControlByID(ID_SETTINGS_Textview5);
    mBtnModifyAdminPwdPtr = (ZKButton*)findControlByID(ID_SETTINGS_BtnModifyAdminPwd);
    mWndModifyAdminPwdPtr = (ZKWindow*)findControlByID(ID_SETTINGS_WndModifyAdminPwd);
    mBtnCancelPtr = (ZKButton*)findControlByID(ID_SETTINGS_BtnCancel);
    mBtnOKPtr = (ZKButton*)findControlByID(ID_SETTINGS_BtnOK);
    mEdittextNewAdminPwd2Ptr = (ZKEditText*)findControlByID(ID_SETTINGS_EdittextNewAdminPwd2);if(mEdittextNewAdminPwd2Ptr!= NULL){mEdittextNewAdminPwd2Ptr->setTextChangeListener(this);}
    mTextview4Ptr = (ZKTextView*)findControlByID(ID_SETTINGS_Textview4);
    mEdittextNewAdminPwd1Ptr = (ZKEditText*)findControlByID(ID_SETTINGS_EdittextNewAdminPwd1);if(mEdittextNewAdminPwd1Ptr!= NULL){mEdittextNewAdminPwd1Ptr->setTextChangeListener(this);}
    mTextview3Ptr = (ZKTextView*)findControlByID(ID_SETTINGS_Textview3);
    mTextview2Ptr = (ZKTextView*)findControlByID(ID_SETTINGS_Textview2);
    mEdittextOldAdminPwdPtr = (ZKEditText*)findControlByID(ID_SETTINGS_EdittextOldAdminPwd);if(mEdittextOldAdminPwdPtr!= NULL){mEdittextOldAdminPwdPtr->setTextChangeListener(this);}
    mEditTextServerPortPtr = (ZKEditText*)findControlByID(ID_SETTINGS_EditTextServerPort);if(mEditTextServerPortPtr!= NULL){mEditTextServerPortPtr->setTextChangeListener(this);}
    mEditTextServerIPPtr = (ZKEditText*)findControlByID(ID_SETTINGS_EditTextServerIP);if(mEditTextServerIPPtr!= NULL){mEditTextServerIPPtr->setTextChangeListener(this);}
    mTvServerIPPtr = (ZKTextView*)findControlByID(ID_SETTINGS_TvServerIP);
    mBtnServerPtr = (ZKButton*)findControlByID(ID_SETTINGS_BtnServer);
    mBtnNetWorkPtr = (ZKButton*)findControlByID(ID_SETTINGS_BtnNetWork);
    mBtnSetLanguagePtr = (ZKButton*)findControlByID(ID_SETTINGS_BtnSetLanguage);
	mActivityPtr = this;
	onUI_init();
    registerProtocolDataUpdateListener(onProtocolDataUpdate); 
    rigesterActivityTimer();
}

void settingsActivity::onClick(ZKBase *pBase) {
	//TODO: add widget onClik code 
    int buttonTablen = sizeof(sButtonCallbackTab) / sizeof(S_ButtonCallback);
    for (int i = 0; i < buttonTablen; ++i) {
        if (sButtonCallbackTab[i].id == pBase->getID()) {
            if (sButtonCallbackTab[i].callback((ZKButton*)pBase)) {
            	return;
            }
            break;
        }
    }


    int len = sizeof(sAppInfoTab) / sizeof(sAppInfoTab[0]);
    for (int i = 0; i < len; ++i) {
        if (sAppInfoTab[i].id == pBase->getID()) {
            EASYUICONTEXT->openActivity(sAppInfoTab[i].pApp);
            return;
        }
    }

	Activity::onClick(pBase);
}

void settingsActivity::onResume() {
	Activity::onResume();
	EASYUICONTEXT->registerGlobalTouchListener(this);
	startVideoLoopPlayback();
	onUI_show();
}

void settingsActivity::onPause() {
	Activity::onPause();
	EASYUICONTEXT->unregisterGlobalTouchListener(this);
	stopVideoLoopPlayback();
	onUI_hide();
}

void settingsActivity::onIntent(const Intent *intentPtr) {
	Activity::onIntent(intentPtr);
	onUI_intent(intentPtr);
}

bool settingsActivity::onTimer(int id) {
	return onUI_Timer(id);
}

void settingsActivity::onProgressChanged(ZKSeekBar *pSeekBar, int progress){

    int seekBarTablen = sizeof(SZKSeekBarCallbackTab) / sizeof(S_ZKSeekBarCallback);
    for (int i = 0; i < seekBarTablen; ++i) {
        if (SZKSeekBarCallbackTab[i].id == pSeekBar->getID()) {
            SZKSeekBarCallbackTab[i].callback(pSeekBar, progress);
            break;
        }
    }
}

int settingsActivity::getListItemCount(const ZKListView *pListView) const{
    int tablen = sizeof(SListViewFunctionsCallbackTab) / sizeof(S_ListViewFunctionsCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SListViewFunctionsCallbackTab[i].id == pListView->getID()) {
            return SListViewFunctionsCallbackTab[i].getListItemCountCallback(pListView);
            break;
        }
    }
    return 0;
}

void settingsActivity::obtainListItemData(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index){
    int tablen = sizeof(SListViewFunctionsCallbackTab) / sizeof(S_ListViewFunctionsCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SListViewFunctionsCallbackTab[i].id == pListView->getID()) {
            SListViewFunctionsCallbackTab[i].obtainListItemDataCallback(pListView, pListItem, index);
            break;
        }
    }
}

void settingsActivity::onItemClick(ZKListView *pListView, int index, int id){
    int tablen = sizeof(SListViewFunctionsCallbackTab) / sizeof(S_ListViewFunctionsCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SListViewFunctionsCallbackTab[i].id == pListView->getID()) {
            SListViewFunctionsCallbackTab[i].onItemClickCallback(pListView, index, id);
            break;
        }
    }
}

void settingsActivity::onSlideItemClick(ZKSlideWindow *pSlideWindow, int index) {
    int tablen = sizeof(SSlideWindowItemClickCallbackTab) / sizeof(S_SlideWindowItemClickCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SSlideWindowItemClickCallbackTab[i].id == pSlideWindow->getID()) {
            SSlideWindowItemClickCallbackTab[i].onSlideItemClickCallback(pSlideWindow, index);
            break;
        }
    }
}

bool settingsActivity::onTouchEvent(const MotionEvent &ev) {
    return onsettingsActivityTouchEvent(ev);
}

void settingsActivity::onTextChanged(ZKTextView *pTextView, const std::string &text) {
    int tablen = sizeof(SEditTextInputCallbackTab) / sizeof(S_EditTextInputCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SEditTextInputCallbackTab[i].id == pTextView->getID()) {
            SEditTextInputCallbackTab[i].onEditTextChangedCallback(text);
            break;
        }
    }
}

void settingsActivity::rigesterActivityTimer() {
    int tablen = sizeof(REGISTER_ACTIVITY_TIMER_TAB) / sizeof(S_ACTIVITY_TIMEER);
    for (int i = 0; i < tablen; ++i) {
        S_ACTIVITY_TIMEER temp = REGISTER_ACTIVITY_TIMER_TAB[i];
        registerTimer(temp.id, temp.time);
    }
}


void settingsActivity::onVideoPlayerMessage(ZKVideoView *pVideoView, int msg) {
    int tablen = sizeof(SVideoViewCallbackTab) / sizeof(S_VideoViewCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SVideoViewCallbackTab[i].id == pVideoView->getID()) {
        	if (SVideoViewCallbackTab[i].loop) {
                //循环播放
        		videoLoopPlayback(pVideoView, msg, i);
        	} else if (SVideoViewCallbackTab[i].onVideoViewCallback != NULL){
        	    SVideoViewCallbackTab[i].onVideoViewCallback(pVideoView, msg);
        	}
            break;
        }
    }
}

void settingsActivity::videoLoopPlayback(ZKVideoView *pVideoView, int msg, int callbackTabIndex) {

	switch (msg) {
	case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_STARTED:
		LOGD("ZKVideoView::E_MSGTYPE_VIDEO_PLAY_STARTED\n");
		pVideoView->setVolume(SVideoViewCallbackTab[callbackTabIndex].defaultvolume / 10.0);
		mVideoLoopErrorCount = 0;
		break;
	case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_ERROR:
		/**错误处理 */
		++mVideoLoopErrorCount;
		if (mVideoLoopErrorCount > 100) {
			LOGD("video loop error counts > 100, quit loop playback !");
            break;
		} //不用break, 继续尝试播放下一个
	case ZKVideoView::E_MSGTYPE_VIDEO_PLAY_COMPLETED:
		LOGD("ZKVideoView::E_MSGTYPE_VIDEO_PLAY_COMPLETED\n");
        std::vector<std::string> videolist;
        std::string fileName(getAppName());
        if (fileName.size() < 4) {
             LOGD("getAppName size < 4, ignore!");
             break;
        }
        fileName = fileName.substr(0, fileName.length() - 4) + "_video_list.txt";
        fileName = "/mnt/extsd/" + fileName;
        if (!parseVideoFileList(fileName.c_str(), videolist)) {
            LOGD("parseVideoFileList failed !");
		    break;
        }
		if (pVideoView && !videolist.empty()) {
			mVideoLoopIndex = (mVideoLoopIndex + 1) % videolist.size();
			pVideoView->play(videolist[mVideoLoopIndex].c_str());
		}
		break;
	}
}

void settingsActivity::startVideoLoopPlayback() {
    int tablen = sizeof(SVideoViewCallbackTab) / sizeof(S_VideoViewCallback);
    for (int i = 0; i < tablen; ++i) {
    	if (SVideoViewCallbackTab[i].loop) {
    		ZKVideoView* videoView = (ZKVideoView*)findControlByID(SVideoViewCallbackTab[i].id);
    		if (!videoView) {
    			return;
    		}
    		//循环播放
    		videoLoopPlayback(videoView, ZKVideoView::E_MSGTYPE_VIDEO_PLAY_COMPLETED, i);
    		return;
    	}
    }
}

void settingsActivity::stopVideoLoopPlayback() {
    int tablen = sizeof(SVideoViewCallbackTab) / sizeof(S_VideoViewCallback);
    for (int i = 0; i < tablen; ++i) {
    	if (SVideoViewCallbackTab[i].loop) {
    		ZKVideoView* videoView = (ZKVideoView*)findControlByID(SVideoViewCallbackTab[i].id);
    		if (!videoView) {
    			return;
    		}
    		if (videoView->isPlaying()) {
    		    videoView->stop();
    		}
    		return;
    	}
    }
}

bool settingsActivity::parseVideoFileList(const char *pFileListPath, std::vector<string>& mediaFileList) {
	mediaFileList.clear();
	if (NULL == pFileListPath || 0 == strlen(pFileListPath)) {
        LOGD("video file list is null!");
		return false;
	}

	ifstream is(pFileListPath, ios_base::in);
	if (!is.is_open()) {
		LOGD("cann't open file %s \n", pFileListPath);
		return false;
	}
	char tmp[1024] = {0};
	while (is.getline(tmp, sizeof(tmp))) {
		string str = tmp;
		removeCharFromString(str, '\"');
		removeCharFromString(str, '\r');
		removeCharFromString(str, '\n');
		if (str.size() > 1) {
     		mediaFileList.push_back(str.c_str());
		}
	}
	LOGD("(f:%s, l:%d) parse fileList[%s], get [%d]files\n", __FUNCTION__,
			__LINE__, pFileListPath, mediaFileList.size());
	for (size_t i = 0; i < mediaFileList.size(); i++) {
		LOGD("file[%d]:[%s]\n", i, mediaFileList[i].c_str());
	}
	is.close();

	return true;
}

int settingsActivity::removeCharFromString(string& nString, char c) {
    string::size_type   pos;
    while(1) {
        pos = nString.find(c);
        if(pos != string::npos) {
            nString.erase(pos, 1);
        } else {
            break;
        }
    }
    return (int)nString.size();
}

void settingsActivity::registerUserTimer(int id, int time) {
	registerTimer(id, time);
}

void settingsActivity::unregisterUserTimer(int id) {
	unregisterTimer(id);
}

void settingsActivity::resetUserTimer(int id, int time) {
	resetUserTimer(id, time);
}