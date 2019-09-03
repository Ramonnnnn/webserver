#ifndef __THREAD_H__
#define __THREAD_H__

#include "uncopyable.h"
#include "irunnable.h"
#include "threadExcept.h"
#include "guardAdv.h"
#include "semaph.h"
#include <pthread.h>
#include <tr1/memory>

namespace advcpp
{

class Thread : private Uncopyable 
{
	friend void* ThreadRun(void* _arg);
public:
	Thread(std::tr1::shared_ptr<IRunnable> _sp);
	~Thread();
	void Join();
	void TimedJoin(unsigned int _timeoutMsec);
	void Cancel();
	pthread_t GetId() const {return m_thread;}

private:
	void ThrowCtorException(int _status);
	void ThrowJoinException(int _status);
	void ThrowCancelException(int _status);

	std::tr1::shared_ptr<IRunnable> m_sp;
	pthread_t m_thread;
	//m_isJoined - used for preventing the case of multiple join attempts
	//from different threads, which share a pointer to this:
	bool m_isJoined;
	Semaphore m_preventMultipleJoinSema;
	Semaphore m_ensureCopyOfRunnable;
};

} //namespace advcpp

#endif//__THREAD_H__