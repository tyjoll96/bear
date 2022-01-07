#pragma once

#include "bear/core/platform_detection.h"

#ifdef BR_DEBUG
	#if defined(BR_PLATFORM_WINDOWS)
		#define BR_DEBUGBREAK() __debugbreak()
	#elif defined(BR_PLATFORM_LINUX)
		#include <signal.h>
		#define BR_DEBUGBREAK() raise(SIGTRAP)
	#else
		#error "Platform doesn't support debugbreak yet!"
	#endif
	#define BR_ENABLE_ASSERTS
#else
	#define BR_DEBUGBREAK()
#endif

#ifdef BR_ENABLE_ASSERTS
	#define BR_ASSERT(x, ...) { if(!(x)) { BR_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define BR_CORE_ASSERT(x, ...) { if(!(x)) { BR_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define BR_ASSERT(x, ...)
	#define BR_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define BR_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace bear
{
	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args)
	{
		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}