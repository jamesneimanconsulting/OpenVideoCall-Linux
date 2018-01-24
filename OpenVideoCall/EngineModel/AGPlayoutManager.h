#pragma once
#include <cstdint>
#include <string>

namespace agora {
    namespace rtc {
        class IRtcEngine;
        class AAudioDeviceManager;
        class IAudioDeviceCollection;
    }
}

using std::string;
using namespace agora::rtc;

class AGPlayoutManager
{
    public:
        AGPlayoutManager();
        ~AGPlayoutManager();

        bool create(IRtcEngine* rtcEngine);
        void close();

        uint8_t getVolume();
        bool setVolume(uint8_t vol);
        uint8_t getDeviceCount();

        bool getCurDeviceId(string& id);
        bool setCurDevice(const char* deviceId);

        bool getDevice(uint8_t index, string &deviceName, string &deviceId);
    private:
        AAudioDeviceManager			*m_deviceManager;
        IAudioDeviceCollection		*m_collection;
};

