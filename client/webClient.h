#ifndef __WEBCLIENT_H__
#define __WEBCLIENT_H__

#include "webServer.h"

namespace advcpp
{

class WebClient
{
public:
	WebClient(WebServer* _webServer);
	~WebClient();
	void Start();

private:
	WebServer* m_webServer;
};

} //namespace advcpp

#endif//__WEBCLIENT_H__