// ifstream htmlFile(fileName.c_str());
		// if(htmlFile.is_open())
		// {
		// 	stringstream htmlFileExtract;
		// 	htmlFileExtract << htmlFile.rdbuf();
		// 	string templateHtmlPage = htmlFileExtract.str();
		// 	htmlFile.close();

		// 	htmlPageSp = m_htmlPageGenerator.ProcessNewHtmlPage(templateHtmlPage, userFirstName, userLastName);
		// }









tr1::shared_ptr<HtmlPage> HttpRequestManager::ProcessNewRequest(std::string& _httpRequest)
{
	string fileName("");
	tr1::shared_ptr<HtmlPage> htmlPageSp(new HtmlPage());
	if(ExtractFileName(_httpRequest, fileName) == true)
	{
		string userFirstName("");
		string userLastName("");
		ExtractUserName(_httpRequest, userFirstName, userLastName);
		
		string templateHtmlPage("");
		if(ExtractFileContents(fileName, templateHtmlPage) == true)
		{
			htmlPageSp = m_htmlPageGenerator.ProcessNewHtmlPage(templateHtmlPage, userFirstName, userLastName);
			htmlPageSp->GetHeader() = GenerateNormalResponceHeader(htmlPageSp->GetBody().length(), fileName);
		}
		else //couldn't open file:
		{
			if(HttpRequestManager::ExtractFileContents(string& _fileName, string& _contents))
			{

			}
			
			htmlPageSp->GetHeader() = GetError404Header(htmlPageSp->GetBody().length(), fileName);
		}

		return htmlPageSp;
	}
	else //file name error
	{
		GetError404Header(size_t _bodyLength, string& _fileName)
		return htmlPageSp;
	}




// string HttpRequestManager::GenerateNormalResponceHeader(size_t _bodyLength, string& _fileName)
// {
// 	stringstream replyHeader;
// 	replyHeader << "HTTP/1.1 200 OK\nContent-Length: "; 
// 	replyHeader << _bodyLength;
// 	replyHeader << '\n';
// 	size_t found = _fileName.find_first_of(".");
// 	if(found != std::string::npos) //found a dot
// 	{
// 		replyHeader << "Content-Type: ";
// 		string fileExtension = _fileName.substr(found + 1, string::npos);
// 		if((fileExtension == "jpg") || (fileExtension == "gif") || (fileExtension == "png"))
// 		{
// 			(replyHeader << "image/") << fileExtension;
// 		}
// 		else if(fileExtension == "html")
// 		{
// 			(replyHeader << "text/") << fileExtension;
// 		}
// 	}
// 	replyHeader << "\n\n";
// 	return replyHeader.str(); 
// }


// string HttpRequestManager::ExtractFileName(const string& _str) const
// {
// 	size_t found1 = _str.find_first_of("/");
// 	if(found1 == std::string::npos)
// 	{
// 		throw CanNotExtractFileName();
// 	}

// 	string result = _str.substr(found1 + 1, string::npos);
	
// 	size_t found2 = result.find_first_of(" ?");
// 	if(found2 == std::string::npos)
// 	{
// 		throw CanNotExtractFileName();
// 	}

// 	result = result.substr(0, found2);

// 	return result;
// }


// void HttpRequestManager::ExtractUserName(string& _httpRequest, string& _userFirstName, string& _userLastName)
// {
// 	size_t found1 = _httpRequest.find("fname=");
// 	if(found1 == std::string::npos)
// 	{
// 		return;
// 	}
// 	found1 = _httpRequest.find_first_of("=", found1); //TODO put into a class or function all these cacls
// 	size_t found2 = _httpRequest.find_first_of("&", found1) - 1;
// 	_userFirstName = _httpRequest.substr(found1 + 1, found2 - found1);

// 	found1 = _httpRequest.find("lname=");
// 	found1 = _httpRequest.find_first_of("=", found1);
// 	found2 = _httpRequest.find_first_of(" ", found1) - 1;
// 	_userLastName = _httpRequest.substr(found1 + 1, found2 - found1);
// }



// string HttpRequestManager::GetErrorHeader(size_t _bodyLength, size_t _errorNum, string& _errorText)
// {
// 	stringstream replyHeader;
// 	replyHeader << "HTTP/1.1 ";
// 	replyHeader << _errorNum; 
// 	replyHeader << " ";
// 	replyHeader << _errorText;
// 	replyHeader << "\nContent-Length: "; 
// 	replyHeader << _bodyLength;
// 	replyHeader << '\n';
// 	replyHeader << "Content-Type: text/html";
// 	replyHeader << "\n\n";
// 	return replyHeader.str(); 
// }