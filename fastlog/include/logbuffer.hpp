#pragma once
#include <algorithm>
#include <array>
#include <cassert>
#include <string>


namespace fastlog::detail {
template <size_t SIZE>
class FileLogBuffer {
  public:
	FileLogBuffer() noexcept
		: cur_(data_.begin()) {};

	void write(const std::string& str) noexcept {
		assert(writeable() > str.size());
		std::copy(str.begin(), str.end(), cur_);
		cur_ += str.size();
	}

	[[nodiscard]] size_t size() noexcept {
		return std::distance(data_.begin(), cur_);
	}

	[[nodiscard]] size_t capacity() noexcept {
		return SIZE;
	}

	[[nodiscard]] size_t writeable() noexcept {
		return capacity() - size();
	}

	[[nodiscard]] bool empty() noexcept {
		return data_.begin() == cur_;
	}

	void reset() noexcept {
		cur_ = data_.begin();
	}

	const char* data() noexcept {
		return data_.data();
	}

  private:
	std::array<char, SIZE>			 data_{};
	std::array<char, SIZE>::iterator cur_{};
};
}  // namespace fastlog::detail
