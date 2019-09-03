
TCPSERVER_Err StartServer(TCPServer *_server, CallBack _callback, void *_context)
{
	struct sockaddr_in cli_addr;
	int newsockfd; 
	socklen_t clilen;
	fd_set active_fd_set, read_fd_set;
   	size_t i;
   	size_t maxConnectionsPermitted;

	if((_server == NULL) || (_callback == NULL))
	{
		perror("null pointer");
		return TCPSERVER_UNINITIALIZED_ERROR;
	}

	maxConnectionsPermitted = _server->m_maxConnectionsPermitted;
   	listen(_server->m_sockfd, maxConnectionsPermitted); /* check maybe lower ? */
   	clilen = sizeof(cli_addr);
	/* Initialize the set of active sockets. */
	FD_ZERO(&active_fd_set);
	FD_SET(_server->m_sockfd, &active_fd_set);

	while(!(*(_server->m_isSystemPaused)))
	{
		throwOldFdsOfList(_server->m_fdList);
		/* Block until input arrives on one or more active sockets. */
		read_fd_set = active_fd_set;
		if(select(FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0)
		{
			perror("select");
			exit(EXIT_FAILURE);
		}

		/* Service all the sockets with input pending. */
		for(i = 0; i < FD_SETSIZE; ++i)
		{
			if(FD_ISSET(i, &read_fd_set))
			{
				if(i == _server->m_sockfd) /* the server's own socket */
				{
					if(List_Size(_server->m_fdList) < maxConnectionsPermitted)
					{
						/* Connection request from client on original socket. */
						newsockfd = accept(_server->m_sockfd, (struct sockaddr *)&cli_addr, &clilen);
						if (newsockfd < 0)
						{
							perror("ERROR on accept");						
						}

						addToFdList(_server->m_fdList, newsockfd, &active_fd_set);
						/*setsockopt(newsockfd, SOL_SOCKET, SO_LINGER, &so_linger, sizeof so_linger);*/
						printf("--->new sockid %d\n", newsockfd);
						/*fprintf (stderr, "Server: connect from host %s, port %hd.\n", inet_ntoa (clientname.sin_addr), ntohs (clientname.sin_port));*/
						FD_SET(newsockfd, &active_fd_set);
					}
				}
				else /* TODO put an if here, don't skeep an option */
				{
					/* Data arriving on an already-connected socket. */
					if(interactWithClient(i, _callback, _server->m_buffer, _server->m_buffSize, _context) < 0)
					{
						close(i);
						/*printf("%s\n", "closed");*/
						FD_CLR(i, &active_fd_set);
						removeOfFdList(_server->m_fdList ,i);
					}
					else /* interaction with client succeeded */
					{
						updateFdLastTimeOfUse(_server->m_fdList ,i);
					}
				}
			}
		}
	}

	return TCPSERVER_OK;
}













int WebServer::InteractWithClient(Socket &_socket)
{
	/* If connection is established then start communicating */
	//std::list<Socket>::iterator itSocket = std::find_if(m_clientSockets.begin(), m_clientSockets.end(), IsEqual(_socketfd));
	//char buffer[BUFFERSIZE];
	string buffer;
	int n = _socket.Read(buffer);
	if(n == 0)
	{
		/* EOF */
		return -1;
	}
	else
	{
		/* Write a response to the client */
		HttpRequestManager httpRequestManager(buffer);
		_socket.Write(httpRequestManager.GetHeader());

		//content:
		size_t position = 0;
		const unsigned int MTU = 1500;
		string chunkedMessage;
		size_t bodyLength = httpRequestManager.GetBody().length();

		while(position < bodyLength)
		{
			chunkedMessage = httpRequestManager.GetBody().substr(position, MTU);
			position += MTU;
			//n = write(_socket.GetFd(), chunkedMessage.c_str(), chunkedMessage.length());
			_socket.Write(chunkedMessage);
		}

		return 0;
	}
}










		

		
		

		
		

		
//m_clientSockets.push_back(newSocket);
//m_clientSockets.remove_if(IsEqual(newSocket.GetFd()));