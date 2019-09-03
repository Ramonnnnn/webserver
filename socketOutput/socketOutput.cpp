#include "socketOutput.h"

namespace advcpp
{

using namespace std;


SocketOutput::SocketOutput(Socket& _socket)
	: m_socket(_socket)
{
}


SocketOutput& SocketOutput::operator<<(const string& _buffer)
{
	size_t position = 0;
	string chunkedMessage("");
	size_t length = _buffer.length();

	while(position < length)
	{
		chunkedMessage = _buffer.substr(position, MTU);
		position += MTU;
		//n = write(_socket.GetFd(), chunkedMessage.c_str(), chunkedMessage.length());
		m_socket.Write(chunkedMessage);
	}

	return *this;
}

}