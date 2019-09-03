#ifndef __HTTPREQUESTMANAGER_H__
#define __HTTPREQUESTMANAGER_H__

#include "htmlPageGenerator.h"
#include "headerGenerator.h"
#include <cstddef>
#include <string>
#include <map>
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
DEFINE_EXEPTION(CanNotOpenFile)
//===================================================================


class HttpRequestManager
{
public:
	std::tr1::shared_ptr<HtmlPage> ProcessNewRequest(std::string& _httpRequest);

private:
	void InitArgsTranslatorsContainer(vector<tr1::shared_ptr<IArgumentsTranslator> >& _argsTranslators, const map<string, string>& _argsMap);
	std::string ExtractFileContents(std::string& _fileName);
	std::map<string, string> InsertQueryArgsToMap(std::string& _httpRequest);

	HtmlPageGenerator m_htmlPageGenerator;
	HeaderGenerator m_headerGenerator;
	Tokenizer_t m_tokenizer;
};

} //namespace advcpp

#endif//__HTTPREQUESTMANAGER_H__