#ifndef __LISTENINGSOCKET_H__
#define __LISTENINGSOCKET_H__

#include "socket.h"
#include <cstddef>
#include <list>
#include <tr1/memory>

namespace advcpp
{

class ListeningSocket
{
public:
	ListeningSocket(size_t _maxConnectionsPermitted, unsigned short _port);
	std::tr1::shared_ptr<Socket> Listen();

private:	
	void SetAsReusableSocket();

	int m_listeningSocket;
};

} //namespace advcpp

#endif//__LISTENINGSOCKET_H__