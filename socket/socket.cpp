#include "socket.h"
#include <cstring>
#include <unistd.h>
#include <netinet/in.h>
#include <cassert>
#include <cerrno>

namespace advcpp
{

using namespace std;

Socket::~Socket()
{
	if(m_isInitialized == true)
	{
		close(m_fd);
	}
}


int Socket::Read(string& _str)
{
	char buffer[BUFFERSIZE];
	int n = read(m_fd, buffer, BUFFERSIZE);
	if(n < 0)
	{
	
	}
	_str = buffer;
	return n;
}


int Socket::Write(const string& _str)
{
	int n = write(m_fd, _str.c_str(), _str.length());
	if (n < 0)
	{

	}

	return n;
}


void Socket::Accept(int _listeningSocket)
{
	struct sockaddr_in cli_addr;
	socklen_t clilen = sizeof(cli_addr);;
	m_fd = accept(_listeningSocket, (struct sockaddr *)&cli_addr, &clilen);
	if(m_fd	< 0)
	{
		assert(errno != EAGAIN);
		assert(errno != EWOULDBLOCK);
		assert(errno != EBADF);
		assert(errno != ENOTSOCK);
		assert(errno != EOPNOTSUPP);
		ThrowAcceptException(errno);
	}
	m_isInitialized = true;
}



void Socket::ThrowAcceptException(int _status)
{
	switch(_status)
	{
		case ECONNABORTED:
			throw ConnectionHasBeenAborted();
		break;
		case EINTR:
			throw SignalInterruptedBeforeConnection();
		break;
		case EINVAL:
			throw SocketNotAcceptingConnections();
		break;
		case EMFILE:
			throw OpenMaxFileDescriptorsOpened();
		break;
		case ENFILE:
			throw MaximumNumberOfDescriptorsOpened();
		break;
		case ENOBUFS:
			throw NoBufferSpaceForAcceptAvailable();
		break;
		case ENOMEM:
			throw InsufficientMemoToCompleteOperation();
		break;
		case EPROTO:
			throw ProtocolErrorOccured();
		break;
		default:
		break;
	}
}

}