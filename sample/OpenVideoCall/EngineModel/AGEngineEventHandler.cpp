#include "AGEngineEventHandler.h"
#include "AGEventDef.h"
#include "IAGEventReceiver.h"
#include <cstring>
#include <iostream>

AGEngineEventHandler::AGEngineEventHandler()
{
    m_receiver = NULL;
}

AGEngineEventHandler::~AGEngineEventHandler()
{
}

void AGEngineEventHandler::setEventReceiver(IAGEventReceiver* receiver)
{
    m_receiver = receiver;
}

void AGEngineEventHandler::onJoinChannelSuccess(const char* channel, uid_t uid, int elapsed)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_JOINCHANNEL_SUCCESS, NULL);
}

void AGEngineEventHandler::onRejoinChannelSuccess(const char* channel, uid_t uid, int elapsed)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_REJOINCHANNEL_SUCCESS, NULL);
}

void AGEngineEventHandler::onWarning(int warn, const char* msg)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_WARNING, NULL);
}

void AGEngineEventHandler::onError(int err, const char* msg)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_ERROR, NULL);
}

void AGEngineEventHandler::onAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_AUDIO_QUALITY, NULL); 
} 

void AGEngineEventHandler::onLeaveChannel(const RtcStats& stat)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_LEAVE_CHANNEL, NULL);
}

void AGEngineEventHandler::onRtcStats(const RtcStats& stat)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_RTC_STAT, NULL);
}

void AGEngineEventHandler::onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_AUDIO_DEVICE_STATE_CHANGED, NULL);
}

void AGEngineEventHandler::onUserJoined(uid_t uid, int elapsed)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_USER_JOINED, NULL);
}

void AGEngineEventHandler::onUserOffline(uid_t uid, USER_OFFLINE_REASON_TYPE reason)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_USER_OFFLINE, NULL);
}

void AGEngineEventHandler::onUserMuteAudio(uid_t uid, bool muted)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_USER_MUTE_AUDIO, NULL);
}

void AGEngineEventHandler::onUserMuteVideo(uid_t uid, bool muted)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_USER_MUTE_VIDEO, NULL);
}

void AGEngineEventHandler::onCameraReady()
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_CAMERA_READY, NULL);
}

void AGEngineEventHandler::onConnectionLost()
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_CONNECTION_LOST, NULL);
}

void AGEngineEventHandler::onConnectionInterrupted()
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_CONNECTION_INTERRUPTED, NULL);
}

void AGEngineEventHandler::onUserEnableVideo(uid_t uid, bool enabled)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_USER_ENABLE_VIDEO, NULL);
}

