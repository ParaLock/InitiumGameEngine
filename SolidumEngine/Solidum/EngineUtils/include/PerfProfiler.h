#pragma once
#include "../../sysInclude.h"

class PerfProfiler {
private:

	struct TimerSet {

		TimerSet(std::chrono::time_point<std::chrono::steady_clock>& start) {
			perf_profiler_timer_start = start;
		}

		std::chrono::time_point<std::chrono::steady_clock> perf_profiler_timer_start;
	};

	std::list<TimerSet> _activeProfiles;

public:
	void start();
	void end(std::string msg);
};




