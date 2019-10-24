
#include "LogHelper.h"
#include <unistd.h>

void TestFunc()
{
    g_PtrLog->SetLogLevel(0);
    LOG_DEBUG("test log %d", 100);
    LOG_FATAL("test log %d", 200);
    g_PtrLog->SetLogLevel(3);
    LOG_DEBUG("test log3 %d", 100);
    g_PtrLog->SetLogLevel(2);
    LOG_DEBUG("test log2 %d", 100);
}

int main(int argc, char const *argv[])
{
    g_PtrLog.reset(new LogHelper());
    g_PtrLog->Start();
    TestFunc();
    g_PtrLog->Join();
    while (1)
    {
        sleep(1);
    }
    
    return 0;
}
