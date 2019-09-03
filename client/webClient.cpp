#include "webClient.h"
#include <iostream>

namespace advcpp
{

using namespace std;

WebClient::WebClient(WebServer* _webServer)
	: m_webServer(_webServer)
{

}


void WebClient::Start()
{
	string request;
	cout << "Please insert http request:" << '\n';
	cin >> request;
	m_webServer->IssueHttpRequest(request);
}

} //namespace advcpp