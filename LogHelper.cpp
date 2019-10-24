
#include "LogHelper.h"
#include <ctime>
#include <cstring>
#include <iostream>

std::unique_ptr<LogHelper> g_PtrLog = nullptr;

LogHelper::LogHelper()
{
    Init();
}

LogHelper::~LogHelper()
{
}


bool LogHelper::Init()
{
}

void LogHelper::Loop()
{
    while(IsActive())
    {
        //todo 通过kafka发送日志
        SendLog();
    }
}

bool LogHelper::SendLog()
{
    std::string info;
    m_queue.PopQ(info);
    std::cout << info << std::endl;
    
}

void LogHelper::SetLogLevel(int level)
{
    m_level = level;
}

void LogHelper::Log(const char* file, const char* func, int line, int level, const char* fmt, ...)
{
    switch (m_level)
    {
    case E_LOG_FATAL:
    {
        if(level < E_LOG_FATAL)
        {
            return;
        }        
    }
    case E_LOG_ERR:
    {
        if(level < E_LOG_ERR)
        {
            return;
        }
    }
    case E_LOG_WARN:
    {
        if(level < E_LOG_WARN)
        {
            return;
        }        
    }    
    case E_LOG_INFO:
    {
        if(level < E_LOG_INFO)
        {
            return;
        }
    }
    case E_LOG_DEBUG:
    {
        if(level < E_LOG_DEBUG)
        {
            return;
        }
    }    
    default:
        break;
    }
    //记录日志时间
    char time_stamp[32];
    memset(time_stamp, '\0', sizeof(time_stamp));
    time_t now = time(0);
    ::strftime(time_stamp, sizeof(time_stamp), "%Y-%m-%d %H:%M:%S", localtime(&now));

    char content[512];
    memset(content, '\0', sizeof(content));
    va_list ap;
    va_start(ap, fmt);
    vsnprintf(content, sizeof(content) - 1, fmt, ap);
    va_end(ap);

    std::string logs;
    logs.append(std::to_string(level) + "|");
    logs.append(time_stamp);
    logs.append("|");
    logs.append(file);
    logs.append(":");
    logs.append(func);
    logs.append(":");
    logs.append(std::to_string(line));
    logs.append(" ");    
    logs.append(content);
    logs.append("\n");
    m_queue.PutQ(logs);
} 