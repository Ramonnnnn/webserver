#ifndef __HTMLPAGEGENERATOR_H__
#define __HTMLPAGEGENERATOR_H__

#include "tokenizer.h"
#include "argumentsTranslator.h"
#include <cstddef>
#include <string>
#include <vector>
#include <tr1/memory>

namespace advcpp
{

struct HtmlPage
{
	HtmlPage(std::string& _header, std::string& _body)
		: m_header(_header), m_body(_body) { }
	HtmlPage()
		: m_header(""), m_body("") { }
	std::string& GetHeader() {return m_header;}
	std::string& GetBody() {return m_body;}
private:
	std::string m_header;
	std::string m_body;
};


class HtmlPageGenerator
{
	static const size_t SIZEOFTIME = 6;
	static const size_t SIZEOFDATE = 6;
	static const size_t SIZEOF_REPEATFILE_END = 14;
	static const size_t SIZEOFFILE = 6;
	static const size_t SIZEOFPATH = 6;
	static const size_t SIZEOFFIRSTNAME = 14;

public:
	std::tr1::shared_ptr<HtmlPage> ProcessNewHtmlPage(std::string& _templateHttpPage, std::vector<tr1::shared_ptr<IArgumentsTranslator> >& _argsTranslators);

private:
	void TranslateBodyArguments(std::string& _templateHttpPage, std::string& _userFirstName, std::string& _userLastName);
	void TranslateUserName(std::string& _templateHttpPage, std::string& _userFirstName, std::string& _userLastName);
	void TranslateImages(std::string& _templateHttpPage);
	void GetExistingImageFileNames(const std::string& _dirName, std::vector<std::string>& _images);
	void DoRepeatFile(std::string& _templateHttpPage);
	void IntegrateFileNamesIntoTemplate(std::string& _templateHttpPage, size_t _repeatFileStart, std::vector<std::string>& _images, std::string& _imgDirName);
	std::string GetTemplateImgFileSrc(std::string& _templateHttpPage, size_t _repeatFileStart);
	std::string FindDirName(std::string& _templateHttpPage, size_t _repeatFileStart);
	void TranslateDateTime(std::string& _templateHttpPage);
	std::string MultiplyTemplateToMatchImagesNumber(std::string& _templateImgFileSrc, unsigned long _imageContainerSize);
};

} //namespace advcpp

#endif//__HTMLPAGEGENERATOR_H__