/***********************************************
/gen auto by zuitools
***********************************************/
#include "personActivity.h"

/*TAG:GlobalVariable全局变量*/
static ZKTextView* mTextFingerOnlineStatePtr;
static ZKTextView* mTextview8Ptr;
static ZKTextView* mTvConnectStatePtr;
static ZKTextView* mTextview9Ptr;
static ZKWindow* mWindStatePtr;
static ZKTextView* mTextFingerTotalNumPtr;
static ZKButton* mButton1Ptr;
static ZKTextView* mTextview10Ptr;
static ZKTextView* mTextFingerIDListPtr;
static ZKTextView* mTextFingerNumPtr;
static ZKTextView* mTextview7Ptr;
static ZKButton* mBtnDeleteUserFingerPtr;
static ZKButton* mBtnClearFinger1Ptr;
static ZKTextView* mTextview5Ptr;
static ZKEditText* mEditInstructionPtr;
static ZKButton* mBtnPicturePtr;
static ZKButton* mBtnGetIDFeaturePtr;
static ZKButton* mBtnReadCurrentFeaturePtr;
static ZKButton* mBtnUpdateServerPtr;
static ZKButton* mBtnSetTimeoutPtr;
static ZKButton* mBtnReadTimeoutPtr;
static ZKTextView* mTextFingerStatePtr;
static ZKButton* mBtnClearFingerPtr;
static ZKTextView* mTextPersonIDPtr;
static ZKTextView* mTextPersonLevelPtr;
static ZKTextView* mTextPersonNamePtr;
static ZKTextView* mTextStatusNotice2Ptr;
static ZKTextView* mTextStatusNoticePtr;
static ZKWindow* mWindStatusNoticePtr;
static ZKTextView* mTextview6Ptr;
static ZKButton* mButton2Ptr;
static ZKTextView* mTextview4Ptr;
static ZKTextView* mTextview3Ptr;
static ZKEditText* mEditPersonIDPtr;
static ZKTextView* mTextview2Ptr;
static ZKTextView* mTextview1Ptr;
static ZKButton* mBtnQuaryPersonPtr;
static personActivity* mActivityPtr;

/*register activity*/
REGISTER_ACTIVITY(personActivity);

typedef struct {
	int id; // 定时器ID ， 不能重复
	int time; // 定时器  时间间隔  单位 毫秒
}S_ACTIVITY_TIMEER;

#include "logic/personLogic.cc"

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
    ID_PERSON_Button1, onButtonClick_Button1,
    ID_PERSON_BtnDeleteUserFinger, onButtonClick_BtnDeleteUserFinger,
    ID_PERSON_BtnClearFinger1, onButtonClick_BtnClearFinger1,
    ID_PERSON_BtnPicture, onButtonClick_BtnPicture,
    ID_PERSON_BtnGetIDFeature, onButtonClick_BtnGetIDFeature,
    ID_PERSON_BtnReadCurrentFeature, onButtonClick_BtnReadCurrentFeature,
    ID_PERSON_BtnUpdateServer, onButtonClick_BtnUpdateServer,
    ID_PERSON_BtnSetTimeout, onButtonClick_BtnSetTimeout,
    ID_PERSON_BtnReadTimeout, onButtonClick_BtnReadTimeout,
    ID_PERSON_BtnClearFinger, onButtonClick_BtnClearFinger,
    ID_PERSON_Button2, onButtonClick_Button2,
    ID_PERSON_BtnQuaryPerson, onButtonClick_BtnQuaryPerson,
};
/***************/


