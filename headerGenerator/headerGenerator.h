#ifndef __HEADERGENERATOR_H__
#define __HEADERGENERATOR_H__

#include <cstddef>
#include <string>
#define DEFINE_EXEPTION(someException)\
class someException: public std::exception\
{\
public:\
    someException() {}\
    virtual ~someException() throw (){}\
};

namespace advcpp
{

//======================== EXEPTIONS ================================
DEFINE_EXEPTION(CanNotExtractFileName)
//===================================================================


class HeaderGenerator
{
public:
	std::string GenerateNormalResponceHeader(size_t _bodyLength, std::string& _fileName);
	std::string GenerateErrorHeader(size_t _bodyLength, size_t _errorNum, std::string& _errorText);
	std::string ExtractFileName(const std::string& _str) const;

private:

};

} //namespace advcpp

#endif//__HEADERGENERATOR_H__