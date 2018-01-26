#pragma once

#include"Controller/MsgHandler.h"
#include"IAGEventReceiver.h"
#include"AGEngineEventHandler.h"
#include"AgoraDefs.h"

class EngineController;
class AGEngine;
class AGCameraManager;
class AGAudInputManager;
class AGPlayoutManager;

class AGEngineModel : public MsgHandler
                      ,public IAGEventReceiver
{
    public:
        static AGEngineModel* Get();

        //event callback handler
        void onEvent(int id, void* pData);

        void initialize();

    private:
        AGEngineModel();
        ~AGEngineModel();

        //message handler
        bool onOpenMsg(void* msg);
        bool onCloseMsg(void* msg);
        bool onEnableVideoMsg(void* msg);
        bool onEnableAudioMsg(void* msg);
        bool onEnableLocalVideoMsg(void* msg);
        bool onEnableLocalAudioMsg(void* msg);
        bool onConfigureMsg(void* msg);
        bool onPrintDeviceInfoMsg(void* msg);
        bool onSetCurCameraMsg(void* msg); 
        bool onGetPlayoutVolMsg(void* msg);
        bool onGetInputVolMsg(void* msg);
        bool onSetPlayoutVolMsg(void* msg);
        bool onSetInputVolMsg(void* msg);
        bool onExitMsg(void* msg); 

        void release(); 
    private:
        AGEngineEventHandler m_engineEventHandler;
        AGEngine*   m_engine;
        AGCameraManager*  m_cameraMgr;
        AGAudInputManager* m_audInMgr;
        AGPlayoutManager* m_playoutMgr;

        AppConfig m_cfg;

    private:
        static AGEngineModel m_model; 
};

