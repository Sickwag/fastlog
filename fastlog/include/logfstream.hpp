#pragma once

#include <array>
#include <ctime>
#include <filesystem>
#include <fstream>

namespace fastlog::detail {
class logfstream {
  public:
	logfstream(std::filesystem::path filepath);
	~logfstream();
	void flush();
	void set_maxsize(std::size_t maxsize);
	void write(const char* content, std::size_t size);

  private:
	void create_log();

	static inline constexpr std::size_t BUFFER_SIZE = 1024;

	std::ofstream				  file_stream_;
	std::filesystem::path		  log_file_;
	std::size_t					  file_maxsize_{ 1024 * 1024 * 100 };
	std::array<char, BUFFER_SIZE> buffer_;
	std::size_t					  current_file_size_{ 0 };
	std::filesystem::path		  log_path_;
};
}  // namespace fastlog::detail