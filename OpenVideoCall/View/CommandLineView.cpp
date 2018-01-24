#include <stdio.h>
#include <iostream>
#include <string.h>
#include<sstream>

#include "AgoraDefs.h"
#include"CommandLineView.h"
#include"Controller/EngineController.h"

#define MAXLINE 1024

using std::cout;
using std::endl;


CommandLineView::CommandLineView(){
}

CommandLineView::~CommandLineView() {
}

void CommandLineView::configure(const AppConfig& config) {
    if(m_controller)
        m_controller->sendMsg(this,MSG_CONFIGURE,(void*)&config);
}

void CommandLineView::run(bool openVideoCall) {

    if(openVideoCall) {
        open();
    }

    char buf[MAXLINE];
    memset(buf, 0, MAXLINE);

    cout<< "input command:" << endl;
    while(fgets(buf, MAXLINE, stdin) != NULL) {
        buf[strlen(buf)-1] = 0;

        stringstream ss(&buf[0]);
        string cmd;
        ss >> cmd;
        if(cmd == "exit") {
            exit();
            break;
        }
        else {
            if(!onCommand(cmd , ss)) {
                cout<< "failed to call command:" << cmd << endl;
            }
        }
        memset(buf, 0, MAXLINE);
    }

    cout<< "exit command line" << endl;
}

bool CommandLineView::onCommand(const string& cmd, stringstream& params) {

    if(cmd.compare("open") == 0 ) {
        return open();
    } 
    else if(cmd.compare("close") == 0) {
        return close();
    }
    else if(cmd.compare("enable_video") == 0) {
        string enable;
        params >> enable;

        int flag = 0;
        sscanf(enable.c_str(),"%d",&flag);
        return enableVideo((bool)flag);
    }
    else if(cmd.compare("enable_audio") == 0) {
        string enable;
        params >> enable;

        int flag = 0;
        sscanf(enable.c_str(),"%d",&flag);
        return enableAudio((bool)flag);
    }  
    else if(cmd.compare("enable_local_video") == 0) {
        string enable;
        params >> enable;

        int flag = 0;
        sscanf(enable.c_str(),"%d",&flag);
        return enableLocalVideo((bool)flag);
    }
    else if(cmd.compare("enable_local_audio") == 0) {
        string enable;
        params >> enable;

        int flag = 0;
        sscanf(enable.c_str(),"%d",&flag);
        return enableLocalAudio((bool)flag);
    }  

    else if(cmd.compare("print_device_info") == 0) {
        return printDeviceInfo();
    }  
    else if(cmd.compare("set_cur_camera") == 0) {
        string cameraId;
        params >> cameraId;

        return setCurCamera(cameraId);
    }
    else {
        cout<< "WARNING:invalid command: " << cmd <<endl;
        return false;
    }
}

bool CommandLineView::printDeviceInfo() {
    if(!m_controller)
        return false;

    return m_controller->sendMsg(this, MSG_PRINT_DEVICE_INFO,NULL);
}

bool CommandLineView::open() {
    if(!m_controller)
        return false;

    return m_controller->sendMsg(this, MSG_OPEN, NULL);
}

bool CommandLineView::close() {
    if(!m_controller)
        return false;

    return m_controller->sendMsg(this, MSG_CLOSE, NULL);
}

bool CommandLineView::enableVideo(bool enable) {
    if(!m_controller)
        return false;

    return m_controller->sendMsg(this, MSG_ENABLE_VIDEO , (void*)&enable);
}

bool CommandLineView::enableAudio(bool enable) {
    if(!m_controller)
        return false;

    return m_controller->sendMsg(this, MSG_ENABLE_AUDIO , (void*)&enable);
}

bool CommandLineView::enableLocalVideo(bool enable) {
    if(!m_controller)
        return false;

    return m_controller->sendMsg(this, MSG_ENABLE_LOCAL_VIDEO , (void*)&enable);
}

bool CommandLineView::enableLocalAudio(bool enable) {
    if(!m_controller)
        return false;

    return m_controller->sendMsg(this, MSG_ENABLE_LOCAL_AUDIO , (void*)&enable);
}

bool CommandLineView::setCurCamera(const string& cameraId) {
    if(!m_controller)
        return false;

    return m_controller->sendMsg(this, MSG_SET_CUR_CAMERA , (void*)&cameraId);
}

bool CommandLineView::exit() {
    if(!m_controller)
        return false;

    return m_controller->sendMsg(this, MSG_EXIT , NULL);
}
