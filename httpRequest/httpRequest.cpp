#include "httpRequest.h"
#include "tokenizer.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

namespace advcpp
{

using namespace std;


tr1::shared_ptr<HtmlPage> HttpRequestManager::ProcessNewRequest(std::string& _httpRequest)
{
	map<string, string> argsMap = InsertQueryArgsToMap(_httpRequest);

	string errorText("");
	string fileName("");
	size_t errorNum;
	tr1::shared_ptr<HtmlPage> htmlPageSp(new HtmlPage());
	try
	{
		fileName = m_headerGenerator.ExtractFileName(_httpRequest);
		
		string templateHtmlPage = ExtractFileContents(fileName);
		
		vector<tr1::shared_ptr<IArgumentsTranslator> > argsTranslators;
		InitArgsTranslatorsContainer(argsTranslators, argsMap);
		htmlPageSp = m_htmlPageGenerator.ProcessNewHtmlPage(templateHtmlPage, argsTranslators);
		htmlPageSp->GetHeader() = m_headerGenerator.GenerateNormalResponceHeader(htmlPageSp->GetBody().length(), fileName);

		return htmlPageSp;
	
	}
	catch(CanNotExtractFileName& _e)
	{
		errorText = "Bad Request";
		fileName = "error400.html";
		errorNum = 400;
	}
	catch(CanNotOpenFile& _e)
	{
		errorText = "Not Found";
		fileName = "error404.html";
		errorNum = 404;
	}

	htmlPageSp->GetBody() = ExtractFileContents(fileName);
	htmlPageSp->GetHeader() = m_headerGenerator.GenerateErrorHeader(htmlPageSp->GetBody().length(), errorNum, errorText);
	return htmlPageSp;
}


void HttpRequestManager::InitArgsTranslatorsContainer(vector<tr1::shared_ptr<IArgumentsTranslator> >& _argsTranslators, const map<string, string>& _argsMap)
{
	_argsTranslators.push_back(tr1::shared_ptr<IArgumentsTranslator>(new TimeTranslator()));
	_argsTranslators.push_back(tr1::shared_ptr<IArgumentsTranslator>(new DateTranslator()));
	_argsTranslators.push_back(tr1::shared_ptr<IArgumentsTranslator>(new ArgsTranslator(_argsMap)));
}


string HttpRequestManager::ExtractFileContents(string& _fileName)
{
	ifstream htmlFile(_fileName.c_str());
	if(htmlFile.is_open())
	{
		stringstream htmlFileExtract;
		htmlFileExtract << htmlFile.rdbuf();
		string contents = htmlFileExtract.str();
		htmlFile.close();
		return contents;
	}

	throw CanNotOpenFile();
}


struct SearchString
{
	SearchString(string& _str)
		: m_target(_str) { }
	bool operator()(string& _str)
	{
		return(_str == m_target);
	}

	string& m_target;
};


map<string, string> HttpRequestManager::InsertQueryArgsToMap(string& _httpRequest)
{
	vector<string> queryStringTokens = m_tokenizer.tokenize(_httpRequest);
	map<string, string> argsMap;
	string searchedString = "=";
	vector<string>::iterator it = queryStringTokens.begin();
	while(1)
	{
		it = find_if(it + 1, queryStringTokens.end(), SearchString(searchedString));
		if(it == queryStringTokens.end())
		{
			break;
		}
		argsMap[*(it - 1)] = (*(it + 1));
	}
	return argsMap;
}

}