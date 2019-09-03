#ifndef __MUTEXEXCEPT_H__
#define __MUTEXEXCEPT_H__

#include <stdexcept>

namespace advcpp
{

class MutexException : public std::exception
{
public:
    explicit MutexException(const std::string& message)
    	: m_msg(message)
    {}

    virtual ~MutexException() throw () 
    {}

    virtual const char* what() const throw ()
    {
       return m_msg.c_str();
    }

protected:
    std::string m_msg;
};

/**
 *  @brief Constructor thrown exceptions:
 */
class InsufficientResourcesException : public MutexException
{
public:
    explicit InsufficientResourcesException(const std::string& message)
        : MutexException(message)
    {}
};

class InsufficientMemoryException : public MutexException
{
public:
    explicit InsufficientMemoryException(const std::string& message)
        : MutexException(message)
    {}
};

class NoPermissionException : public MutexException
{
public:
    explicit NoPermissionException(const std::string& message)
        : MutexException(message)
    {}
};

class MutexBusyException : public MutexException
{
public:
    explicit MutexBusyException(const std::string& message)
        : MutexException(message)
    {}
};

class AttributeInvalid : public MutexException
{
public:
    explicit AttributeInvalid(const std::string& message)
        : MutexException(message)
    {}
};

/**
 *  @brief Dtor thrown exceptions:
 */
class MutexDestroyedWhileLocked : public MutexException
{
public:
    explicit MutexDestroyedWhileLocked(const std::string& message)
    	: MutexException(message)
    {}
};

/**
 *  @brief Lock, unlock thrown exceptions:
 */
class DeadlockException : public MutexException
{
public:
    explicit DeadlockException(const std::string& message)
        : MutexException(message)
    {}
};

class MaximumrecursiveLocksExceeded : public MutexException
{
public:
    explicit MaximumrecursiveLocksExceeded(const std::string& message)
        : MutexException(message)
    {}
};

}//advcpp

#endif//__MUTEXEXCEPT_H__