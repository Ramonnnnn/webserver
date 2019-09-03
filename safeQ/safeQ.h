#ifndef __SAFEQCV_H__
#define __SAFEQCV_H__

#include "condVar.h"
#include "mutex.h"
#include "semaph.h"
#include <queue>
#include <pthread.h>
#include <semaphore.h>
#include <iostream>

namespace advcpp
{

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
	bool IsEmpty();
	void StopWaitingOnQ(); //change name, too complicated - unblock

private:
	queue<T> m_messageQ;
	bool m_exit; // a way to make all waiting threads (wait upon pop) exit safely
    Mutex m_mutex;
	CondVar m_safeRemoveCV;
};


template <class T>
void SafeQ<T>::StopWaitingOnQ()
{
	m_exit = true;
	m_safeRemoveCV.Broadcast();
	
}



template <class T>
SafeQ<T>::SafeQ()
	: m_exit(false), m_safeRemoveCV(m_mutex)
{
}


template <class T>
SafeQ<T>::~SafeQ()
{	
}



template <class T>
bool SafeQ<T>::Push(const T _element)
{
	m_mutex.Lock();

	m_messageQ.push(_element);

	m_safeRemoveCV.Signal();

	m_mutex.Unlock();

	return true;
}



template <class T>
T SafeQ<T>::Pop()
{	
	// if(m_exit)
	// {
	// 	string stop("queue shut down");
	// 	throw stop;
	// }
	m_mutex.Lock();

	while((m_messageQ.empty()) && (!m_exit))
	{
		m_safeRemoveCV.Wait();
		
		//here is the way to make all waiting threads exit safely:
		if(m_exit == true)
		{
			m_mutex.Unlock();
			string stop("queue shut down");
			throw stop;
		}
	}

	T tempElm = m_messageQ.front();
	m_messageQ.pop();

	m_mutex.Unlock();

	return tempElm;
}


template <class T>
bool SafeQ<T>::IsEmpty()
{
	return m_messageQ.empty();
}

}

#endif//__SAFEQCV_H__




















