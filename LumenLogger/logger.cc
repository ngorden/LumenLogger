#include "lumen_logger/logger.h"

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <vector>

namespace lumen
{
	std::shared_ptr<spdlog::logger> logger::s_core_logger;
	std::shared_ptr<spdlog::logger> logger::s_debug_logger;
	std::shared_ptr<spdlog::logger> logger::s_verbose_logger;

	void logger::init(const logger_configuration &config)
	{
		std::vector<spdlog::sink_ptr> log_sinks;
		log_sinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		log_sinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>(config.log_filename));

		log_sinks[0]->set_pattern(config.stdout_format);
		log_sinks[1]->set_pattern(config.file_format);

		s_core_logger = std::make_shared<spdlog::logger>(config.log_filename, log_sinks.begin(), log_sinks.end());
		spdlog::register_logger(s_core_logger);
		s_core_logger->set_level(spdlog::level::trace);
		s_core_logger->flush_on(spdlog::level::trace);

#if _LM_LOGLEVEL >= 2
		s_debug_logger = std::make_shared<spdlog::logger>(config.debug_log_name, log_sinks.begin(), log_sinks.end());
		spdlog::register_logger(s_debug_logger);
		s_debug_logger->set_level(spdlog::level::trace);
		s_debug_logger->flush_on(spdlog::level::trace);
#else
		s_debug_logger = nullptr;
#endif // _LM_LOGLEVEL >= 2

#if _LM_LOGLEVEL >= 3
		s_verbose_logger = std::make_shared<spdlog::logger>(config.verbose_log_name, log_sinks.begin(), log_sinks.end());
		spdlog::register_logger(s_verbose_logger);
		s_verbose_logger->set_level(spdlog::level::trace);
		s_verbose_logger->flush_on(spdlog::level::trace);
#else
		s_verbose_logger = nullptr;
#endif // _LM_LOGLEVEL >= 3
	}
} // namespace lumen
