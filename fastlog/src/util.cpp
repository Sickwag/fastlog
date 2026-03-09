#include "util.hpp"
#include <array>
#include <chrono>
#include <ctime>

std::optional<std::string> fastlog::detail::util::get_current_time_tostring(bool is_repeat) {
	static thread_local std::array<char, 64> buf{};
	static thread_local std::chrono::seconds last_second{ 0 };
	const auto								 now			= std::chrono::system_clock::now();
	const auto								 time_t_now		= std::chrono::system_clock::to_time_t(now);
	const auto								 current_second = std::chrono::seconds(time_t_now);
	if(is_repeat || (current_second.count() != last_second.count())) {
		std::tm* local_tm = std::localtime(&time_t_now);
#ifdef _WIN32
		std::strftime(buf.data(), buf.size(), "%Y-%m-%d-%H-%M-%S", local_tm);
#else
		std::strftime(buf.data(), buf.size(), "%Y-%m-%d-%H:%M:%S", local_tm);
#endif
		last_second = current_second;
		return { buf.data() };
	}
	return std::nullopt;
}

std::uint32_t fastlog::detail::util::get_current_pid() {
#ifdef _WIN32
	return static_cast<std::uint32_t>(GetCurrentProcessId());
#elif defined(__APPLE__) || defined(__linux__)
	return static_cast<std::uint32_t>(getpid());
#else
	return 0;
#endif
}
