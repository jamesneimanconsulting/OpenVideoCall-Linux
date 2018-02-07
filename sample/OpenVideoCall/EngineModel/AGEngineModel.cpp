#include"AGEngineModel.h"
#include"AGEngine.h"
#include"AGCameraManager.h"
#include"AGAudInputManager.h"
#include"AGPlayoutManager.h"
#include"AGEventDef.h"
#include"AGFrameObserver.h"

#include<iostream>
#include<string>

using std::cout;
using std::endl;
using std::string;
using std::stringstream;

AGEngineModel AGEngineModel::m_model;

AGEngineModel* AGEngineModel::Get() {
    return &m_model;
}

AGEngineModel::AGEngineModel() {
    m_engine = NULL;
    m_cameraMgr = NULL;
    m_audInMgr = NULL;
    m_playoutMgr = NULL;
    m_audioObserver = NULL;
    m_videoObserver = NULL;

    registerHandler(MSG_OPEN,(handler_ptr)&AGEngineModel::onOpenMsg);
    registerHandler(MSG_CLOSE, (handler_ptr)&AGEngineModel::onCloseMsg);
    registerHandler(MSG_CONFIGURE, (handler_ptr)&AGEngineModel::onConfigureMsg);
    registerHandler(MSG_ENABLE_VIDEO, (handler_ptr)&AGEngineModel::onEnableVideoMsg);
    registerHandler(MSG_ENABLE_AUDIO, (handler_ptr)&AGEngineModel::onEnableAudioMsg);
    registerHandler(MSG_ENABLE_LOCAL_VIDEO, (handler_ptr)&AGEngineModel::onEnableLocalVideoMsg);
    registerHandler(MSG_ENABLE_LOCAL_AUDIO, (handler_ptr)&AGEngineModel::onEnableLocalAudioMsg);
    registerHandler(MSG_PRINT_DEVICE_INFO, (handler_ptr)&AGEngineModel::onPrintDeviceInfoMsg);
    registerHandler(MSG_SET_CUR_CAMERA, (handler_ptr)&AGEngineModel::onSetCurCameraMsg);
    registerHandler(MSG_GET_PLAYOUT_VOL, (handler_ptr)&AGEngineModel::onGetPlayoutVolMsg);
    registerHandler(MSG_GET_INPUT_VOL, (handler_ptr)&AGEngineModel::onGetInputVolMsg);
    registerHandler(MSG_SET_PLAYOUT_VOL, (handler_ptr)&AGEngineModel::onSetPlayoutVolMsg);
    registerHandler(MSG_SET_INPUT_VOL, (handler_ptr)&AGEngineModel::onSetInputVolMsg);
    registerHandler(MSG_EXIT, (handler_ptr)&AGEngineModel::onExitMsg);
    registerHandler(MSG_REGISTER_VIDEO_FRAME_OBSERVER , (handler_ptr)&AGEngineModel::onRegisterVideoFrameObserver);
    registerHandler(MSG_REGISTER_AUDIO_FRAME_OBSERVER , (handler_ptr)&AGEngineModel::onRegisterAudioFrameObserver);

    m_engineEventHandler.setEventReceiver(this);
}

AGEngineModel::~AGEngineModel() {
    release();
}

void AGEngineModel::initialize() {
    if(!m_engine)
        m_engine = new AGEngine(&m_engineEventHandler, m_cfg.appId.c_str());

    if(!m_cameraMgr) 
        m_cameraMgr = new AGCameraManager();

    if(!m_audInMgr) 
        m_audInMgr = new AGAudInputManager();

    if(!m_playoutMgr)
        m_playoutMgr = new AGPlayoutManager();
}

