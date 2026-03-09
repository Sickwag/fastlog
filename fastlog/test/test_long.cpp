#include "fastlog.hpp"
#include <chrono>
#include <iostream>
#include <thread>

int main() {
	std::cout << "Testing long logging..." << std::endl;

	// 创建文件日志器
	auto& logger1 = fastlog::file::make_logger("long_test1", "./logs/long_test/");
	auto& logger2 = fastlog::file::make_logger("long_test2", "./logs/long_test/");

	// 记录大量日志
	for(int i = 0; i < 10000; ++i) {
		logger1.info("Long test log message {} with some content", i);
		logger2.info("Another log message {} with different content", i);
		if(i % 1000 == 0) {
			std::cout << "Logged " << i << " messages..." << std::endl;
		}
	}

	std::cout << "All messages logged, sleeping for 5 seconds to allow processing..." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));

	std::cout << "Done!" << std::endl;
	return 0;
}