typedef void (*SeekBarCallback)(ZKSeekBar *pSeekBar, int progress);
typedef struct {
    int id;
    SeekBarCallback callback;
}S_ZKSeekBarCallback;
/*TAG:SeekBarCallbackTab*/
static S_ZKSeekBarCallback SZKSeekBarCallbackTab[] = {
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
    ID_PERSON_EditInstruction, onEditTextChanged_EditInstruction,
    ID_PERSON_EditPersonID, onEditTextChanged_EditPersonID,
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


personActivity::personActivity() {
	//todo add init code here
	mVideoLoopIndex = 0;
	mVideoLoopErrorCount = 0;
}

personActivity::~personActivity() {
	//todo add init file here
    // 退出应用时需要反注册
    EASYUICONTEXT->unregisterGlobalTouchListener(this);
    onUI_quit();
    unregisterProtocolDataUpdateListener(onProtocolDataUpdate);
}

const char* personActivity::getAppName() const{
	return "person.ftu";
}

//TAG:onCreate
void personActivity::onCreate() {
	Activity::onCreate();
    mTextFingerOnlineStatePtr = (ZKTextView*)findControlByID(ID_PERSON_TextFingerOnlineState);
    mTextview8Ptr = (ZKTextView*)findControlByID(ID_PERSON_Textview8);
    mTvConnectStatePtr = (ZKTextView*)findControlByID(ID_PERSON_TvConnectState);
    mTextview9Ptr = (ZKTextView*)findControlByID(ID_PERSON_Textview9);
    mWindStatePtr = (ZKWindow*)findControlByID(ID_PERSON_WindState);
    mTextFingerTotalNumPtr = (ZKTextView*)findControlByID(ID_PERSON_TextFingerTotalNum);
    mButton1Ptr = (ZKButton*)findControlByID(ID_PERSON_Button1);
    mTextview10Ptr = (ZKTextView*)findControlByID(ID_PERSON_Textview10);
    mTextFingerIDListPtr = (ZKTextView*)findControlByID(ID_PERSON_TextFingerIDList);
    mTextFingerNumPtr = (ZKTextView*)findControlByID(ID_PERSON_TextFingerNum);
    mTextview7Ptr = (ZKTextView*)findControlByID(ID_PERSON_Textview7);
    mBtnDeleteUserFingerPtr = (ZKButton*)findControlByID(ID_PERSON_BtnDeleteUserFinger);
    mBtnClearFinger1Ptr = (ZKButton*)findControlByID(ID_PERSON_BtnClearFinger1);
    mTextview5Ptr = (ZKTextView*)findControlByID(ID_PERSON_Textview5);
    mEditInstructionPtr = (ZKEditText*)findControlByID(ID_PERSON_EditInstruction);if(mEditInstructionPtr!= NULL){mEditInstructionPtr->setTextChangeListener(this);}
    mBtnPicturePtr = (ZKButton*)findControlByID(ID_PERSON_BtnPicture);
    mBtnGetIDFeaturePtr = (ZKButton*)findControlByID(ID_PERSON_BtnGetIDFeature);
    mBtnReadCurrentFeaturePtr = (ZKButton*)findControlByID(ID_PERSON_BtnReadCurrentFeature);
    mBtnUpdateServerPtr = (ZKButton*)findControlByID(ID_PERSON_BtnUpdateServer);
    mBtnSetTimeoutPtr = (ZKButton*)findControlByID(ID_PERSON_BtnSetTimeout);
    mBtnReadTimeoutPtr = (ZKButton*)findControlByID(ID_PERSON_BtnReadTimeout);
    mTextFingerStatePtr = (ZKTextView*)findControlByID(ID_PERSON_TextFingerState);
    mBtnClearFingerPtr = (ZKButton*)findControlByID(ID_PERSON_BtnClearFinger);
    mTextPersonIDPtr = (ZKTextView*)findControlByID(ID_PERSON_TextPersonID);
    mTextPersonLevelPtr = (ZKTextView*)findControlByID(ID_PERSON_TextPersonLevel);
    mTextPersonNamePtr = (ZKTextView*)findControlByID(ID_PERSON_TextPersonName);
    mTextStatusNotice2Ptr = (ZKTextView*)findControlByID(ID_PERSON_TextStatusNotice2);
    mTextStatusNoticePtr = (ZKTextView*)findControlByID(ID_PERSON_TextStatusNotice);
    mWindStatusNoticePtr = (ZKWindow*)findControlByID(ID_PERSON_WindStatusNotice);
    mTextview6Ptr = (ZKTextView*)findControlByID(ID_PERSON_Textview6);
    mButton2Ptr = (ZKButton*)findControlByID(ID_PERSON_Button2);
    mTextview4Ptr = (ZKTextView*)findControlByID(ID_PERSON_Textview4);
    mTextview3Ptr = (ZKTextView*)findControlByID(ID_PERSON_Textview3);
    mEditPersonIDPtr = (ZKEditText*)findControlByID(ID_PERSON_EditPersonID);if(mEditPersonIDPtr!= NULL){mEditPersonIDPtr->setTextChangeListener(this);}
    mTextview2Ptr = (ZKTextView*)findControlByID(ID_PERSON_Textview2);
    mTextview1Ptr = (ZKTextView*)findControlByID(ID_PERSON_Textview1);
    mBtnQuaryPersonPtr = (ZKButton*)findControlByID(ID_PERSON_BtnQuaryPerson);
	mActivityPtr = this;
	onUI_init();
    registerProtocolDataUpdateListener(onProtocolDataUpdate); 
    rigesterActivityTimer();
}

void personActivity::onClick(ZKBase *pBase) {
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

void personActivity::onResume() {
	Activity::onResume();
	EASYUICONTEXT->registerGlobalTouchListener(this);
	startVideoLoopPlayback();
	onUI_show();
}

void personActivity::onPause() {
	Activity::onPause();
	EASYUICONTEXT->unregisterGlobalTouchListener(this);
	stopVideoLoopPlayback();
	onUI_hide();
}

void personActivity::onIntent(const Intent *intentPtr) {
	Activity::onIntent(intentPtr);
	onUI_intent(intentPtr);
}

bool personActivity::onTimer(int id) {
	return onUI_Timer(id);
}

void personActivity::onProgressChanged(ZKSeekBar *pSeekBar, int progress){

    int seekBarTablen = sizeof(SZKSeekBarCallbackTab) / sizeof(S_ZKSeekBarCallback);
    for (int i = 0; i < seekBarTablen; ++i) {
        if (SZKSeekBarCallbackTab[i].id == pSeekBar->getID()) {
            SZKSeekBarCallbackTab[i].callback(pSeekBar, progress);
            break;
        }
    }
}

int personActivity::getListItemCount(const ZKListView *pListView) const{
    int tablen = sizeof(SListViewFunctionsCallbackTab) / sizeof(S_ListViewFunctionsCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SListViewFunctionsCallbackTab[i].id == pListView->getID()) {
            return SListViewFunctionsCallbackTab[i].getListItemCountCallback(pListView);
            break;
        }
    }
    return 0;
}

void personActivity::obtainListItemData(ZKListView *pListView,ZKListView::ZKListItem *pListItem, int index){
    int tablen = sizeof(SListViewFunctionsCallbackTab) / sizeof(S_ListViewFunctionsCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SListViewFunctionsCallbackTab[i].id == pListView->getID()) {
            SListViewFunctionsCallbackTab[i].obtainListItemDataCallback(pListView, pListItem, index);
            break;
        }
    }
}

