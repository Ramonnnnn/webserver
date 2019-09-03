#include "listeningSocket.h"
#include <cstring>
#include <sys/select.h>
#include <sys/socket.h>
#include <netdb.h>
#include <cassert>
#include <errno.h>

namespace advcpp
{

using namespace std;

ListeningSocket::ListeningSocket(size_t _maxConnectionsPermitted, unsigned short _port)
{
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) 
	{

	}

	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(_port);
	
	if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) 
	{

	}

	listen(sockfd, _maxConnectionsPermitted);
	m_listeningSocket = sockfd;
	SetAsReusableSocket();
}


tr1::shared_ptr<Socket> ListeningSocket::Listen()
{
	fd_set active_fd_set;
	FD_ZERO(&active_fd_set);
	FD_SET(m_listeningSocket, &active_fd_set);
	/* Block until input arrives on one or more active sockets. */
	if(select(FD_SETSIZE, &active_fd_set, NULL, NULL, NULL) < 0)
	{
	}

	tr1::shared_ptr<Socket> newSocketSp(new Socket());
	newSocketSp->Accept(m_listeningSocket);
	return newSocketSp;	
	/*setsockopt(newsockfd, SOL_SOCKET, SO_LINGER, &so_linger, sizeof so_linger);*/
}


void ListeningSocket::SetAsReusableSocket()
{
	int optval = 1;
	ssize_t result = setsockopt(m_listeningSocket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
	if(-1 == result)
	{
		assert(EBADF != errno); //m_socketFd invalid descriptor
		assert(EFAULT != errno); //optval address invalid, or optlen address invalid
		assert(EINVAL != errno); //optlen invalid, or optval value invalid.
		assert(ENOPROTOOPT != errno); //unknown option in the level
		assert(ENOTSOCK != errno); //m_socketFd is a file not socket
	} 
}

}