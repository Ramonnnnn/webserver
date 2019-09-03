#ifndef __SOCKETOUTPUT_H__
#define __SOCKETOUTPUT_H__

#include "output.h"
#include "socket.h"
#include <string>

namespace advcpp
{

class SocketOutput : public IOutput
{
	static const unsigned int MTU = 1500;
public:
	SocketOutput(Socket& _socket);
	virtual SocketOutput& operator<<(const std::string& _fileName);

private:
	Socket& m_socket;
};

} //namespace advcpp

#endif//__SOCKETOUTPUT_H__