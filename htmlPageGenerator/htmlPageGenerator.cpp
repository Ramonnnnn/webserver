#include "htmlPageGenerator.h"
#include <time.h>
#include <iostream>
#include <dirent.h>

namespace advcpp
{

using namespace std;

std::tr1::shared_ptr<HtmlPage> HtmlPageGenerator::ProcessNewHtmlPage(string& _templateHttpPage, vector<tr1::shared_ptr<IArgumentsTranslator> >& _argsTranslators)
{
	string htmlPageHeader(""); //TODO for later thinking of how to prevent this dummy
	for(vector<tr1::shared_ptr<IArgumentsTranslator> >::iterator it = _argsTranslators.begin() ; it != _argsTranslators.end(); ++it)
	{
		(*it)->Translate(&_templateHttpPage);
	}

	TranslateImages(_templateHttpPage);

	return std::tr1::shared_ptr<HtmlPage>(new HtmlPage(htmlPageHeader, _templateHttpPage));
}


void HtmlPageGenerator::TranslateBodyArguments(string& _templateHttpPage, string& _userFirstName, string& _userLastName)
{
	TranslateUserName(_templateHttpPage, _userFirstName, _userLastName);
	TranslateDateTime(_templateHttpPage);
	TranslateImages(_templateHttpPage);
}	


void HtmlPageGenerator::TranslateUserName(string& _templateHttpPage, string& _userFirstName, string& _userLastName)
{
	size_t position = _templateHttpPage.find("@arg:firstname@");
	if(position == string::npos) //not found
	{
		return;
	}

	_templateHttpPage.replace(position, SIZEOFFIRSTNAME,  _userFirstName);
}


void HtmlPageGenerator::TranslateImages(string& _templateHttpPage)
{
	DoRepeatFile(_templateHttpPage);
}


void HtmlPageGenerator::GetExistingImageFileNames(const string& _dirName, vector<string>& _images)
{
	DIR* dir;
	struct dirent *ent;
	if((dir = opendir(_dirName.c_str())) != 0) 
	{
		/* print all the files and directories within directory */
		while((ent = readdir(dir)) != 0) 
		{
			if(ent->d_name[0] != '.')
			{
				_images.push_back(ent->d_name);
			}
		}

	closedir(dir);
	} 
	else 
	{
		/* could not open directory */
	}
}


void HtmlPageGenerator::DoRepeatFile(string& _templateHttpPage)
{
	vector<string> images;
	size_t position = _templateHttpPage.find("<@repeatfile");
	if(position == string::npos) //not found
	{
		return;
	}

	size_t repeatFileStart = position;
	string imgDirName = FindDirName(_templateHttpPage, repeatFileStart);
	GetExistingImageFileNames(imgDirName, images);

	string templateImgFileSrc = GetTemplateImgFileSrc(_templateHttpPage, repeatFileStart);
	string totalTemplatesNeeded = MultiplyTemplateToMatchImagesNumber(templateImgFileSrc, images.size());
	
	size_t repeatfileEnd = _templateHttpPage.find("<@/repeatfile>", repeatFileStart);
	_templateHttpPage.replace(repeatFileStart, repeatfileEnd - repeatFileStart + SIZEOF_REPEATFILE_END,  totalTemplatesNeeded);
	
	IntegrateFileNamesIntoTemplate(_templateHttpPage, repeatFileStart, images, imgDirName);
}


string HtmlPageGenerator::MultiplyTemplateToMatchImagesNumber(string& _templateImgFileSrc, unsigned long _imageContainerSize)
{
	_templateImgFileSrc += '\n';
	_templateImgFileSrc = "<td>" + _templateImgFileSrc + "</td>";
	string totalTemplatesNeeded("");
	size_t i = 0;
	for(; i < _imageContainerSize; ++i)
	{	
		if(i % 2 == 0)
		{
			totalTemplatesNeeded += ("<tr>" + _templateImgFileSrc);
		}
		else
		{
			totalTemplatesNeeded += (_templateImgFileSrc + "</tr>");
		}
	}

	if(i % 2 != 0)
	{
		totalTemplatesNeeded += "</tr>";
	}
	totalTemplatesNeeded = "<table>" + totalTemplatesNeeded + "</table>";
	return totalTemplatesNeeded;
}


void HtmlPageGenerator::IntegrateFileNamesIntoTemplate(string& _templateHttpPage, size_t _repeatFileStart, vector<string>& _images, string& _imgDirName)
{
	size_t position = _repeatFileStart;
	for(vector<string>::const_iterator it = _images.begin(); it < _images.end(); ++it)
	{
		position = _templateHttpPage.find("@file@", position);
		_templateHttpPage.replace(position, SIZEOFFILE,  *it);
		position = _templateHttpPage.find("@path@", position);
		_templateHttpPage.replace(position, SIZEOFPATH,  _imgDirName + "/" + (*it));
	}
	//cout << _templateHttpPage << '\n';
}


string HtmlPageGenerator::GetTemplateImgFileSrc(string& _templateHttpPage, size_t _repeatFileStart)
{
	string templateFileSrc;
	size_t position = _templateHttpPage.find("@file@", _repeatFileStart);
	if(position != string::npos) //found
	{
		templateFileSrc = "@file@";
		templateFileSrc += '\n';
	}

	position = _templateHttpPage.find("<img", _repeatFileStart);
	if(position != string::npos)
	{
		size_t imgTagPosEnd = _templateHttpPage.find_first_of(">", position) + 1;
		templateFileSrc += _templateHttpPage.substr(position , imgTagPosEnd - position);
	}
	return templateFileSrc;
}


string HtmlPageGenerator::FindDirName(string& _templateHttpPage, size_t _repeatFileStart)
{
	size_t dirNamePosBegin = _templateHttpPage.find_first_of("\"", _repeatFileStart) + 1;
	size_t dirNamePosEnd = _templateHttpPage.find_first_of("\"", dirNamePosBegin);
	return _templateHttpPage.substr(dirNamePosBegin , dirNamePosEnd - dirNamePosBegin);
}


void HtmlPageGenerator::TranslateDateTime(string& _templateHttpPage)
{
	time_t rawtime;
	struct tm* timeinfo;
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	string dateTime = asctime(timeinfo);
	string curdate = dateTime.substr(4, 6);
	curdate += " ";
	curdate += dateTime.substr(20, 4);
	string curtime = dateTime.substr(11, 8);
	//time replacement:
	size_t position = _templateHttpPage.find("@time@");
	if(position != string::npos)
	{
		_templateHttpPage.replace(position, SIZEOFTIME,  curtime);
		//_templateHttpPage.replace(position, SIZEOFTIME,  curtime);
		position += SIZEOFTIME;
	}
	//date replacement:
	position = _templateHttpPage.find("@date@", position);
	if(position != string::npos)
	{
		_templateHttpPage.replace(position, SIZEOFDATE,  curdate);
		position += SIZEOFDATE;
	}
}

}