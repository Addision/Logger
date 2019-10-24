//日志接口
#pragma once

#include "Queue.h"
#include "ThreadBase.h"
#include <string>
#include <memory>
#include <cstdio>
#include <cstdarg>

enum eLogLevel
{
    E_LOG_DEBUG = 1,  //打印全部信息
    E_LOG_INFO = 2,   //不打印调试信息
    E_LOG_WARN = 3,   //不打印调试信息，普通信息
    E_LOG_ERR = 4, 
    E_LOG_FATAL = 5,
};

class LogHelper : public ThreadBase{
public:
    LogHelper();
    ~LogHelper();
    bool Init();
    void Loop();
    bool SendLog();
    void Log(const char *file, const char *func, int line, int level, const char *fmt, ...);
    void SetLogLevel(int level);

private:
    Queue<std::string> m_queue;
    int m_level{1};
};

extern std::unique_ptr<LogHelper> g_PtrLog;

#define LOG_DEBUG(...)   g_PtrLog->Log(__FILE__, __PRETTY_FUNCTION__, __LINE__, E_LOG_DEBUG, __VA_ARGS__)
#define LOG_INFO(...)    g_PtrLog->Log(__FILE__, __PRETTY_FUNCTION__, __LINE__, E_LOG_INFO, __VA_ARGS__)
#define LOG_WARN(...)    g_PtrLog->Log(__FILE__, __PRETTY_FUNCTION__, __LINE__, E_LOG_WARN, __VA_ARGS__)
#define LOG_ERR(...)     g_PtrLog->Log(__FILE__, __PRETTY_FUNCTION__, __LINE__, E_LOG_ERR, __VA_ARGS__)
#define LOG_FATAL(...)   g_PtrLog->Log(__FILE__, __PRETTY_FUNCTION__, __LINE__, E_LOG_FATAL, __VA_ARGS__)


