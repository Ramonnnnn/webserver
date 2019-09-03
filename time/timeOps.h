#ifndef __TIMEOPS_H__
#define __TIMEOPS_H__
#include <time.h>
namespace advcpp
{

timespec AddTimespec(timespec t1, timespec t2);
timespec ConvertMillisToTimespec(unsigned int _millis);

} //namespace advcpp

#endif//__TIMEOPS_H__