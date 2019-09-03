#ifndef __OUTPUT_H__
#define __OUTPUT_H__

#include <string>

namespace advcpp
{

class IOutput
{
public:
	virtual IOutput& operator<<(const std::string&) = 0;

};

} //namespace advcpp

#endif//__OUTPUT_H__