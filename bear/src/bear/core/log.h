#pragma once

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "core.h"

namespace bear {
	class Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& CoreLogger() { return core_logger_; }
		inline static std::shared_ptr<spdlog::logger>& ClientLogger() { return client_logger_; }
	private:
		static std::shared_ptr<spdlog::logger> core_logger_;
		static std::shared_ptr<spdlog::logger> client_logger_;
	};
}

// Core log macros
#define BR_CORE_TRACE(...) ::bear::Log::CoreLogger()->trace(__VA_ARGS__)
#define BR_CORE_INFO(...) ::bear::Log::CoreLogger()->info(__VA_ARGS__)
#define BR_CORE_WARN(...) ::bear::Log::CoreLogger()->warn(__VA_ARGS__)
#define BR_CORE_ERROR(...) ::bear::Log::CoreLogger()->error(__VA_ARGS__)
#define BR_CORE_FATAL(...) ::bear::Log::CoreLogger()->fatal(__VA_ARGS__)

// Client log macros
#define BR_TRACE(...) ::bear::Log::ClientLogger()->trace(__VA_ARGS__)
#define BR_INFO(...) ::bear::Log::ClientLogger()->info(__VA_ARGS__)
#define BR_WARN(...) ::bear::Log::ClientLogger()->warn(__VA_ARGS__)
#define BR_ERROR(...) ::bear::Log::ClientLogger()->error(__VA_ARGS__)
#define BR_FATAL(...) ::bear::Log::ClientLogger()->fatal(__VA_ARGS__)