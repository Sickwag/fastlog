#include "loglevel.hpp"
#include <utility>

fastlog::detail::LogLevelWrapper::LogLevelWrapper(LogLevel level)
	: level_(level) {}

std::string_view fastlog::detail::LogLevelWrapper::to_string() {
	switch(level_) {
	case LogLevel::Trace:
		return "TRACE";
	case LogLevel::Debug:
		return "DEBUG";
	case LogLevel::Info:
		return "INFO ";
	case LogLevel::Warn:
		return "WARN ";
	case LogLevel::Error:
		return "ERROR";
	case LogLevel::Fatal:
		return "FATAL";
	default:
		std::unreachable();
		return "unknown log level";
	}
}

std::string_view fastlog::detail::LogLevelWrapper::to_color() {
	switch(level_) {
	case LogLevel::Trace:
		return "\033[46m";	// cyan
	case LogLevel::Debug:
		return "\033[44m";	// blue
	case LogLevel::Info:
		return "\033[42m";	// green
	case LogLevel::Warn:
		return "\033[43m";	// yellow
	case LogLevel::Error:
		return "\033[41m";	// red
	case LogLevel::Fatal:
		return "\033[45m";	// purple
	default:
		std::unreachable();
		return "NOT DEFINE COLOR";
	}
}

std::string_view fastlog::detail::reset_format() {
	return "\033[0m";
}
