#include "AGAudInputManager.h"
#include "IAgoraRtcEngine.h"

AGAudInputManager::AGAudInputManager()
    : m_deviceManager(NULL)
    , m_collection(NULL)
{
}

AGAudInputManager::~AGAudInputManager()
{
    close();
}

bool AGAudInputManager::create(IRtcEngine *rtcEngine)
{
    m_deviceManager = new AAudioDeviceManager(rtcEngine);
    if (m_deviceManager == NULL || m_deviceManager->get() == NULL)
        return false;

    m_collection = (*m_deviceManager)->enumerateRecordingDevices();
    if (m_collection == NULL) {
        delete m_deviceManager;
        m_deviceManager = NULL;
    }

    return m_collection != NULL ? true : false;
}

void AGAudInputManager::close()
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

bool AGAudInputManager::getVolume(int& vol)
{
    if (m_deviceManager == NULL || m_deviceManager->get() == NULL)
        return false;

    int ret = (*m_deviceManager)->getRecordingDeviceVolume(&vol);

    return ret == 0 ? true : false;
}

bool AGAudInputManager::setVolume(uint8_t vol)
{
    if (m_deviceManager == NULL || m_deviceManager->get() == NULL)
        return false;

    int ret = (*m_deviceManager)->setRecordingDeviceVolume((int)vol);

    return ret == 0 ? true : false;
}

uint8_t AGAudInputManager::getDeviceCount()
{
    if (m_collection != NULL)
        return (uint8_t)m_collection->getCount();

    return 0;
}

bool AGAudInputManager::getDevice(uint8_t index, string& deviceName, string& deviceId)
{
    char name[MAX_DEVICE_ID_LENGTH];
    char id[MAX_DEVICE_ID_LENGTH];

    if (index >= getDeviceCount())
        return false;

    if (m_collection == NULL)
        return false;

    int ret = m_collection->getDevice(index, name, id);
    if (ret != 0)
        return false;

    deviceName.assign(name);
    deviceId.assign(id);
    return true;
}

bool AGAudInputManager::getCurDeviceId(string& id)
{
    char deviceId[MAX_DEVICE_ID_LENGTH];

    if (m_deviceManager == NULL || m_deviceManager->get() == NULL)
        return false;

    (*m_deviceManager)->getRecordingDevice(deviceId);
    
    id.assign(deviceId);

    return true;
}

bool AGAudInputManager::setCurDevice(const char* deviceId)
{
    if (m_deviceManager == NULL || m_deviceManager->get() == NULL)
        return false;

    int ret = (*m_deviceManager)->setRecordingDevice(deviceId);

    return ret == 0 ? true : false;
}

