//
// Created by 18081333 on 2019/6/20.
//

#ifndef FACESDK_LOGGER_HPP
#define FACESDK_LOGGER_HPP

#include <android/log.h>
#include <string>
#include <sstream>

#define LOG_TAG "Yancy"

#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
using namespace std;

static stringstream ss;
static bool debugger = true;

class logger {

public:
    static void setDebug(bool isDebug) {
        debugger = isDebug;
    }

    static unsigned long getTime() {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return static_cast<unsigned long>(tv.tv_sec * 1000 + tv.tv_usec / 1000);
    }

    static void printTime(string msg, unsigned long startTime) {
        if (!debugger) { return;}
        msg += ":%ld";
        __android_log_print(ANDROID_LOG_INFO, "FaceSdkEngine_TIME", msg.c_str(), getTime() - startTime);
    }


    template<typename T>
    static void debug(const T &value) {
        if (!debugger) { return;}
        ss << value;
        LOGD("%s", ss.str().c_str());
        ss.str("");
        ss.clear();
    }

    template<typename T, typename... Args>
    static void debug(const T &value, const Args &... arg) {
        if (!debugger) { return;}
        ss << value;
        debug(arg...);
    }

    template<typename T>
    static void error(const T &value) {
        if (!debugger) { return;}
        ss << value;
        LOGE("%s", ss.str().c_str());
        ss.str("");
        ss.clear();
    }

    template<typename T, typename... Args>
    static void error(const T &value, const Args &... arg) {
        if (!debugger) { return;}
        ss << value;
        error(arg...);
    }
};


#endif //FACESDK_LOGGER_HPP
