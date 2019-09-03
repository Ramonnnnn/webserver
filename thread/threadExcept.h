#ifndef __THREADEXCEPT_H__
#define __THREADEXCEPT_H__

#include <stdexcept>

namespace advcpp
{

class ThreadException : public std::exception
{
public:
    explicit ThreadException(const std::string& message)
    	: m_msg(message)
    {}

    virtual ~ThreadException() throw () 
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
class InvalidAttributeSettingException : public ThreadException
{
public:
    explicit InvalidAttributeSettingException(const std::string& message)
    	: ThreadException(message)
    {}
};

/**
 *  @brief Join, Timed Join and Cancel thrown exceptions:
 */
class NotJoinableThreadException : public ThreadException
{
public:
    explicit NotJoinableThreadException(const std::string& message)
    	: ThreadException(message)
    {}
};

class ThreadIdNotFoundException : public ThreadException
{
public:
    explicit ThreadIdNotFoundException(const std::string& message)
    	: ThreadException(message)
    {}
};

class OperationTimedOut : public ThreadException
{
public:
    explicit OperationTimedOut(const std::string& message)
    	: ThreadException(message)
    {}
};

}//advcpp

#endif//__THREADEXCEPT_H__