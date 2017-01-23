#pragma once
#include <chrono>
#include <string>

class PerformanceTimer
{
public:
	PerformanceTimer(const std::string& message);
	~PerformanceTimer();
	void Expire();

private :
	const std::string _message;
	std::chrono::time_point<std::chrono::system_clock> _start;
	bool _didExpire;
};

