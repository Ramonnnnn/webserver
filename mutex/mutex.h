#ifndef __MUTEX_H__
#define __MUTEX_H__

#include "uncopyable.h"
#include "timeOps.h"
#include "mutexExcept.h"
#include <pthread.h>

namespace advcpp
{

class Mutex : private Uncopyable 
{
	friend class CondVar;
public:
	Mutex();
	~Mutex();
	void Lock();
	void Unlock();
	bool Trylock(unsigned int _timeoutMsec);

private:
	void ThrowCtorException(int _status);
	void ThrowException(int _status);
	
	pthread_mutex_t m_lock;
};

} //namespace advcpp

#endif//__MUTEX_H__