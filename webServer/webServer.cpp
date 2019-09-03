#include "webServer.h"
#include "socketOutput.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <unistd.h>

namespace advcpp
{

using namespace std;

bool isWorking = true;

static void SignalHandler(int _signal, siginfo_t* _infoSig, void* _context);

struct IsEqual 
{
	IsEqual(int _fd)
		: m_fd(_fd) { }
	bool operator() (const Socket& _sk) { return (_sk.GetFd() == m_fd); }

	int m_fd;
};


struct InteractWithSocket : public IRunnable
{
	InteractWithSocket(WebServer& _webServer, tr1::shared_ptr<Socket> _spSocket)
		: m_spSocket(_spSocket), m_webserver(_webServer) { }
	void Run()
	{
		m_webserver.InteractWithClient(m_spSocket);
	}

	tr1::shared_ptr<Socket> m_spSocket;
	WebServer& m_webserver;
};


WebServer::WebServer(size_t _numOfThreads)
	: m_listeningSocket(128, 8888), m_threadPool(_numOfThreads)
{
}


static void SignalHandler(int _signal, siginfo_t* _infoSig, void* _context)
{
	isWorking = false;
}


void WebServer::Start()
{
	struct sigaction action;
	action.sa_handler = NULL;
    action.sa_sigaction = SignalHandler;
	action.sa_flags = SA_SIGINFO;	
	sigaction(SIGINT, &action, NULL);

	m_threadPool.Start();

	while(isWorking)
	{
		tr1::shared_ptr<Socket> newSocketSp(new Socket());
		try
		{
			newSocketSp = m_listeningSocket.Listen();
		}
		catch(SignalInterruptedBeforeConnection& _ex) //This thread might sit on an accept()
		{
			break;
		}
		
		tr1::shared_ptr<IRunnable> spInteractWithSocket(new InteractWithSocket(*this, newSocketSp));
		m_threadPool.InsertToTasksQ(spInteractWithSocket);
		// sleep(2);
		// m_threadPool.Decrease();
	}

	m_threadPool.ShutDown();
}


int WebServer::InteractWithClient(tr1::shared_ptr<Socket> _spSocket)
{
	string httpRequest("");
	int n = _spSocket->Read(httpRequest);
	if(n == 0)
	{
		/* EOF */
		return -1;
	}
	else
	{
		tr1::shared_ptr<HtmlPage> spHtmlPage = m_httpRequestManager.ProcessNewRequest(httpRequest);

		SocketOutput socketout(*_spSocket);
		socketout << spHtmlPage->GetHeader();

		socketout << spHtmlPage->GetBody();

		return 0;
	}
}

}


