#pragma once
#include "logger.hpp"
#include "loglevel.hpp"
#include "manager.hpp"

namespace fastlog {
inline auto& console = detail::util::Singleton<detail::ConsoleLogger>::instance();
void		 set_console_log_level(LogLevel level);
}  // namespace fastlog

namespace fastlog::file {
using FileLogger						= detail::FileLogger;
inline auto&		file_logger_manager = detail::util::Singleton<detail::FileLoggerManager>::instance();
detail::FileLogger& make_logger(const std::string& logger_name, std::filesystem::path log_path = "");
void				delete_logger(const std::string& logger_name);
[[nodiscard]] fastlog::detail::FileLogger* get_logger(const std::string& logger_name);

}  // namespace fastlog::file
