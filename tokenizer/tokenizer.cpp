#include "tokenizer.h"
#include <sstream>



vector<string> & Tokenizer_t::tokenize(const string &_line)
{
	string tempStr;
	istringstream iss(_line);
	size_t prev = 0;
	size_t pos;
	m_tokens.clear();

	while(getline(iss, tempStr, ' '))
	{
	    while ((pos = tempStr.find_first_of("/ ?=&", prev)) != string::npos)
	    {
	        if (pos >= prev)
	        {
	        	if(pos > prev)
	        	{
	        		m_tokens.push_back(tempStr.substr(prev, pos-prev));
	        	}
	        	
	        	if(tempStr.substr(pos,1) != "\t")
	        	{
	        		m_tokens.push_back(tempStr.substr(pos,1));
	        	}
	            
	        }

	        prev = pos + 1;
	    }

	    if (prev < tempStr.length())
	    {
	    	m_tokens.push_back(tempStr.substr(prev, string::npos));
	    }

        prev = 0;
	}
	
	return m_tokens;
}




// set<string> Tokenizer_t::s_types = {"char", "short", "int", "long", "float", "double", "void"};

// set<string> Tokenizer_t::s_keywords = {"if", "else", "for" , "while", "class", "private", "public", "protected", "main", "const", "virtual"};

// set<string> Tokenizer_t::s_operators = {"++", "--", "==", "->" , "=", "+", "-", "*", "&", "<<", ">>"};

// set<string> Tokenizer_t::s_delimiters = {"(", ")", "[", "]" , "{" , "}" ,";" , "<", ">" , "=", "+", "-", "*", "&"};



/*
vector<string> & Tokenizer_t::tokenize(const string &_line)
{
	string tempStr;
	istringstream iss(_line);
	size_t prev = 0;
	size_t pos;
	m_tokens.clear();

	while(getline(iss, tempStr, ' '))
	{
	    while ((pos = tempStr.find_first_of("()[]{};<>=+-*&", prev)) != string::npos)
	    {
	        if (pos >= prev)
	        {
	        	if(pos > prev)
	        	{
	        		m_tokens.push_back(tempStr.substr(prev, pos-prev));
	        	}

	            m_tokens.push_back(tempStr.substr(pos,1));
	        }

	        prev = pos + 1;
	    }

	    if (prev < tempStr.length())
	    {
	    	m_tokens.push_back(tempStr.substr(prev, string::npos));
	    }

        prev = 0;
	}
	
	return m_tokens;
}
*/
