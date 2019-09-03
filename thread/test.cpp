#include "thread.h"
#include <iostream>
#include <string>
#include <tr1/memory>
#include <unistd.h>
#include <queue>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace advcpp;
using namespace std;

const int arrayLength = 10;
const int sleepTime = 1;
int rounds_g;

void TestConsumerProducer();
void TestConsumerProducer_joinFromMultipleThreads();
void TestConsumerProducer_joinFromAnotherThread();
void TestConsumerProducer_2Consumers1Producer();
void TestConsumerProducer_4Consumers1Producer();
void TestCancelThread();


struct PrintHello : public IRunnable
{
	PrintHello(string& _str) : m_str(_str) { }
	void Run() {sleep(10); cout << m_str << '\n';}

private:
	string m_str;
};

struct Producer : public IRunnable
{
	Producer(queue<int>& _q, Semaphore& _empty, Semaphore& _full, Mutex& _lock, int _rounds) 
		: m_q(_q), m_empty(_empty), m_full(_full), m_lock(_lock), m_rounds(_rounds) { }
	void Run()
	{
		for(int i = 0; i < m_rounds; ++i)
		{
			m_empty.Wait();
			m_lock.Lock();
			m_q.push(i);
			m_lock.Unlock();
			m_full.Post();
			sleep(sleepTime);
		}
	}

	queue<int>& m_q;
	Semaphore& m_empty;
	Semaphore& m_full;
	Mutex& m_lock;
	int m_rounds;
};


struct Consumer : public IRunnable
{
	Consumer(queue<int>& _q, Semaphore& _empty, Semaphore& _full, Mutex& _lock, int _rounds, int _numOfConsumers = 1) 
		: m_q(_q), m_empty(_empty), m_full(_full), m_lock(_lock), m_rounds(_rounds / _numOfConsumers), 
		  m_testArr(_rounds), m_numOfConsumers(_numOfConsumers) { }
	void Run()
	{
		for(int i = 0; i < m_rounds; ++i)
		{
			m_full.Wait();
			m_lock.Lock();
			cout << m_q.front() << '\n';
			//assert(m_q.front() == i);
			++m_testArr[m_q.front()]; 
			m_q.pop();
			m_lock.Unlock();
			m_empty.Post();
		}
	}

	void PrintResults()
	{
		for (vector<int>::const_iterator it = m_testArr.begin(); it != m_testArr.end(); ++it)
    	std::cout << *it << ' ';
    	cout << '\n';
	}

	bool RunHistogramTest()
	{
		for(int i = 0; i < m_rounds * m_numOfConsumers; ++i)
		{
			if(m_testArr[i] != 1)
			{
				PrintResults();
				return false;
			}
		}
		PrintResults();
		return true;
	}

	queue<int>& m_q;
	Semaphore& m_empty;
	Semaphore& m_full;
	Mutex& m_lock;
	int m_rounds;
	vector<int> m_testArr;
	int m_numOfConsumers;
};

void TestConsumerProducer()
{
	int _rounds = 4;
	queue<int> q;
	Mutex lock;
	Semaphore empty(_rounds);
	Semaphore full(0);
	tr1::shared_ptr<IRunnable> spProd(new Producer(q, empty, full, lock, _rounds));
	tr1::shared_ptr<IRunnable> spCons(new Consumer(q, empty, full, lock, _rounds));

	Thread prod_t(spProd);
	Thread cons_t(spCons);

	prod_t.Join();
	cons_t.Join();
}

struct JoinMultipleThreads : public IRunnable
{
	JoinMultipleThreads(tr1::shared_ptr<Thread> _tp) : m_thread(_tp) { }
	void Run() {sleep(rounds_g / 2); m_thread->Join();}

private:
	tr1::shared_ptr<Thread> m_thread;
};

void TestConsumerProducer_joinFromMultipleThreads()
{
	int _rounds = 4;
	rounds_g = _rounds;
	queue<int> q;
	Mutex lock;
	Semaphore empty(_rounds);
	Semaphore full(0);
	tr1::shared_ptr<IRunnable> spProd(new Producer(q, empty, full, lock, _rounds));
	tr1::shared_ptr<IRunnable> spCons(new Consumer(q, empty, full, lock, _rounds));

	tr1::shared_ptr<Thread> spProdThread(new Thread(spProd));
	tr1::shared_ptr<Thread> spProdThreadPeer(spProdThread);
	//Thread prod_t(spProd);
	Thread cons_t(spCons);

	tr1::shared_ptr<IRunnable> spJoinMult(new JoinMultipleThreads(spProdThreadPeer));
	Thread JoinMult_t(spJoinMult);

	spProdThread->Join();
	cons_t.Join();
	assert((static_cast<Consumer*>(spCons.get()))->RunHistogramTest() == true);
}

