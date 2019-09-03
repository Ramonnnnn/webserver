#include <stdexcept>

#define DEFINE_EXCEPTION(someException)\
class someException: public std::exception\
{\
public:\
    someException() {}\
    virtual ~someException() throw (){}\
};

