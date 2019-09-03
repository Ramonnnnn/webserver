#ifndef __SEMAPHEXCEPT_H__
#define __SEMAPHEXCEPT_H__

#include <stdexcept>

namespace advcpp
{

/**
 *  @brief Constructor thrown exceptions:
 */
class MaxInitValueExceeded : public std::exception
{
public:
    explicit MaxInitValueExceeded(const std::string& message)
    	: m_msg(message)
    {}
    
    virtual ~MaxInitValueExceeded() throw () 
    {}

protected:
    std::string m_msg;
};

/**
 *  @brief Wait thrown exceptions:
 */
class CallInterruptedBySignalHandler : public std::exception
{
public:
    explicit CallInterruptedBySignalHandler(const std::string& message)
        : m_msg(message)
    {}
    
    virtual ~CallInterruptedBySignalHandler() throw () 
    {}

protected:
    std::string m_msg;
};

/**
 *  @brief Post thrown exceptions:
 */
class OverflowInSemaphoreValue : public std::exception
{
public:
    explicit OverflowInSemaphoreValue(const std::string& message)
        : m_msg(message)
    {}
    
    virtual ~OverflowInSemaphoreValue() throw () 
    {}

protected:
    std::string m_msg;
};

}//advcpp

#endif//__SEMAPHEXCEPT_H__