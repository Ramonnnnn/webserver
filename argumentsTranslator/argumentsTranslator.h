#ifndef __ARGUMENTSTRANSLATOR_H__
#define __ARGUMENTSTRANSLATOR_H__

#include "tokenizer.h"
#include <cstddef>
#include <string>
#include <time.h>
#include <map>

namespace advcpp
{

static const char* TIME = "@time@";
static const char* DATE = "@date@";

static void SearchAndReplaceVal(string& _htmlPage, string _arument, size_t _size, string& _value);

class IArgumentsTranslator
{
public:
	~IArgumentsTranslator() { }
	virtual void Translate(std::string* _htmlPage) = 0;

};


static void SearchAndReplaceVal(string& _htmlPage, string _arument, size_t _size, string& _value)
{
	size_t position = 0;
	while(position != string::npos)
	{
		position = _htmlPage.find(_arument, position);
		if(position != string::npos)
		{
			_htmlPage.replace(position, _size,  _value);
			position += _size;
		}
	}
}


struct TimeTranslator : public IArgumentsTranslator
{
	friend void SearchAndReplaceVal(string& _htmlPage, const char *_arument, size_t _size, string& _value);
	static const size_t SIZEOFTIME = 6;
	virtual void Translate(std::string* _htmlPage)
	{
		time_t rawtime;
		time(&rawtime);
		struct tm* timeinfo;
		timeinfo = localtime(&rawtime);
		string dateTime = asctime(timeinfo);
		string curtime = dateTime.substr(11, 8);

		SearchAndReplaceVal(*_htmlPage, TIME, SIZEOFTIME, curtime);
	}
};


struct DateTranslator : public IArgumentsTranslator
{
	friend void SearchAndReplaceVal(string& _htmlPage, const char *_arument, size_t _size, string& _value);
	static const size_t SIZEOFDATE = 6;
	virtual void Translate(std::string* _htmlPage)
	{
		time_t rawtime;
		struct tm* timeinfo;
		time(&rawtime);
		timeinfo = localtime(&rawtime);
		string dateTime = asctime(timeinfo);
		string curdate = dateTime.substr(4, 6);
		curdate += " ";
		curdate += dateTime.substr(20, 4);

		SearchAndReplaceVal(*_htmlPage, DATE, SIZEOFDATE, curdate);
	}
};


struct ArgsTranslator : public IArgumentsTranslator
{
	friend void SearchAndReplaceVal(string& _htmlPage, const char *_arument, size_t _size, string& _value);
	ArgsTranslator(const map<string, string>& _argsMap)
		: m_argsMap(_argsMap) { }
	virtual void Translate(std::string* _htmlPage)
	{
		size_t position = 0;
		while(1)
		{
			position = _htmlPage->find("@arg:");
			if(position == string::npos)
			{
				break;
			}
			size_t startArgPos = _htmlPage->find_first_of(":", position) + 1;
			size_t endPos = _htmlPage->find_first_of("@", position + 1);
			if(endPos == string::npos)
			{
				break;
			}
			string replaceKey = _htmlPage->substr(startArgPos, endPos - startArgPos);
			_htmlPage->replace(position, endPos - position + 1, m_argsMap.find(replaceKey)->second);
		}
	}

	const map<string, string>& m_argsMap;
};

} //namespace advcpp

#endif//__ARGUMENTSTRANSLATOR_H__