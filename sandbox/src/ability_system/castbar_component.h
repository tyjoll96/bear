#pragma once

#include <chrono>

namespace ralleon
{
	struct CastbarComponent
	{
		std::chrono::steady_clock::duration Duration;
		bool Reverse = false;
		std::chrono::steady_clock::time_point StartTime = std::chrono::steady_clock::time_point::max();
	};
}