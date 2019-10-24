#pragma once

#include <mutex>
#include <condition_variable>

typedef std::recursive_mutex RecursiveMutex;
typedef std::lock_guard<std::recursive_mutex> RecursiveLock;
typedef std::mutex Mutex;
typedef std::unique_lock<std::mutex> AutoLock;

typedef std::condition_variable Cond; //条件变量