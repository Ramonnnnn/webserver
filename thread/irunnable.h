#ifndef __RUNNABLE_H__
#define __RUNNABLE_H__

class IRunnable
{
public:
	virtual ~IRunnable() { };
	virtual void Run() = 0;
};






#endif//__RUNNABLE_H__