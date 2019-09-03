#include "semaph.h"
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <errno.h>

namespace advcpp
{

Semaphore::Semaphore(int _InitValue)
{	
	int status = sem_init(&m_semaphore, 0, _InitValue);
	if(status != 0)
	{	
		throw MaxInitValueExceeded("maximum initial value is to large");
	}
}


Semaphore::~Semaphore()
{
	sem_destroy(&m_semaphore);
	assert(errno != EINVAL);
}


void Semaphore::Wait()
{
	int status = sem_wait(&m_semaphore);
	if(status != 0)
    {
    	assert(errno != EINVAL);
        throw(CallInterruptedBySignalHandler("signal handler interrupted"));
    }
}


void Semaphore::Post()
{
	int status = sem_post(&m_semaphore);
	if(status != 0)
    {
    	assert(errno != EINVAL);
        throw(OverflowInSemaphoreValue("overflow in semaphore value"));
    }
}


bool Semaphore::TryWait()
{
	return !sem_trywait(&m_semaphore);
}

}