#pragma once

#include <thread>
#include <vector>
#include <queue>
#include <mutex>

class Manager
{
public:
	Manager();
	~Manager();

	void addToQueue(int socket);

private:
	void doJob();
	int getFromQueue();
	void sendRequest(int client_socket);

private:
	std::vector<std::thread> m_threads;
	std::queue<int> m_queue;
	std::mutex m_mutex;
};

