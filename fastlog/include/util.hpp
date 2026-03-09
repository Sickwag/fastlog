#pragma once
#include <cstdint>
#include <optional>
#include <string>
// 平台检测宏
#ifdef _WIN32
#	include <windows.h>
#elif defined(__APPLE__) || defined(__linux__)
#	include <pthread.h>
#	include <unistd.h>
#endif

namespace fastlog::detail::util {
class noncopyable {
  public:
	noncopyable(const noncopyable&)			   = delete;
	noncopyable& operator=(const noncopyable&) = delete;

  protected:
	noncopyable()  = default;
	~noncopyable() = default;
};

template <typename T>
class Singleton {
  private:
	Singleton()	 = delete;
	~Singleton() = delete;

  public:
	[[nodiscard]] static T& instance() {
		static T instance;
		return instance;
	}
};
std::optional<std::string> get_current_time_tostring(bool is_repeat = true);
std::uint32_t			   get_current_pid();
}  // namespace fastlog::detail::util
