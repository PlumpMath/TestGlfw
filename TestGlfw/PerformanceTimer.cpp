#include "PerformanceTimer.h"
#include <chrono>
#include <iostream>

using namespace std;

PerformanceTimer::PerformanceTimer(const std::string& message)
:_message(message),
_start(std::chrono::system_clock::now()),
_didExpire(false)
{
}

PerformanceTimer::~PerformanceTimer()
{
	if (!_didExpire)
		Expire();
}

void PerformanceTimer::Expire()
{
	auto now = chrono::system_clock::now();
	auto elapsed = now - _start;
	auto elapsedMiliseconds = chrono::duration_cast<chrono::milliseconds>(elapsed);
	cout << _message << " -- " << elapsedMiliseconds.count() << " m/s." << endl;
	_didExpire = true;
}
