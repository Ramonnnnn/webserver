#ifndef __TOKENIZER_T_H__
#define __TOKENIZER_T_H__


#include <string>
#include <stdio.h>
#include <vector>
#include <set>
#include <iostream>


using namespace std;



class Tokenizer_t
{
public:

	Tokenizer_t()
	{
	}

	~Tokenizer_t()
	{
	}

	vector<string> & tokenize(const string &_line);
	
	void print()
	{
		for (std::vector<string>::iterator it = m_tokens.begin() ; it != m_tokens.end(); ++it)
    	std::cout << '\n' << *it;
  		std::cout << '\n';
	}

private:
	Tokenizer_t(const Tokenizer_t &);
	Tokenizer_t & operator=(const Tokenizer_t &);
	

	string m_line;
	vector<string> m_tokens;
	//map<char,int> mymap;
	// static set<string> s_keywords;
	// static set<string> s_types;
	// static set<string> s_operators;
	// static set<string> s_delimiters;
};









#endif








	// size_t getFileLength()
	// {
	// 	fseek(m_fp, 0, SEEK_END);
	// 	size_t size = ftell(m_fp);

	// 	rewind(m_fp);
	// 	//fseek(m_fp, 0L, SEEK_SET);
	// 	return size;
	// }
