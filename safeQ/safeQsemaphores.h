#ifndef __SAFEQ_H__
#define __SAFEQ_H__

#include <queue>
#include <pthread.h>
#include <semaphore.h>

using namespace std;

template <class T>
class SafeQ
{
public:
	SafeQ();	
	~SafeQ();
	
	bool Push(const T &_element);
	T & Pop();
	T & Front();
	bool IsEmpty();

private:
	queue<T> m_messageQ;
	sem_t m_semaphore;
    pthread_mutex_t m_mutex;
};


template <class T>
SafeQ<T>::SafeQ()
{
	if(pthread_mutex_init(&m_mutex, 0) != 0)
	{
		
		throw("mutex init failed");
	}

	if(sem_init(&m_semaphore, 0, 0) != 0)
	{
		if(pthread_mutex_destroy(&m_mutex) != 0)
		{
			throw("mutex destroy failed");
		}

		
		throw("semaphore init failed");
	}
}


template <class T>
SafeQ<T>::~SafeQ()
{
	if(pthread_mutex_destroy(&m_mutex) != 0)
	{
		throw("mutex destroy failed");
		
	}

	if(sem_destroy(&m_semaphore) != 0)
	{
		throw("semaphore destruction failed");
		
	}
}



template <class T>
bool SafeQ<T>::Push(const T &_element)
{
	if(pthread_mutex_lock(&m_mutex) != 0)
	{
		throw("mutex lock failed");
	}

	m_messageQ.push((T &)_element);

	if(pthread_mutex_unlock(&m_mutex) != 0)
	{
		throw("mutex unlock failed");
	}

	if(sem_post(&m_semaphore) != 0)
	{
		throw("sem post failed");
	}

	return true;
}



template <class T>
T & SafeQ<T>::Pop()
{
	if(sem_wait(&m_semaphore) != 0)
	{
		throw("sem wait failed");
	}

	
	if(pthread_mutex_lock(&m_mutex) != 0)
	{
		throw("mutex lock failed");
	}

	T &tempElm = m_messageQ.front();
	m_messageQ.pop();

	if(pthread_mutex_unlock(&m_mutex) != 0)
	{
		throw("mutex unlock failed");
	}

	return tempElm;
}


template <class T>
T & SafeQ<T>::Front()
{	
	if(sem_wait(&m_semaphore) != 0)
	{
		throw("sem wait failed");
	}

	if(pthread_mutex_lock(&m_mutex) != 0)
	{
		throw("mutex lock failed");
	}

	T &tempElm = m_messageQ.front();

	if(pthread_mutex_unlock(&m_mutex) != 0)
	{
		throw("mutex unlock failed");
	}

	return tempElm;
}


template <class T>
bool SafeQ<T>::IsEmpty()
{
	bool tempRet;

	if(pthread_mutex_lock(&m_mutex) != 0)
	{
		throw("mutex lock failed");
	}

	tempRet = m_messageQ.empty();

	if(pthread_mutex_unlock(&m_mutex) != 0)
	{
		throw("mutex unlock failed");
	}

	return tempRet;
}


#endif//__SAFEQ_H__