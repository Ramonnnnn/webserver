#ifndef __SOCKET_H__
#define __SOCKET_H__

#include "uncopyable.h"
#include <cstddef>
#include <string>
#define DEFINE_EXEPTION(someException)\
class someException: public std::exception\
{\
public:\
    someException() {}\
    virtual ~someException() throw (){}\
};

namespace advcpp
{

//======================== EXCEPTIONS ================================
DEFINE_EXEPTION(ConnectionHasBeenAborted)
DEFINE_EXEPTION(SignalInterruptedBeforeConnection)
DEFINE_EXEPTION(SocketNotAcceptingConnections)
DEFINE_EXEPTION(OpenMaxFileDescriptorsOpened)
DEFINE_EXEPTION(MaximumNumberOfDescriptorsOpened)
DEFINE_EXEPTION(NoBufferSpaceForAcceptAvailable)
DEFINE_EXEPTION(InsufficientMemoToCompleteOperation)
DEFINE_EXEPTION(ProtocolErrorOccured)
//===================================================================

static const int BUFFERSIZE = 1496;

class Socket : public Uncopyable
{
public:
	Socket() 
		: m_isInitialized(false) { }
	~Socket();
	int Read(std::string& _str);
	int Write(const std::string& _str);
	void Accept(int _listeningSocket);
	int GetFd() const {return m_fd;}
private:
	void ThrowAcceptException(int _status);

	int m_fd;
	bool m_isInitialized;
};

} //namespace advcpp

#endif//__SOCKET_H__