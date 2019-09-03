#ifndef __GUARDADV_H__
#define __GUARDADV_H__

#include "mutex.h"

namespace advcpp
{

class Guard
{
public:
    Guard(Mutex& _lock)
        : m_lock(_lock) 
    {
        m_lock.Lock();  
    }

    ~Guard() 
    {
        m_lock.Unlock();
    }

 	
 private:
    Mutex& m_lock;
};

}//advcpp

#endif//__GUARDADV_H__