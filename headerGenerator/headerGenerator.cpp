#include "headerGenerator.h"
#include <sstream>

namespace advcpp
{

using namespace std;


string HeaderGenerator::GenerateNormalResponceHeader(size_t _bodyLength, string& _fileName)
{
	stringstream replyHeader;
	replyHeader << "HTTP/1.1 200 OK\nContent-Length: "; 
	replyHeader << _bodyLength;
	replyHeader << '\n';
	size_t found = _fileName.find_first_of(".");
	if(found != std::string::npos) //found a dot
	{
		replyHeader << "Content-Type: ";
		string fileExtension = _fileName.substr(found + 1, string::npos);
		if((fileExtension == "jpg") || (fileExtension == "gif") || (fileExtension == "png"))
		{
			(replyHeader << "image/") << fileExtension;
		}
		else if(fileExtension == "html")
		{
			(replyHeader << "text/") << fileExtension;
		}
	}
	replyHeader << "\n\n";
	return replyHeader.str(); 
}


string HeaderGenerator::ExtractFileName(const string& _str) const
{
	size_t found1 = _str.find_first_of("/");
	if(found1 == std::string::npos)
	{
		throw CanNotExtractFileName();
	}

	string result = _str.substr(found1 + 1, string::npos);
	
	size_t found2 = result.find_first_of(" ?");
	if(found2 == std::string::npos)
	{
		throw CanNotExtractFileName();
	}

	result = result.substr(0, found2);

	return result;
}


string HeaderGenerator::GenerateErrorHeader(size_t _bodyLength, size_t _errorNum, string& _errorText)
{
	stringstream replyHeader;
	replyHeader << "HTTP/1.1 ";
	replyHeader << _errorNum; 
	replyHeader << " ";
	replyHeader << _errorText;
	replyHeader << "\nContent-Length: "; 
	replyHeader << _bodyLength;
	replyHeader << '\n';
	replyHeader << "Content-Type: text/html";
	replyHeader << "\n\n";
	return replyHeader.str(); 
}

}