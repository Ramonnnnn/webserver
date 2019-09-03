#include "mutex.h"
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <errno.h>

namespace advcpp
{

Mutex::Mutex()
{	
	int status = pthread_mutex_init(&m_lock, 0);
	if(status != 0)
	{	
		assert(status != EBUSY);
		assert(status != EINVAL);
		ThrowCtorException(status);
	}
}


Mutex::~Mutex()
{
	int status = pthread_mutex_destroy(&m_lock);
	if(status != 0)
	{
		assert(status != EINVAL);
		throw MutexDestroyedWhileLocked("Mutex destroyed while locked");
	}
}


void Mutex::Lock()
{
	int status = pthread_mutex_lock(&m_lock);
	if(status != 0)
    {
    	assert(status != EINVAL);
        ThrowException(status);
    }
}


void Mutex::Unlock()
{
	int status = pthread_mutex_unlock(&m_lock);
	if(status != 0)
    {
    	assert(status != EINVAL);
        ThrowException(status);
    }
}


bool Mutex::Trylock(unsigned int _timeoutMsec)
{
	struct timespec tsCurrent;
	int status = clock_gettime(CLOCK_REALTIME, &tsCurrent);
	assert(status != EFAULT);
	assert(status != EINVAL);

	struct timespec tsInterval = ConvertMillisToTimespec(_timeoutMsec);
	struct timespec tsFuture = AddTimespec(tsCurrent, tsInterval);
	return (pthread_mutex_timedlock(&m_lock, &tsFuture) == 0);
}


void Mutex::ThrowCtorException(int _status)
{
	switch(_status)
	{
		case EAGAIN:
			throw InsufficientResourcesException("Insufficient resources while creatig thread");
		break;
		case ENOMEM:
			throw InsufficientMemoryException("Insufficient Memory");
		break;
		case EPERM:
			throw NoPermissionException("No permissions to set the attributes specified");
		break;
		case EBUSY:
			throw MutexBusyException("Reinitialization detected");
		break;
		case EINVAL:
			throw AttributeInvalid("Invalid attribute parameter");
		break;
		default:
		break;
	}
}



void Mutex::ThrowException(int _status)
{
	switch(_status)
	{
		case EDEADLK:
			throw DeadlockException("The current thread already owns the mutex");
		break;
		case EPERM:
			throw NoPermissionException("Insufficient permissions");
		break;
		case EAGAIN:
			throw NoPermissionException("maximum number of recursive locks for mutex has been exceeded");
		break;
		default:
		break;
	}
}

}