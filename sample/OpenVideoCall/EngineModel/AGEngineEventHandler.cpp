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
}

void AGEngineEventHandler::onError(int err, const char* msg)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_ERROR, NULL);
}

void AGEngineEventHandler::onAudioQuality(uid_t uid, int quality, unsigned short delay, unsigned short lost)
{
    if(m_receiver != NULL) m_receiver->onEvent(EID_AUDIO_QUALITY, NULL); } void AGEngineEventHandler::onAudioVolumeIndication(const AudioVolumeInfo* speakers, unsigned int speakerNumber, int totalVolume)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_AUDIO_VOLUME_INDICATION, NULL);
}

void AGEngineEventHandler::onLeaveChannel(const RtcStats& stat)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_LEAVE_CHANNEL, NULL);
}

void AGEngineEventHandler::onRtcStats(const RtcStats& stat)
{
}

void AGEngineEventHandler::onMediaEngineEvent(int evt)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_MEDIA_ENGINE_EVENT, NULL);
}

void AGEngineEventHandler::onAudioDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_AUDIO_DEVICE_STATE_CHANGED, NULL);
}

void AGEngineEventHandler::onVideoDeviceStateChanged(const char* deviceId, int deviceType, int deviceState)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_VIDEO_DEVICE_STATE_CHANGED, NULL);
}

void AGEngineEventHandler::onLastmileQuality(int quality)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_LASTMILE_QUALITY, NULL);
}

void AGEngineEventHandler::onFirstLocalVideoFrame(int width, int height, int elapsed)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_FIRST_LOCAL_VIDEO_FRAME, NULL);
}

void AGEngineEventHandler::onFirstRemoteVideoDecoded(uid_t uid, int width, int height, int elapsed)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_FIRST_REMOTE_VIDEO_DECODED, NULL);
}

void AGEngineEventHandler::onFirstRemoteVideoFrame(uid_t uid, int width, int height, int elapsed)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_FIRST_REMOTE_VIDEO_FRAME, NULL);
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

void AGEngineEventHandler::onStreamMessage(uid_t uid, int streamId, const char* data, size_t length)
{
    if (m_receiver != NULL)
        m_receiver->onEvent(EID_STREAM_MESSAGE, NULL);
}

void AGEngineEventHandler::onApiCallExecuted(const char* api, int error)
{
    if (m_receiver != NULL)
        m_receiver->onEvent(EID_APICALL_EXECUTED, NULL);
}

void AGEngineEventHandler::onLocalVideoStats(const LocalVideoStats& stats)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_LOCAL_VIDEO_STAT, NULL);
}

void AGEngineEventHandler::onRemoteVideoStats(const RemoteVideoStats& stats)
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_REMOTE_VIDEO_STAT, NULL);
}

void AGEngineEventHandler::onCameraReady()
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_CAMERA_READY, NULL);
}

void AGEngineEventHandler::onVideoStopped()
{
    if (m_receiver != NULL)
        m_receiver->onEvent(EID_VIDEO_STOPPED, NULL);
}

void AGEngineEventHandler::onConnectionLost()
{
    if(m_receiver != NULL)
        m_receiver->onEvent(EID_CONNECTION_LOST, NULL);
}

void AGEngineEventHandler::onConnectionInterrupted()
{

}

void AGEngineEventHandler::onUserEnableVideo(uid_t uid, bool enabled)
{
}

void AGEngineEventHandler::onStartRecordingService(int error)
{
    if (m_receiver != NULL)
        m_receiver->onEvent(EID_START_RCDSRV, NULL);
}

void AGEngineEventHandler::onStopRecordingService(int error)
{
    if (m_receiver != NULL)
        m_receiver->onEvent(EID_STOP_RCDSRV, NULL);
}

void AGEngineEventHandler::onRefreshRecordingServiceStatus(int status)
{
    if (m_receiver != NULL)
        m_receiver->onEvent(EID_REFREASH_RCDSRV, NULL);
}
