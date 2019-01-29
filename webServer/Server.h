#pragma once

#include <mutex>

class Server
{
public:
	Server();
	~Server();
	void startServer();

private:
	int m_listenSocket;
	struct addrinfo* m_addr = nullptr;
};

