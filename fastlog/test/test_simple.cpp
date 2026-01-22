#include "fastlog.hpp"
#include <iostream>
#include <thread>

int main() {
	std::cout << "Testing simple logging..." << std::endl;

	auto& logger = fastlog::file::make_logger("test_logger", "./logs/test/");

	for(int i = 0; i < 100; ++i) {
		logger.info("Test log message {}", i);
	}

	std::cout << "Logged 100 messages, sleeping for 2 seconds to allow processing..." << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(2));

	std::cout << "Done!" << std::endl;
	return 0;
}
