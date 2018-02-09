#include"AGFrameObserver.h"
#include<iostream>
#include<memory.h>

AGAudioFrameObserver::AGAudioFrameObserver() {
}

AGAudioFrameObserver::~AGAudioFrameObserver() {
}

bool AGAudioFrameObserver::onMixedAudioFrame(IAudioFrameObserver::AudioFrame &audioFrame) {
//    std::cout<<"onMixedAudioFrame"<<std::endl;
    if(m_filter != 1)
        return true;

    saveAudioFrame(0, audioFrame, "onMixedAudioFrame");
    return true;
}

bool AGAudioFrameObserver::onPlaybackAudioFrame(IAudioFrameObserver::AudioFrame &audioFrame) {
//   std::cout<<"onPlaybackAudioFrame"<<std::endl;
    if(m_filter != 2)
        return true;

    saveAudioFrame(0, audioFrame, "onPlaybackAudioFrame");
    return true;
}

bool AGAudioFrameObserver::onRecordAudioFrame(IAudioFrameObserver::AudioFrame &audioFrame) {
//    std::cout<<"onRecordAudioFrame"<<std::endl;
    if(m_filter != 3)
        return true;

    saveAudioFrame(0, audioFrame, "onRecordAudioFrame");
    return true;
}

bool AGAudioFrameObserver::onPlaybackAudioFrameBeforeMixing(unsigned int uid, IAudioFrameObserver::AudioFrame& audioFrame) {
//   std::cout<<"onPlaybackAudioFrameBeforeMixing"<<std::endl;
    if(m_filter != 4)
        return true;

    saveAudioFrame(uid, audioFrame, "onPlaybackAudioFrameBeforeMixing");
    return true;
}

void AGAudioFrameObserver::saveAudioFrame(int uid, const IAudioFrameObserver::AudioFrame& audioFrame, const char* tag) {
    std::string info_name = std::string(tag); 
    info_name += "_";

    char uidbuf[65];
    snprintf(uidbuf, sizeof(uidbuf),"%u", uid);
    info_name += std::string(uidbuf); 
    info_name += "_";

    char channelsbuf[20];
    snprintf(channelsbuf, sizeof(channelsbuf),"%u", audioFrame.channels);
    info_name += std::string(channelsbuf);
    info_name += "_";

    char bitRatebuf[20];
    snprintf(bitRatebuf, sizeof(bitRatebuf),"%u", audioFrame.samplesPerSec);
    info_name += std::string(bitRatebuf);
    info_name += ".pcm";  

    const uint8_t* data = static_cast<const uint8_t*>(audioFrame.buffer);
    uint32_t size = audioFrame.bytesPerSample * audioFrame.samples * audioFrame.channels;

    FILE *fp = fopen(info_name.c_str(), "a+b");
    ::fwrite(data, 1, size, fp);
    ::fclose(fp);
}


AGVideoFrameObserver::AGVideoFrameObserver() {
}

AGVideoFrameObserver::~AGVideoFrameObserver() {
}

bool AGVideoFrameObserver::onCaptureVideoFrame(IVideoFrameObserver::VideoFrame &videoFrame) {
//    std::cout<<"onCaptureVideoFrame"<<std::endl;
    if(m_filter != 1)
        return true;

    int width = videoFrame.width;
    int height = videoFrame.height;

    memset(videoFrame.uBuffer, 128, videoFrame.uStride*height / 2);
    memset(videoFrame.vBuffer, 128, videoFrame.vStride*height / 2);
    return true;
}

bool AGVideoFrameObserver::onRenderVideoFrame(unsigned int uid, VideoFrame& videoFrame) {
    //   std::cout<<"onRenderVideoFrame"<<std::endl;
    if(m_filter != 2)
        return true;

    saveVideoFrame(uid, videoFrame, "onRenderVideoFrame"); 
    return true;
}

void AGVideoFrameObserver::saveVideoFrame(int uid, const IVideoFrameObserver::VideoFrame& videoFrame, const char* tag) {
    std::string info_name = std::string(tag); 
    info_name += "_";

    char uidbuf[65];
    snprintf(uidbuf, sizeof(uidbuf),"%u", uid);
    info_name += std::string(uidbuf);

    info_name += "_";
    char yStrideBuf[20];
    snprintf(yStrideBuf, sizeof(yStrideBuf),"%u", videoFrame.yStride);
    info_name += std::string(yStrideBuf);

    info_name += "_";
    char uStrideBuf[20];
    snprintf(uStrideBuf, sizeof(uStrideBuf),"%u", videoFrame.uStride);
    info_name += std::string(yStrideBuf);

    info_name += "_";
    char vStrideBuf[20];
    snprintf(vStrideBuf, sizeof(vStrideBuf),"%u", videoFrame.vStride);
    info_name += std::string(vStrideBuf);

    int y_size = videoFrame.height * videoFrame.yStride;
    int u_size = videoFrame.height * videoFrame.uStride / 2;
    int v_size = videoFrame.height * videoFrame.vStride / 2;

    FILE *fp = fopen(info_name.c_str(), "a+b");
    ::fwrite(videoFrame.yBuffer, 1, y_size, fp);
    ::fwrite(videoFrame.uBuffer, 1, u_size, fp);
    ::fwrite(videoFrame.vBuffer, 1, v_size, fp);

    ::fclose(fp);
}

