#include "logfstream.hpp"
#include "util.hpp"
#include <exception>
#include <format>

namespace fs = std::filesystem;

fastlog::detail::logfstream::logfstream(fs::path log_file)
	: log_file_(log_file) {
	if(log_file_.has_parent_path()) {
		const auto log_dir = log_file_.parent_path();
		if(!fs::exists(log_dir)) {
			fs::create_directories(log_dir);
		}
	}

	this->create_log();
	file_stream_.rdbuf()->pubsetbuf(buffer_.data(), buffer_.size());
}

fastlog::detail::logfstream::~logfstream() { file_stream_.close(); }

void fastlog::detail::logfstream::flush() { file_stream_.flush(); }

void fastlog::detail::logfstream::set_maxsize(std::size_t maxsize) { this->file_maxsize_ = maxsize; }

void fastlog::detail::logfstream::write(const char* data, std::size_t size) {
	file_stream_.write(data, size);
	current_file_size_ += size;
	if(current_file_size_ > file_maxsize_) {
		create_log();
	}
}

void fastlog::detail::logfstream::create_log() {
	const auto time_str = util::get_current_time_tostring();
	if(time_str.has_value()) {
		fs::path log_file_path = log_file_;
		// generate a default filename when it's a dir
		if(!log_file_path.has_filename()) {
			log_file_path /= "log-" + time_str.value();
		} else {
			// add timestamp when path contains filename
			log_file_path += "-" + time_str.value();
		}
		current_file_size_ = 0;
		if(file_stream_.is_open()) {
			file_stream_.close();
		}
		file_stream_.open(log_file_path, std::ios::out);
		if(!file_stream_.is_open()) {
			throw std::runtime_error("create log file failed");
		}
	}
}