bool AGEngineModel::onOpenMsg(void* msg) {
    cout << "AgoraRtcEngine:open" <<endl;

    if(m_engine) {
        m_engine->enableVideo(m_cfg.enableVideo);

        m_engine->enableAudio(m_cfg.enableAudio);

        m_engine->muteLocalVideo(!m_cfg.enableLocalVideo);

        m_engine->muteLocalAudio(!m_cfg.enableLocalAudio);

        m_engine->setVideoProfile(m_cfg.videoProfile);

        m_engine->setAudioProfile(m_cfg.audioProfile, m_cfg.audioScenario);

        m_engine->enableWebSdkInteroperability(m_cfg.enableWebSdkInteroperability);

        return m_engine->joinChannel(m_cfg.channelId.c_str(), m_cfg.uid, m_cfg.channelProfile); 
    }

    return false;
}

bool AGEngineModel::onCloseMsg(void* msg) {
    cout << "AgoraRtcEngine:close" <<endl;

    if(m_cameraMgr)
        m_cameraMgr->close();
    
    if(m_audInMgr)
        m_audInMgr->close();

    if(m_playoutMgr)
        m_playoutMgr->close();

    if(m_engine)  
        return m_engine->leaveChannel(); 

    return false;
}

bool AGEngineModel::onEnableVideoMsg(void* msg) {
    bool enable = *(reinterpret_cast<bool*>(msg));

    if(enable != m_cfg.enableVideo && m_engine) {
        m_cfg.enableVideo =  enable;
        cout << "AgoraRtcEngine: enable video: " << enable <<endl;
        return m_engine->enableVideo(enable);
    } else {
        cout << "AgoraRtcEngine: already enabled video: " << enable <<endl;
        return false;
    }
}

bool AGEngineModel::onEnableAudioMsg(void* msg) {
    bool enable = *(reinterpret_cast<bool*>(msg));

    if(enable != m_cfg.enableAudio && m_engine) {
        m_cfg.enableAudio =  enable;

        cout << "AgoraRtcEngine: enable audio: " << enable <<endl;
        return m_engine->enableAudio(enable);
    } else {
        cout << "AgoraRtcEngine: already enabled audio: " << enable <<endl;
        return false;
    }
}

bool AGEngineModel::onEnableLocalVideoMsg(void* msg) {
    bool enable = *(reinterpret_cast<bool*>(msg));

    if(enable != m_cfg.enableLocalVideo && m_engine) {
        m_cfg.enableLocalVideo =  enable;

        cout << "AgoraRtcEngine: enable local video: " << enable <<endl;
        return m_engine->muteLocalVideo(!m_cfg.enableLocalVideo);
    } else {
        cout << "AgoraRtcEngine: already enabled local video: " << enable <<endl;
        return false;
    }
}

bool AGEngineModel::onEnableLocalAudioMsg(void* msg) {
    bool enable = *(reinterpret_cast<bool*>(msg));

    if(enable != m_cfg.enableLocalAudio && m_engine) {
        m_cfg.enableLocalAudio =  enable;
        cout << "AgoraRtcEngine: enable local audio: " << enable <<endl;
        return m_engine->muteLocalAudio(!m_cfg.enableLocalAudio);
    } else {
        cout << "AgoraRtcEngine: already enabled local audio: " << enable <<endl;
        return false;
    }
}

bool AGEngineModel::onConfigureMsg(void* msg) {
    AppConfig* cfg = reinterpret_cast<AppConfig*>(msg);
    m_cfg = *cfg;

    cout << "model onConfigureMsg"<<endl;
    return true;
}

bool AGEngineModel::onPrintDeviceInfoMsg(void* msg) {
    cout << "model onPrintDeviceInfoMsg"<<endl;

    int cameraCnt = m_cameraMgr->getDeviceCount();
    cout <<"camera device number is:" << cameraCnt<< endl;
    cout <<"camera device list:" << endl;
    for(int i = 0; i < cameraCnt; ++i) {
        string deviceId;
        string deviceName;
        if(m_cameraMgr->getDevice(i , deviceName, deviceId)) {
            cout <<"device index: "<< i<<",  device name: "<< deviceName <<",  device Id: " << deviceId << endl;
        }
    }
    string curDeviceId;
    if(m_cameraMgr->getCurDeviceId(curDeviceId)) 
        cout <<"current camera device id is:" << curDeviceId << endl;

    cout <<"audio input device number is:" << (uint32_t)m_audInMgr->getDeviceCount() << endl;
    //cout <<"current audio input device id is:" << auInputId << endl;

    cout <<"audio playout device number is:" << (uint32_t)m_playoutMgr->getDeviceCount() << endl;
    //cout <<"current audio playout device id is:" << auPlayoutId << endl;

    return true;
}