void personActivity::onItemClick(ZKListView *pListView, int index, int id){
    int tablen = sizeof(SListViewFunctionsCallbackTab) / sizeof(S_ListViewFunctionsCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SListViewFunctionsCallbackTab[i].id == pListView->getID()) {
            SListViewFunctionsCallbackTab[i].onItemClickCallback(pListView, index, id);
            break;
        }
    }
}

void personActivity::onSlideItemClick(ZKSlideWindow *pSlideWindow, int index) {
    int tablen = sizeof(SSlideWindowItemClickCallbackTab) / sizeof(S_SlideWindowItemClickCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SSlideWindowItemClickCallbackTab[i].id == pSlideWindow->getID()) {
            SSlideWindowItemClickCallbackTab[i].onSlideItemClickCallback(pSlideWindow, index);
            break;
        }
    }
}

bool personActivity::onTouchEvent(const MotionEvent &ev) {
    return onpersonActivityTouchEvent(ev);
}

void personActivity::onTextChanged(ZKTextView *pTextView, const std::string &text) {
    int tablen = sizeof(SEditTextInputCallbackTab) / sizeof(S_EditTextInputCallback);
    for (int i = 0; i < tablen; ++i) {
        if (SEditTextInputCallbackTab[i].id == pTextView->getID()) {
            SEditTextInputCallbackTab[i].onEditTextChangedCallback(text);
            break;
        }
    }
}

void personActivity::rigesterActivityTimer() {
    int tablen = sizeof(REGISTER_ACTIVITY_TIMER_TAB) / sizeof(S_ACTIVITY_TIMEER);
    for (int i = 0; i < tablen; ++i) {
        S_ACTIVITY_TIMEER temp = REGISTER_ACTIVITY_TIMER_TAB[i];
        registerTimer(temp.id, temp.time);
    }
}


void personActivity::onVideoPlayerMessage(ZKVideoView *pVideoView, int msg) {
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

void personActivity::videoLoopPlayback(ZKVideoView *pVideoView, int msg, int callbackTabIndex) {

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

void personActivity::startVideoLoopPlayback() {
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

void personActivity::stopVideoLoopPlayback() {
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

bool personActivity::parseVideoFileList(const char *pFileListPath, std::vector<string>& mediaFileList) {
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

int personActivity::removeCharFromString(string& nString, char c) {
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

void personActivity::registerUserTimer(int id, int time) {
	registerTimer(id, time);
}

void personActivity::unregisterUserTimer(int id) {
	unregisterTimer(id);
}

void personActivity::resetUserTimer(int id, int time) {
	resetTimer(id, time);
}