struct JoinFromAnotherThread : public IRunnable
{
	JoinFromAnotherThread(tr1::shared_ptr<Thread> _tp) : m_thread(_tp) { }
	void Run() {sleep(rounds_g / 2); m_thread->Join();}

private:
	tr1::shared_ptr<Thread> m_thread;
};

void TestConsumerProducer_joinFromAnotherThread()
{
	int _rounds = 4;
	rounds_g = _rounds;
	queue<int> q;
	Mutex lock;
	Semaphore empty(_rounds);
	Semaphore full(0);
	tr1::shared_ptr<IRunnable> spProd(new Producer(q, empty, full, lock, _rounds));
	tr1::shared_ptr<IRunnable> spCons(new Consumer(q, empty, full, lock, _rounds));

	tr1::shared_ptr<Thread> threadProd(new Thread(spProd));
	tr1::shared_ptr<Thread> threadProdPeer(threadProd);
	//Thread prod_t(spProd);
	Thread cons_t(spCons);

	//Join the producer from this thread:
	tr1::shared_ptr<IRunnable> spOtherJoin(new JoinFromAnotherThread(threadProdPeer));
	Thread JoinMult_t(spOtherJoin);

	//TEST - THIS JOIN IS ELIMINATED, the join occurs from another spwaned thread:
	//threadProd->Join();
	cons_t.Join();
	JoinMult_t.Join();
	assert((static_cast<Consumer*>(spCons.get()))->RunHistogramTest() == true);
}


void TestConsumerProducer_2Consumers1Producer()
{
	int _rounds = 4;
	int numOfConsumers = 2;
	rounds_g = _rounds;
	queue<int> q;
	Mutex lock;
	Semaphore empty(_rounds);
	Semaphore full(0);
	tr1::shared_ptr<IRunnable> spProd(new Producer(q, empty, full, lock, _rounds));
	tr1::shared_ptr<IRunnable> spCons(new Consumer(q, empty, full, lock, _rounds, numOfConsumers));

	Thread prod_t(spProd);
	Thread cons_t1(spCons);
	Thread cons_t2(spCons);

	prod_t.Join();
	cons_t1.Join();
	cons_t2.Join();
	assert(((static_cast<Consumer*>(spCons.get()))->RunHistogramTest()) == true);
}


void TestConsumerProducer_4Consumers1Producer()
{
	int _rounds = 8;
	int numOfConsumers = 4;
	rounds_g = _rounds;
	queue<int> q;
	Mutex lock;
	Semaphore empty(_rounds);
	Semaphore full(0);
	tr1::shared_ptr<IRunnable> spProd(new Producer(q, empty, full, lock, _rounds));
	tr1::shared_ptr<IRunnable> spCons(new Consumer(q, empty, full, lock, _rounds, numOfConsumers));

	Thread prod_t(spProd);
	Thread cons_t1(spCons);
	Thread cons_t2(spCons);
	Thread cons_t3(spCons);
	Thread cons_t4(spCons);

	prod_t.Join();
	cons_t1.Join();
	cons_t2.Join();
	cons_t3.Join();
	cons_t4.Join();
	assert(((static_cast<Consumer*>(spCons.get()))->RunHistogramTest()) == true);
}


struct CancelThread : public IRunnable
{
	void Run() {sleep(rounds_g);}
};


void TestCancelThread()
{
	int timeLimit = 6;
	rounds_g = timeLimit;
	
	tr1::shared_ptr<IRunnable> spCancel(new CancelThread());

	Thread cancel_t(spCancel);
	struct timespec tsCurrent, tsNext;
	clock_gettime(CLOCK_REALTIME, &tsCurrent);
	sleep(2);
	cancel_t.Cancel();
	clock_gettime(CLOCK_REALTIME, &tsNext);
	assert(tsNext.tv_sec - tsCurrent.tv_sec < timeLimit);
}


int main()
{
	TestConsumerProducer();
	TestConsumerProducer_joinFromMultipleThreads();
	TestConsumerProducer_joinFromAnotherThread();
	TestConsumerProducer_2Consumers1Producer();
	TestConsumerProducer_4Consumers1Producer();
	TestCancelThread();
}





























// int main()
// {
// 	string sayhello("hello");
	
// 	tr1::shared_ptr<IRunnable> sp(new PrintHello(sayhello));
	
// 	Thread t1(sp);
	
// 	t1.Join();

// 	Mutex mutex1;
// }









































// Guard guard(m_cancelMutex);
// 	if(!m_isCancelled)
// 	{
// 		int status = pthread_cancel(m_thread);
// 		if(status != 0)
// 		{
// 			ThrowCancelException(status);
// 		}
// 		m_isCancelled = true;
// 	}
//tr1::shared_ptr<IRunnable> sp = *(tr1::shared_ptr<IRunnable>*)_arg;
