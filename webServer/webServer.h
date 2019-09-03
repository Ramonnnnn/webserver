#ifndef __WEBSERVER_H__
#define __WEBSERVER_H__

#include "listeningSocket.h"
#include "httpRequest.h"
#include "threadPool.h"
#include <string>
#include <signal.h>

namespace advcpp
{

class WebServer
{
	friend struct InteractWithSocket;

public:
	WebServer(size_t _numOfThreads);
	void Start();
private:
	int InteractWithClient(std::tr1::shared_ptr<Socket> _spSocket);

	ListeningSocket m_listeningSocket;
	std::list<Socket> m_clientSockets;
	HttpRequestManager m_httpRequestManager;
	ThreadPool m_threadPool;
};

} //namespace advcpp

#endif//__WEBSERVER_H__