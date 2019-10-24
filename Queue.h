//多线程安全队列
#pragma once

#include <deque>
#include "Mutex.h"

template<typename T>
class Queue{
public:
    Queue()
    {
    }
    virtual ~Queue()
    {
        m_cond_empty.notify_all();
        if(!m_deque.empty())
        {
            m_deque.clear();
        }
    }

    void PutQ(const T& info)
    {
        AutoLock lock(m_mutex);
        m_deque.push_front(info);
        m_cond_empty.notify_one();
    }

    void PopQ(T& info)
    {
        AutoLock lock(m_mutex);
        if(m_deque.empty())
        {
            m_cond_empty.wait(lock); 
        }
        info = m_deque.back();
        m_deque.pop_back();
    }

private:
    std::deque<T> m_deque;
    Mutex m_mutex;
    Cond m_cond_empty;
};



