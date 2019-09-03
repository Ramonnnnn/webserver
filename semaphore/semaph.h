#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#include "uncopyable.h"
#include "semaphExcept.h"
#include <semaphore.h>

namespace advcpp
{

class Semaphore : private Uncopyable 
{
public:
	Semaphore(int _InitValue);
	~Semaphore();
	void Wait();
	bool TryWait(); //should be with time limit
	void Post();

private:
	sem_t m_semaphore;
};

} //namespace advcpp

#endif//__SEMAPHORE_H__