#ifndef __THREADPOOL_H__
#define __THREADPOOL_H__

#include "uncopyable.h"
#include "safeQ.h"
#include "thread.h"
#include <cstddef>
#include <list>

namespace advcpp
{

class ThreadPool : public Uncopyable
{
public:
	ThreadPool(size_t _numOfThreads);
	//~ThreadPool() = default;
	void Start();
	void Stop();
	void InsertToTasksQ(tr1::shared_ptr<IRunnable>);
	void ShutDown();
	void Increase();
	void Decrease();

private:
	size_t m_numOfThreads;
	SafeQ<tr1::shared_ptr<IRunnable> > m_safeQ;
	list<tr1::shared_ptr<Thread> > m_threads;
};

} //namespace advcpp

#endif//__THREADPOOL_H__