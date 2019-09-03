#include "condVar.h"
#include <iostream>
#include <cassert>
#include <errno.h>

namespace advcpp
{

using namespace std;


CondVar::CondVar(Mutex& _mutex)
	: m_mutex(_mutex)
{
	int status = pthread_cond_init(&m_CV, 0);
	if(status != 0)
	{
		assert(status != EBUSY);
		assert(status != EINVAL);
	}
}


CondVar::~CondVar()
{
	int status = pthread_cond_destroy(&m_CV);
	if(status != 0)
	{
		assert(status != EINVAL);
		ThrowException(status);
	}
}


void CondVar::Wait()
{
	int status = pthread_cond_wait(&m_CV, &(m_mutex.m_lock));
	if(status != 0)
	{
		assert(status != EINVAL);
		ThrowException(status);
	}
}


void CondVar::Signal()
{
	int status = pthread_cond_signal(&m_CV);
	if(status != 0)
	{
		assert(status != EINVAL);
	}
}


void CondVar::Broadcast()
{
	int status = pthread_cond_broadcast(&m_CV);
	if(status != 0)
	{
		assert(status != EINVAL);
	}
}


void CondVar::ThrowException(int _status)
{
	switch(_status)
	{
		case EAGAIN:
			throw CVSystemLackedNecessaryResources();
		break;
		case ENOMEM:
			throw CVInsufficientMemory();
		break;
		case EBUSY:
			throw CVDestroyWhileObjectIsReferencedDetected();
		break;
		case EPERM:
			throw CVTheMutexWasNotOwnedByCurrentThread();
		break;
		default:
		break;
	}
}

}
