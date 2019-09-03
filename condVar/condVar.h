#ifndef __CONDVAR_H__
#define __CONDVAR_H__

#include "uncopyable.h"
#include "mutex.h"
#include "exceptionTemplate.h"
#include <pthread.h>

namespace advcpp
{


//======================== EXEPTIONS ================================
DEFINE_EXCEPTION(CVSystemLackedNecessaryResources)
DEFINE_EXCEPTION(CVInsufficientMemory)
DEFINE_EXCEPTION(CVDestroyWhileObjectIsReferencedDetected)
DEFINE_EXCEPTION(CVTheMutexWasNotOwnedByCurrentThread)
//===================================================================


class CondVar : private Uncopyable 
{
public:
	CondVar(Mutex& _mutex);
	~CondVar();
	void Wait();
	void Signal();
	void Broadcast();

private:
	void ThrowException(int _status);

	pthread_cond_t m_CV;
	Mutex& m_mutex;
};

} //namespace advcpp

#endif//__CONDVAR_H__