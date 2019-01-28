#include "pch.h"
#include "Server.h"

#include <iostream>
#include <sstream>

#include <winsock2.h>
#include <ws2tcpip.h>

#include <thread>

#pragma comment(lib, "Ws2_32.lib")

Server::Server()
{
	WSADATA wsData;
	WSAStartup(MAKEWORD(2, 2), &wsData);
	
	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	getaddrinfo("127.0.0.1", "8000", &hints, &m_addr);

	m_listenSocket = socket(m_addr->ai_family, m_addr->ai_socktype, m_addr->ai_protocol);
	bind(m_listenSocket, m_addr->ai_addr, (int)m_addr->ai_addrlen);
	listen(m_listenSocket, SOMAXCONN);
}

Server::~Server()
{
	closesocket(m_listenSocket);
	freeaddrinfo(m_addr);
	WSACleanup();
}

void Server::startServer()
{
	while (true)
	{
		// Принимаем входящие соединения
		int client_socket = accept(m_listenSocket, NULL, NULL);

		const int max_client_buffer_size = 1024;
		char buf[max_client_buffer_size];

		int result = recv(client_socket, buf, max_client_buffer_size, 0);

		if (result != 0)
		{
			std::thread thr(&Server::sendRequest, this, client_socket);
			if (thr.joinable())
				thr.join();
		}
	}
}

void Server::sendRequest(int client_socket)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	std::stringstream response;
	response << "Hello world";
	std::cout << "request received" << std::endl;
	int result = send(client_socket, response.str().c_str(), response.str().length(), 0);
	if (result != SOCKET_ERROR)
	{
		std::cout << "responce send" << std::endl;
	}
	closesocket(client_socket);
}
