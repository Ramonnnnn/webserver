#include "thread.h"
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <errno.h>
#include <string>

namespace advcpp
{

using namespace std;

void* ThreadRun(void* _arg);


void* ThreadRun(void* _arg)
{
	try
	{
		tr1::shared_ptr<IRunnable> sp((static_cast<Thread*>(_arg))->m_sp); //make a local copy of the shared pointer.
		(static_cast<Thread*>(_arg))->m_ensureCopyOfRunnable.Post(); //ensure a copy of the shared ptr to this function for independency.
		sp->Run();	
	}
	catch(const std::exception _ex)
	{
		std::cerr << _ex.what();
	}

	return NULL;
}

Thread::Thread(tr1::shared_ptr<IRunnable> _sp)
	: m_sp(_sp), m_isJoined(false), m_preventMultipleJoinSema(1), m_ensureCopyOfRunnable(0)
{
	int status = pthread_create(&m_thread, NULL, ThreadRun, (void *)this);
	if(status != 0)
	{
		ThrowCtorException(status);
	}
}


Thread::~Thread()
{
	//copy of shared ptr ensured:
	m_ensureCopyOfRunnable.Wait(); // possibly not necessary since incorporating the Join() next.
	//yariv note: instead of Wait in the dtor do: Join() and then possibly - not mandatory - cancel()
	Join();
	//Cancel(); // yariv said to also do a Cancel. For later debugging.
}


void Thread::Join()
{
	//For the case of sharing a thread object with multiple other threads -
	//the semaphore prevents undefined behavior when applying multiple join calls.
	m_preventMultipleJoinSema.Wait();
	if(!m_isJoined)
	{
		int status = pthread_join(m_thread, 0);
		if(status != 0)
		{
			m_preventMultipleJoinSema.Post();
			ThrowJoinException(status);
		}
		m_isJoined = true;
	}
	m_preventMultipleJoinSema.Post();
}


void Thread::TimedJoin(unsigned int _timeoutMsec)
{
	m_preventMultipleJoinSema.Wait();
	if(!m_isJoined)
	{
		struct timespec tsCurrent;
		int status = clock_gettime(CLOCK_REALTIME, &tsCurrent);
		assert(status != EFAULT);
		assert(status != EINVAL);

		struct timespec tsInterval = ConvertMillisToTimespec(_timeoutMsec);
		struct timespec tsFuture =  AddTimespec(tsCurrent, tsInterval);
		status = pthread_timedjoin_np(m_thread, 0, &tsFuture);
		if(status != 0)
		{
			m_preventMultipleJoinSema.Post();
			ThrowJoinException(status);
		}

		m_isJoined = true;
	}
	m_preventMultipleJoinSema.Post();
}


void Thread::Cancel()
{
	int status = pthread_cancel(m_thread);
	if(status != 0)
	{
		ThrowCancelException(status);
	}
}



void Thread::ThrowCtorException(int _status)
{
	switch(_status)
	{
		case EAGAIN:
			throw InsufficientResourcesException("Insufficient resources while creatig thread");
		break;
		case EINVAL:
			throw InvalidAttributeSettingException("Invalid attributes setting");
		break;
		case EPERM:
			throw NoPermissionException("No permissions to set the attributes specified");
		break;
		default:
		break;
	}
}


void Thread::ThrowJoinException(int _status)
{
	switch(_status)
	{
		case EDEADLK:
			throw DeadlockException("A deadlock was detected");
		break;
		case EINVAL:
			throw NotJoinableThreadException("Thread is not joinalbe thread");
		break;
		case ESRCH:
			throw ThreadIdNotFoundException("No thread with the ID thread could be found");
		break;
		case ETIMEDOUT:
			throw OperationTimedOut("The call timed out before thread terminated");
		break;
		default:
		break;
	}
}


void Thread::ThrowCancelException(int _status)
{
	switch(_status)
	{
		case ESRCH:
			throw ThreadIdNotFoundException("No thread with the ID thread could be found");
		break;
		default:
		break;
	}
}

}

















	//
	// Guard guard(m_mutex);
	// static int i = 7;
	// cout << i << endl;
	// ++i;