bool AGEngineModel::onExitMsg(void* msg) {
    if(m_cameraMgr)
        m_cameraMgr->close();

    if(m_audInMgr)
        m_audInMgr->close();

    if(m_playoutMgr)
        m_playoutMgr->close();

    if(m_engine) {
        m_engine->leaveChannel();
        m_engine->release();
    }

    release();

    return true;
}

bool AGEngineModel::onSetCurCameraMsg(void* msg) {
    string* deviceId = reinterpret_cast<string*>(msg);
    if(!m_cameraMgr)
        return false;

    return m_cameraMgr->setCurDevice(deviceId->c_str());
}

bool AGEngineModel::onGetPlayoutVolMsg(void* msg) {
    int* vol = reinterpret_cast<int*>(msg);
    if(!m_playoutMgr)
        return false;

    return m_playoutMgr->getVolume(*vol);
}

bool AGEngineModel::onGetInputVolMsg(void* msg) {
    int* vol = reinterpret_cast<int*>(msg);
    if(!m_audInMgr)
        return false;

    return m_audInMgr->getVolume(*vol);
}

bool AGEngineModel::onSetInputVolMsg(void* msg) {
    int* vol = reinterpret_cast<int*>(msg);
    if(!m_audInMgr)
        return false;

    return m_audInMgr->setVolume(*vol);
}

bool AGEngineModel::onSetPlayoutVolMsg(void* msg) {
    int* vol = reinterpret_cast<int*>(msg);
    if(!m_playoutMgr)
        return false;

    return m_playoutMgr->setVolume(*vol);
}

bool AGEngineModel::onRegisterAudioFrameObserver(void* msg) {
    bool* filter = reinterpret_cast<bool*>(msg);

    if(m_audioObserver == NULL) {
        m_audioObserver = new AGAudioFrameObserver();
    }

    m_audioObserver->setFilter(*filter);

    if(*filter)
        return m_engine->registerAudioFrameObserver(m_audioObserver);
    else
        return m_engine->registerAudioFrameObserver(NULL);
}

bool AGEngineModel::onRegisterVideoFrameObserver(void* msg) {
    bool* filter = reinterpret_cast<bool*>(msg);

    if(m_videoObserver == NULL) {
        m_videoObserver = new AGVideoFrameObserver();
    }

    m_videoObserver->setFilter(*filter);

    if(*filter)
        return m_engine->registerVideoFrameObserver(m_videoObserver);
    else
        return m_engine->registerVideoFrameObserver(NULL);
}

void AGEngineModel::release() {
    if(m_cameraMgr) {
        delete m_cameraMgr;
        m_cameraMgr = NULL;
    }

    if(m_audInMgr) {
        delete m_audInMgr;
        m_audInMgr = NULL;
    }

    if(m_playoutMgr) {
        delete m_playoutMgr;
        m_playoutMgr = NULL;
    }

    if(m_engine) {
        m_engine->registerVideoFrameObserver(NULL);
        m_engine->registerAudioFrameObserver(NULL);
        
        if(m_audioObserver) {
            delete m_audioObserver;
            m_audioObserver = NULL;
        }

        if(m_videoObserver) {
            delete m_videoObserver;
            m_videoObserver = NULL;
        }

        delete m_engine;
        m_engine = NULL;
    }
}

void AGEngineModel::onEvent(int id, void* pData) {
    switch(id) {
        case EID_JOINCHANNEL_SUCCESS: 
            m_cameraMgr->create(m_engine->getRtcEngine());
            m_audInMgr->create(m_engine->getRtcEngine());
            m_playoutMgr->create(m_engine->getRtcEngine());
            break;
    }
}

