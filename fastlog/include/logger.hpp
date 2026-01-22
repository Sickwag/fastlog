#pragma once

#include "logbuffer.hpp"
#include "logfstream.hpp"
#include "loglevel.hpp"
#include "util.hpp"
#include <atomic>
#include <condition_variable>
#include <format>
#include <iostream>
#include <list>
#include <source_location>
#include <thread>

namespace fs = std::filesystem;

namespace fastlog::detail {
struct logrecord_t {
	const char* datetime;
	uint64_t	thread_id;
	const char* file_name;
	size_t		line;
	std::string log;
};

template <typename... Args>
struct basic_format_string_wrapper {
	template <typename T>
		requires std::convertible_to<T, std::string_view>
	consteval basic_format_string_wrapper(const T& s, std::source_location loc = std::source_location::current())
		: fmt_(s)
		, loc_(loc) {}

	std::format_string<Args...> fmt_;
	std::source_location		loc_;
};

template <typename... Args>
using format_string_wrapper = basic_format_string_wrapper<std::type_identity_t<Args>...>;

template <typename DerviceLogger>
class BaseLogger : util::noncopyable {
  public:
	void set_level(LogLevel level) {
		level_ = level;
	};

	[[nodiscard]] LogLevel level() const {
		return level_;
	};

	template <typename... Args>
	void trace(format_string_wrapper<Args...> fmt, Args&&... args) {
		format<LogLevel::Trace>(fmt, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void debug(format_string_wrapper<Args...> fmt, Args&&... args) {
		format<LogLevel::Debug>(fmt, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void info(format_string_wrapper<Args...> fmt, Args&&... args) {
		format<LogLevel::Info>(fmt, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void warn(format_string_wrapper<Args...> fmt, Args&&... args) {
		format<LogLevel::Warn>(fmt, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void error(format_string_wrapper<Args...> fmt, Args&&... args) {
		format<LogLevel::Error>(fmt, std::forward<Args>(args)...);
	}

	template <typename... Args>
	void fatal(format_string_wrapper<Args...> fmt, Args&&... args) {
		format<LogLevel::Fatal>(fmt, std::forward<Args>(args)...);
	}

  private:
	template <LogLevel LEVEL, typename... Args>
	void format(format_string_wrapper<Args...> fmt_w, Args&&... args) {
		if(level_ > LEVEL) {
			return;
		}
		std::string time_str;
		const auto	res = util::get_current_time_tostring();
		if(res.has_value()) {
			time_str = std::move(res.value());
		}
		static_cast<DerviceLogger*>(this)->template log<LEVEL>(
			logrecord_t{ .datetime	= time_str.c_str(),
						 .thread_id = util::get_current_pid(),
						 .file_name = fmt_w.loc_.file_name(),
						 .line		= fmt_w.loc_.line(),
						 .log		= std::format(fmt_w.fmt_, std::forward<Args>(args)...) });
	}

	LogLevel level_;
};

class ConsoleLogger : public BaseLogger<ConsoleLogger> {
  public:
	template <LogLevel level>
	void log(const logrecord_t& record) {
		LogLevelWrapper level_wrapper(level);
		// current g++ 14.2.0 incomplete support for print leads to link error
		// std::print("{} [{}{}{}] {} {}:{} {}\n",
		// 		   record.datetime,
		// 		   level_wrapper.to_color(),
		// 		   level_wrapper.to_string(),
		// 		   reset_format(),
		// 		   record.thread_id,
		// 		   record.file_name,
		// 		   record.line,
		// 		   record.log);
		std::string output = std::format("{} [{}{}{}] {} {}:{} {}\n",
									   record.datetime,
									   level_wrapper.to_color(),
									   level_wrapper.to_string(),
									   reset_format(),
									   record.thread_id,
									   record.file_name,
									   record.line,
									   record.log);
		std::cout << output;
	}
};

class FileLogger : public BaseLogger<FileLogger> {
  public:
	FileLogger(fs::path log_file_path);
	~FileLogger();

	template <LogLevel Level>
	void log(const logrecord_t& record) {
		if(!running_) {
			return;
		}
		LogLevelWrapper				level_wrapper(Level);
		std::string					msg{ std::format("{} {} {}  {}:{} {}\n",
									 record.datetime,
									 level_wrapper.to_string(),
									 record.thread_id,
									 record.file_name,
									 record.line,
									 record.log) };
		std::lock_guard<std::mutex> lock(mutex_);
		if(current_buffer_->writeable() > msg.size()) {
			current_buffer_->write(msg);
		} else {
			full_buffers_.push_back(std::move(current_buffer_));
			if(!empty_buffers_.empty()) {
				current_buffer_ = std::move(empty_buffers_.front());
				empty_buffers_.pop_front();
			} else {
				current_buffer_ = std::make_unique<FileLogBuf>();
			}
			current_buffer_->write(msg);
			cv_.notify_one();
		}
	}

  private:
	using FileLogBuf = FileLogBuffer<4000 * 1024>;
	using logbuf_ptr = std::unique_ptr<FileLogBuf>;

	void work();

	logfstream				log_fs_;
	logbuf_ptr				current_buffer_;
	std::list<logbuf_ptr>	empty_buffers_{};
	std::list<logbuf_ptr>	full_buffers_{};
	std::mutex				mutex_;
	std::condition_variable cv_{};
	std::thread				work_thread_{};
	std::atomic<bool>		running_{ true };
};
}  // namespace fastlog::detail
