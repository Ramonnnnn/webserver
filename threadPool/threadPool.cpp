#include "threadPool.h"
#include <cassert>
#include <cerrno>

namespace advcpp
{

using namespace std;


struct PopRunnableFromQ : public IRunnable
{
	PopRunnableFromQ(SafeQ<tr1::shared_ptr<IRunnable> >& _q)
		: m_q(_q) { }
	void Run()
	{
		try
		{
			while(1)
			{
				tr1::shared_ptr<IRunnable> spRunnable = m_q.Pop();
				spRunnable->Run();
			}
		}
		catch(string& _ex) //catches - stop running flag was raised exception //TODO chage exceptions type!!!!!!!!!!!!!!!!!!
		{
		}
	}

	SafeQ<tr1::shared_ptr<IRunnable> >& m_q;
};


struct FindSelf
{
	FindSelf(pthread_t _myId)
		: m_myId(_myId) { }
	bool operator()(tr1::shared_ptr<Thread> _threadSp) {return m_myId == _threadSp->GetId();}

	pthread_t m_myId;
};


struct SelfDestoryThread : public IRunnable
{
	SelfDestoryThread(list<tr1::shared_ptr<Thread> >& _threads)
		: m_threads(_threads) { }
	void Run()
	{
		m_threads.remove_if(FindSelf(pthread_self())); //evoke dtor for this context thread
		pthread_exit(0);
	}

	list<tr1::shared_ptr<Thread> >& m_threads;
};


ThreadPool::ThreadPool(size_t _numOfThreads)
	: m_numOfThreads(_numOfThreads)
{
}


void ThreadPool::ShutDown()
{
	m_safeQ.StopWaitingOnQ();
}


// struct TimeOutCalc
// {
// 	TimeOutCalc()
// 	void operator()(tr1::shared_ptr<Thread> _threadSp)
// 	{

// 	}
// };


void ThreadPool::ShutDown(unsigned int _timeOutMilliSecs)
{
	struct timespec tsCurrent;
	int status = clock_gettime(CLOCK_REALTIME, &tsCurrent);
	assert(status != EFAULT);
	assert(status != EINVAL);
	
	m_safeQ.StopWaitingOnQ();

	for(list<tr1::shared_ptr<Thread> >::iterator it = m_threads.begin(); it != m_threads.end(); ++it)
	{
		
	}
}


void ThreadPool::Start()
{
	for(size_t i = 0; i < m_numOfThreads; ++i)
	{
		tr1::shared_ptr<IRunnable> spPopRunnableFromQ(new PopRunnableFromQ(m_safeQ));
		tr1::shared_ptr<Thread> spPopRunnableThread(new Thread(spPopRunnableFromQ));
		m_threads.push_back(spPopRunnableThread);
	}
}


void ThreadPool::Increase()
{
	tr1::shared_ptr<IRunnable> spPopRunnableFromQ(new PopRunnableFromQ(m_safeQ));
	tr1::shared_ptr<Thread> spPopRunnableThread(new Thread(spPopRunnableFromQ));
	m_threads.push_back(spPopRunnableThread);
}


void ThreadPool::Decrease()
{
	if(m_threads.size() == 0)
	{
		return;
	}

	tr1::shared_ptr<IRunnable> spSelfDestroy(new SelfDestoryThread(m_threads));
	InsertToTasksQ(spSelfDestroy);
}


void ThreadPool::Stop()
{
	m_safeQ.StopWaitingOnQ();
}


void ThreadPool::InsertToTasksQ(tr1::shared_ptr<IRunnable> _irunnable)
{
	m_safeQ.Push(_irunnable);
}

}


















//cout << "the size of thread list is: " << m_threads.size() << '\n';
