void HeaderGenerator::ExtractUserName(string& _httpRequest, string& _userFirstName, string& _userLastName)
{
	size_t found1 = _httpRequest.find("fname=");
	if(found1 == std::string::npos)
	{
		return;
	}
	found1 = _httpRequest.find_first_of("=", found1); //TODO put into a class or function all these cacls
	size_t found2 = _httpRequest.find_first_of("&", found1) - 1;
	_userFirstName = _httpRequest.substr(found1 + 1, found2 - found1);

	found1 = _httpRequest.find("lname=");
	found1 = _httpRequest.find_first_of("=", found1);
	found2 = _httpRequest.find_first_of(" ", found1) - 1;
	_userLastName = _httpRequest.substr(found1 + 1, found2 - found1);
}