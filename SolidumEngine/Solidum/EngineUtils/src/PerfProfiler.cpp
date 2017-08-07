#include "../include/PerfProfiler.h"

void PerfProfiler::start()
{
	_activeProfiles.push_back(TimerSet(std::chrono::high_resolution_clock::now()));
}

void PerfProfiler::end(std::string msg)
{
	auto end = std::chrono::high_resolution_clock::now();

	auto start = _activeProfiles.front().perf_profiler_timer_start;

	_activeProfiles.pop_front();

	std::cout << msg << " " << std::chrono::duration_cast<std::chrono::milliseconds>
		(end - start).count() << "ms" << std::endl;
}
