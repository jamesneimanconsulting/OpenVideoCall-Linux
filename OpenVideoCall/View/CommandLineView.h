#pragma once
#include"Controller/MsgHandler.h"

using std::string;
using std::stringstream;

struct AppConfig;

class CommandLineView : public MsgHandler{
    public:
        CommandLineView();
        ~CommandLineView();

        void run();
        void configure(const AppConfig& config);

    private:
        bool onCommand(const string& cmd, stringstream& params);

        bool open(); 

        bool close(); 

        bool enableAudio(int enable); 

        bool enableVideo(int enable);

        bool enableLocalAudio(int enable); 

        bool enableLocalVideo(int enable);

        bool printDeviceInfo(); 

        bool setCurCamera(const string& cameraId); 

        bool exit(); 
};
