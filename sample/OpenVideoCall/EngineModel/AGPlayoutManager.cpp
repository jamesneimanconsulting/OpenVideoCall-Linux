#include "AGPlayoutManager.h"
#include "IAgoraRtcEngine.h"

AGPlayoutManager::AGPlayoutManager()
    : m_deviceManager(NULL)
      , m_collection(NULL)
{
}

AGPlayoutManager::~AGPlayoutManager()
{
    close();
}

bool AGPlayoutManager::create(IRtcEngine *rtcEngine)
{
    m_deviceManager = new AAudioDeviceManager(rtcEngine);
    if (m_deviceManager == NULL || m_deviceManager->get() == NULL)
        return false;

    m_collection = (*m_deviceManager)->enumeratePlaybackDevices();
    if (m_collection == NULL) {
        delete m_deviceManager;
        m_deviceManager = NULL;
    }

    return m_collection != NULL ? true : false;
}

void AGPlayoutManager::close()
{
    if (m_collection != NULL){
        m_collection->release();
        m_collection = NULL;
    }

    if (m_deviceManager != NULL) {
        delete m_deviceManager;
        m_deviceManager = NULL;
    }
}

bool AGPlayoutManager::getVolume(int& vol)
{
    if (m_deviceManager == NULL || m_deviceManager->get() == NULL)
        return false;

    int ret = (*m_deviceManager)->getPlaybackDeviceVolume(&vol);

    return ret == 0 ? true : false;
}

bool AGPlayoutManager::setVolume(uint8_t vol)
{
    if (m_deviceManager == NULL || m_deviceManager->get() == NULL)
        return 0;

    int ret = (*m_deviceManager)->setPlaybackDeviceVolume((int)vol);

    return ret == 0 ? true : false;
}

uint8_t AGPlayoutManager::getDeviceCount()
{
    if (m_collection == NULL)
        return 0;

    return (uint8_t)m_collection->getCount();
}

bool AGPlayoutManager::getDevice(uint8_t index, string &deviceName, string &deviceId)
{
    char name[MAX_DEVICE_ID_LENGTH];
    char id[MAX_DEVICE_ID_LENGTH];

    if (index >= getDeviceCount())
        return false;

    int ret = m_collection->getDevice(index, name, id);
    if (ret != 0)
        return false;

    deviceName.assign(name);
    deviceId.assign(id);

    return true;
}

bool AGPlayoutManager::getCurDeviceId(string& id)
{
    char deviceId[MAX_DEVICE_ID_LENGTH];

    if (m_deviceManager == NULL || m_deviceManager->get() == NULL)
        return false;

    (*m_deviceManager)->getPlaybackDevice(deviceId);

    id.assign(deviceId);

    return true;
}

bool AGPlayoutManager::setCurDevice(const char* deviceId)
{
    if (m_deviceManager == NULL || m_deviceManager->get() == NULL)
        return false;

    int ret = (*m_deviceManager)->setPlaybackDevice(deviceId);

    return ret == 0 ? true : false;
}

