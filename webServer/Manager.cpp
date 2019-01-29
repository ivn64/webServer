#include "pch.h"
#include "Manager.h"

#include <sstream>
#include <iostream>
#include <winsock2.h>

Manager::Manager()
{

}

Manager::~Manager()
{

}

void Manager::doJob()
{
	auto res = 1;
	while(res != 0)
	{




		res = getFromQueue();
	}
}

void Manager::addToQueue(int socket)
{
	std::lock_guard<std::mutex> lock(m_mutex);
	m_queue.push(socket);
	if (m_queue.size() > 10)
		doJob();
}

int Manager::getFromQueue()
{
	std::lock_guard<std::mutex> lock(m_mutex);
	if (m_queue.empty)
		return 0;
	auto res = m_queue.front();
	m_queue.pop();
	return res;
}

void Manager::sendRequest(int client_socket)
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


