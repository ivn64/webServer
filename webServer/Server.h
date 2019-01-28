#pragma once

#include <mutex>

class Server
{
public:
	Server();
	~Server();
	void startServer();

private:
	void sendRequest(int client_socket);

private:
	int m_listenSocket;
	struct addrinfo* m_addr = nullptr;
	std::mutex m_mutex;
};

