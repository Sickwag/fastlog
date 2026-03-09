#pragma once
#include <string_view>

namespace fastlog {
enum class LogLevel { Trace, Debug, Info, Warn, Error, Fatal };
}  // namespace fastlog

namespace fastlog::detail {
class LogLevelWrapper {
  public:
	LogLevelWrapper(LogLevel level);
	std::string_view to_string();
	std::string_view to_color();

  private:
	LogLevel level_;
};

[[nodiscard]] std::string_view reset_format();
}  // namespace fastlog::detail
