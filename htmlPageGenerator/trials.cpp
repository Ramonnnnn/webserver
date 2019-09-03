m_templateHttpPage(_templateHttpPage), m_position(0), m_userFirstName(_userFirstName), m_userLastName(_userLastName)


//std::string m_templateHttpPage;
	//size_t m_position;
	//std::vector<std::string> m_images;
	//size_t m_repeatFileStart;
	//std::string m_imgDirName;
	//std::string m_userFirstName;
	//std::string m_userLastName;



void TranslateBodyArguments(std::string& _templateHttpPage, std::string& _userFirstName, std::string& _userLastName);
	void TranslateDateTime();
	void TranslateImages();
	void GetExistingImageFileNames(const std::string& _dir);
	void DoRepeatFile();
	std::string FindDirName();
	std::string GetTemplateImgFileSrc();
	void IntegrateFileNamesIntoTemplate();
	void TranslateUserName();




	// std::string m_templateHttpPage;
	// std::string m_fileName;
	// std::string m_userFirstName;
	// std::string m_userLastName;