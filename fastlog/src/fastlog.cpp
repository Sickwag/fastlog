#include "fastlog.hpp"
#include <iostream>

namespace fs = std::filesystem;

void fastlog::set_console_log_level(LogLevel level) { console.set_level(level); }

fastlog::detail::FileLogger& fastlog::file::make_logger(const std::string&	  logger_name,
														std::filesystem::path log_path) {
	if(log_path.empty()) {
		log_path = fs::path{ logger_name };
	}
	if(!log_path.has_filename()) {
		log_path.append(logger_name);
	}
	return file_logger_manager.make_logger(logger_name, log_path);
}

void fastlog::file::delete_logger(const std::string& logger_name) {
	file_logger_manager.delete_logger(logger_name);
}

fastlog::detail::FileLogger* fastlog::file::get_logger(const std::string& logger_name) {
	return file_logger_manager.get_logger(logger_name);
}
