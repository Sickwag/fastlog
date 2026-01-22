#include "fastlog.hpp"
#include <iostream>
#include <vector>

namespace fastlog::test {

std::vector<int> vec = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
void			 file_log_func1() {
	long long count = 0;
	while(count < 1000) {
		fastlog::file::get_logger("file_log1")->info("hello world log1,count : {}, vec :{}", count++, vec[count % 10]);
	}
}

void file_log_func2() {
	long long count = 0;
	while(count < 1000) {
		fastlog::file::get_logger("file_log2")->info("hello world log2,count : {}, vec :{}", count++, vec[count % 10]);
	}
}

void file_log_test() {
#ifdef FILE_LOG_PATH1
	const auto& file_logger1 = fastlog::file::make_logger("file_log1", FILE_LOG_PATH1);
	const auto& file_logger2 = fastlog::file::make_logger("file_log2", FILE_LOG_PATH2);
#else
	std::cout << "test log file output to custom log path\n";
	constexpr char* log_file_path1 = "D:/Code Files/vsstudio/FastLogLearning/logs/log1/";
	constexpr char* log_file_path2 = "D:/Code Files/vsstudio/FastLogLearning/logs/log2/";
	const auto&		file_logger1   = fastlog::file::make_logger("file_log1", log_file_path1);
	const auto&		file_logger2   = fastlog::file::make_logger("file_log2", log_file_path2);
#endif
	std::thread t1(file_log_func1);
	std::thread t2(file_log_func2);
	t1.join();
	t2.join();
}

void console_log_test() {
	fastlog::console.trace("hello world");
	fastlog::console.debug("hello world");
	fastlog::console.info("hello world");
	fastlog::console.warn("hello world");
	fastlog::console.error("hello world");
	fastlog::console.fatal("hello world");
}

void test(){
	console_log_test();
	fastlog::console.info("file log write start .............");
	file_log_test();
	fastlog::console.info("file log write finish .............");
}
}  // namespace fastlog::test

int main(){
	fastlog::test::test();
	return 0;
}
