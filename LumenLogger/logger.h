#pragma once
#ifndef __LOGGER_H_INCLUDED__
#define __LOGGER_H_INCLUDED__

#ifndef __LOGGER_H_MEMORY__
#define __LOGGER_H_MEMORY__
#include <memory>
#endif // !__LOGGER_H_MEMORY__

#ifndef __LOGGER_H_SPDLOG__
#define __LOGGER_H_SPDLOG__
#include <spdlog/logger.h>
#include <spdlog/fmt/ostr.h>
#endif // !__LOGGER_H_SPDLOG__

#ifndef _LM_LOGLEVEL
#define _LM_LOGLEVEL 2
#endif // !_LM_LOGLEVEL

namespace lumen
{
	struct logger_configuration
	{
		const char* file_format{ "[%T] [%n] [%l]: %v" };
		const char* stdout_format{ "[%T] [%n] %^[%l]%$: %v" };

		const char* log_filename{ "lumen.log" };

		const char* log_name{ "LUMEN" };
		const char* debug_log_name{ "DBG" };
		const char* verbose_log_name{ "VRB" };
	};

	class logger
	{
	private:
		logger() = delete;
		logger(const logger&) = delete;
		logger& operator=(const logger&) = delete;
	public:
		static void init(const logger_configuration& config = {});

		inline static std::shared_ptr<spdlog::logger> get_core_logger()
		{
			return s_core_logger;
		}

		inline static std::shared_ptr<spdlog::logger> get_debug_logger()
		{
			return s_debug_logger;
		}

		inline static std::shared_ptr<spdlog::logger> get_verbose_logger()
		{
			return s_verbose_logger;
		}
	private:
		static std::shared_ptr<spdlog::logger> s_core_logger;
		static std::shared_ptr<spdlog::logger> s_debug_logger;
		static std::shared_ptr<spdlog::logger> s_verbose_logger;
	};
} // namespace lumen

#define LM_CORE_TRACE(...)	::lumen::logger::get_core_logger()->trace(__VA_ARGS__)
#define LM_CORE_INFO(...)	::lumen::logger::get_core_logger()->info(__VA_ARGS__)
#define LM_CORE_WARN(...)	::lumen::logger::get_core_logger()->warn(__VA_ARGS__)
#define LM_CORE_ERROR(...)	::lumen::logger::get_core_logger()->error(__VA_ARGS__)
#define LM_CORE_CRIT(...)	::lumen::logger::get_core_logger()->critical(__VA_ARGS__)

#if _LM_LOGLEVEL >= 2
#define LM_DEBUG_TRACE(...)	::lumen::logger::get_debug_logger()->trace(__VA_ARGS__)
#define LM_DEBUG_INFO(...)	::lumen::logger::get_debug_logger()->info(__VA_ARGS__)
#define LM_DEBUG_WARN(...)	::lumen::logger::get_debug_logger()->warn(__VA_ARGS__)
#define LM_DEBUG_ERROR(...)	::lumen::logger::get_debug_logger()->error(__VA_ARGS__)
#define LM_DEBUG_CRIT(...)	::lumen::logger::get_debug_logger()->critical(__VA_ARGS__)
#else
#define LM_DEBUG_TRACE(...)
#define LM_DEBUG_INFO(...)
#define LM_DEBUG_WARN(...)
#define LM_DEBUG_ERROR(...)
#define LM_DEBUG_CRIT(...)
#endif // _LM_LOGLEVEL >= 2

#if _LM_LOGLEVEL >= 3
#define LM_VERBOSE_TRACE(...)	::lumen::logger::get_verbose_logger()->trace(__VA_ARGS__)
#define LM_VERBOSE_INFO(...)	::lumen::logger::get_verbose_logger()->info(__VA_ARGS__)
#define LM_VERBOSE_WARN(...)	::lumen::logger::get_verbose_logger()->warn(__VA_ARGS__)
#define LM_VERBOSE_ERROR(...)	::lumen::logger::get_verbose_logger()->error(__VA_ARGS__)
#define LM_VERBOSE_CRIT(...)	::lumen::logger::get_verbose_logger()->critical(__VA_ARGS__)
#else
#define LM_VERBOSE_TRACE(...)
#define LM_VERBOSE_INFO(...)
#define LM_VERBOSE_WARN(...)
#define LM_VERBOSE_ERROR(...)
#define LM_VERBOSE_CRIT(...)
#endif // _LM_LOGLEVEL >= 3

#endif // !__LOGGER_H_INCLUDED__
