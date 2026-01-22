#include "manager.hpp"
#include <memory>

fastlog::detail::FileLogger& fastlog::detail::FileLoggerManager::make_logger(const std::string& loggername,
																			 fs::path			filepath) {
	auto [it, inserted] = loggers_.try_emplace(loggername, filepath);
	if(inserted) {
		return it->second;
	} else {
		throw std::runtime_error("you've created logger named " + loggername);
	}
}

void fastlog::detail::FileLoggerManager::delete_logger(const std::string& loggername) {
	auto it = loggers_.find(loggername);
	if(it != loggers_.end()) {
		loggers_.erase(it);
	} else {
		throw std::runtime_error("logger named " + loggername + " doesn't exist");
	}
}

fastlog::detail::FileLogger* fastlog::detail::FileLoggerManager::get_logger(const std::string& loggername) {
	auto it = loggers_.find(loggername);
	if(it != loggers_.end()) {
		return std::addressof(loggers_.at(loggername));
	}
	return nullptr;
}
