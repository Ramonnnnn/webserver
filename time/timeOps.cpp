#include "timeOps.h"

namespace advcpp
{

const unsigned int MILIS_IN_SEC = 1000;
const unsigned int NANOS_IN_MILISEC = 1000000;
const unsigned int NANOS_IN_SEC = 1000000000;

timespec ConvertMillisToTimespec(unsigned int _millis)
{
	struct timespec ts;
	ts.tv_sec += (_millis / MILIS_IN_SEC);
	ts.tv_nsec = (_millis % MILIS_IN_SEC) * NANOS_IN_MILISEC;
	return ts;
}


timespec AddTimespec(timespec t1, timespec t2)
{
    timespec total;
    long nanos;
    total.tv_sec = t1.tv_sec + t2.tv_sec;
    nanos = t1.tv_nsec + t2.tv_nsec;
    
    if (nanos > NANOS_IN_SEC - 1)
    {
        ++total.tv_sec;
    }
    
    nanos = (nanos % NANOS_IN_SEC);
    
    total.tv_nsec = nanos;
    
    return total;
}

}