#pragma once
#include "logger.hpp"
#include <unordered_map>

namespace fastlog::detail {
class FileLoggerManager : util::noncopyable {
  public:
	FileLogger& make_logger(const std::string& loggername, fs::path filepath);
	void		delete_logger(const std::string& loggername);
	FileLogger* get_logger(const std::string& loggername);

  private:
	std::unordered_map<std::string, FileLogger> loggers_;
};
}  // namespace fastlog::detail
