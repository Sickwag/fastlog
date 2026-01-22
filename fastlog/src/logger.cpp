#include "logger.hpp"
#include <iostream>
#include <iterator>

fastlog::detail::FileLogger::FileLogger(fs::path log_file_path)
	: log_fs_(log_file_path)
	, current_buffer_(std::make_unique<FileLogBuf>())
	, work_thread_{ &FileLogger::work, this } {}

fastlog::detail::FileLogger::~FileLogger() {
	running_ = false;
	cv_.notify_one();
	if(work_thread_.joinable()) {
		work_thread_.join();
	}
}

void fastlog::detail::FileLogger::work() {
	constexpr std::size_t max_buffer_list_size = 15;
	while(running_) {
		std::unique_lock<std::mutex> lock(mutex_);
		cv_.wait_for(lock, std::chrono::milliseconds(3), [this]() -> bool { return !this->full_buffers_.empty(); });
		if(full_buffers_.size() > max_buffer_list_size) {
			std::cerr << std::format("drop log messages {} larger buffers\n", full_buffers_.size() - 2);
			full_buffers_.resize(2);
		}
		for(auto& buffer : full_buffers_) {
			log_fs_.write(buffer->data(), buffer->size());
			buffer->reset();
		}

		// extra protection
		if(full_buffers_.size() > 2) {
			full_buffers_.resize(2);
		}
		if(!running_ && !current_buffer_->empty()) {
			log_fs_.write(current_buffer_->data(), current_buffer_->size());
			log_fs_.flush();
		}
		log_fs_.flush();
		empty_buffers_.splice(empty_buffers_.end(), full_buffers_);
	}
}
