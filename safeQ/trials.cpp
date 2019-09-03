#ifndef __SAFEQCV_H__
#define __SAFEQCV_H__

#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include <iostream>

using namespace std;

template <class T>
class SafeQ
{
public:
	//note: underlying T class should have a default CTOR
	SafeQ();
	~SafeQ();
	
	bool Push(const T _element);
	T Pop();
	//T & Front();
	bool IsEmpty();
	void StopWaitingOnQ();

private:
	queue<T> m_messageQ;
	bool m_exit; // a way to make all waiting threads (wait upon pop) exit safely
	//sem_t m_semaphore;
    pthread_mutex_t m_mutex;
    //pthread_cond_t safeInsertCV;
	pthread_cond_t safeRemoveCV;
};


template <class T>
void SafeQ<T>::StopWaitingOnQ()
{
	m_exit = true;

	if(pthread_cond_broadcast(&safeRemoveCV) != 0)
	{
		throw("pthread_cond_broadcast failed");
	}
	
}



template <class T>
SafeQ<T>::SafeQ()
	: m_exit(false)
{
	if(pthread_mutex_init(&m_mutex, 0) != 0)
	{
		
		throw("mutex init failed");
	}

	// if(pthread_cond_init(&safeInsertCV, 0) != 0)
	// {
	// 	pthread_mutex_destroy(&m_mutex);
	// 	sem_destroy(&m_semaphore);
	// 	throw("CV init failed");
	// }

	if(pthread_cond_init(&safeRemoveCV, 0) != 0)
	{
		pthread_mutex_destroy(&m_mutex);
		//sem_destroy(&m_semaphore);
		//pthread_cond_destroy(&safeInsertCV);
		throw("CV init failed");
	}
}


template <class T>
SafeQ<T>::~SafeQ()
{	
	if(pthread_mutex_destroy(&m_mutex) != 0)
	{
		throw("mutex destroy failed");
		
	}
	// if(sem_destroy(&m_semaphore) != 0)
	// {
	// 	throw("semaphore destruction failed");
		
	// }

	// if(pthread_cond_destroy(&safeInsertCV) != 0)
	// {
	// 	throw("CV destroy failed");
	// }
	//cout << "cond destroy error: " << pthread_cond_destroy(&safeRemoveCV) << endl;
	if(pthread_cond_destroy(&safeRemoveCV) != 0)
	{
		throw("CV destroy failed");
	}
}



template <class T>
bool SafeQ<T>::Push(const T _element)
{
	if(pthread_mutex_lock(&m_mutex) != 0)
	{
		throw("mutex lock failed");
	}

	m_messageQ.push(_element);

	if(pthread_cond_signal(&safeRemoveCV) != 0)
	{
		throw("mutex unlock failed");
	}

	if(pthread_mutex_unlock(&m_mutex) != 0)
	{
		throw("mutex unlock failed");
	}

	return true;
}



template <class T>
T SafeQ<T>::Pop()
{	
	if(pthread_mutex_lock(&m_mutex) != 0)
	{
		throw("mutex lock failed");
	}

	while((m_messageQ.empty()) && (!m_exit))
	{
		if(pthread_cond_wait(&safeRemoveCV, &(m_mutex)) != 0)
		{
			throw("pthread_cond_wait failed");
		}
		
		//here is the way to make all waiting threads exit safely:
		if(m_exit == true)
		{
			if(pthread_mutex_unlock(&m_mutex) != 0)
			{
				throw("mutex unlock failed");
			}

			throw "stop message";
		}
	}

	T tempElm = m_messageQ.front();
	m_messageQ.pop();

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


#endif//__SAFEQCV_H__






















// template <class T>
// T & SafeQ<T>::Front()
// {	
// 	if(sem_wait(&m_semaphore) != 0)
// 	{
// 		throw("sem wait failed");
// 	}

// 	if(pthread_mutex_lock(&m_mutex) != 0)
// 	{
// 		throw("mutex lock failed");
// 	}

// 	T &tempElm = m_messageQ.front();

// 	if(pthread_mutex_unlock(&m_mutex) != 0)
// 	{
// 		throw("mutex unlock failed");
// 	}

// 	return tempElm;
// }



























/////////////////////////////////////////////////////////////
#ifndef __SAFEQCV_H__
#define __SAFEQCV_H__

#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include <iostream>

using namespace std;

template <class T>
class SafeQ
{
public:
	//note: underlying T class should have a default CTOR
	SafeQ();
	~SafeQ();
	
	bool Push(const T _element);
	T Pop();
	//T & Front();
	bool IsEmpty();
	void StopWaitingOnQ();

private:
	queue<T> m_messageQ;
	bool m_exit; // a way to make all waiting threads (wait upon pop) exit safely
    pthread_mutex_t m_mutex;
	pthread_cond_t safeRemoveCV;
};


template <class T>
void SafeQ<T>::StopWaitingOnQ()
{
	m_exit = true;

	if(pthread_cond_broadcast(&safeRemoveCV) != 0)
	{
		throw("pthread_cond_broadcast failed");
	}
	
}



template <class T>
SafeQ<T>::SafeQ()
	: m_exit(false)
{
	if(pthread_mutex_init(&m_mutex, 0) != 0)
	{
		
		throw("mutex init failed");
	}

	if(pthread_cond_init(&safeRemoveCV, 0) != 0)
	{
		pthread_mutex_destroy(&m_mutex);
		throw("CV init failed");
	}
}


template <class T>
SafeQ<T>::~SafeQ()
{	
	if(pthread_mutex_destroy(&m_mutex) != 0)
	{
		throw("mutex destroy failed");
		
	}
	
	if(pthread_cond_destroy(&safeRemoveCV) != 0)
	{
		throw("CV destroy failed");
	}
}



template <class T>
bool SafeQ<T>::Push(const T _element)
{
	if(pthread_mutex_lock(&m_mutex) != 0)
	{
		throw("mutex lock failed");
	}

	m_messageQ.push(_element);

	if(pthread_cond_signal(&safeRemoveCV) != 0)
	{
		throw("mutex unlock failed");
	}

	if(pthread_mutex_unlock(&m_mutex) != 0)
	{
		throw("mutex unlock failed");
	}

	return true;
}



template <class T>
T SafeQ<T>::Pop()
{	
	if(pthread_mutex_lock(&m_mutex) != 0)
	{
		throw("mutex lock failed");
	}

	while((m_messageQ.empty()) && (!m_exit))
	{
		if(pthread_cond_wait(&safeRemoveCV, &(m_mutex)) != 0)
		{
			throw("pthread_cond_wait failed");
		}
		
		//here is the way to make all waiting threads exit safely:
		if(m_exit == true)
		{
			if(pthread_mutex_unlock(&m_mutex) != 0)
			{
				throw("mutex unlock failed");
			}

			throw "stop message";
		}
	}

	T tempElm = m_messageQ.front();
	m_messageQ.pop();

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


#endif//__SAFEQCV_H__




















