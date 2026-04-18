# 已知问题

## 编译期参数类型验证严格导致可读性降低
调用`fastlog::console.debug(const char* str, Args... args)`时，由于
```cpp
template <typename... Args>
struct basic_format_string_wrapper {
	template <typename T>
		requires std::convertible_to<T, std::string_view>
	consteval basic_format_string_wrapper(const T&			   s,
										  std::source_location loc = std::source_location::current())
		: fmt_(s)
		, loc_(loc) {}

	std::format_string<Args...> fmt_;
	std::source_location		loc_;
};
```
会对Args进行类型验证，consteval 要求**整个表达式（返回值&所有参数的类型）必须是编译期已知的**，这就导致引入qt项目中是对QString类型在作为str（第一个参数时）需要调用`QString::constData()`或者使用`fastlog::console.debug("{}"， QStringValue)`

## 没有指针特化
`std::format`只为void* 和nullptr 做了特化，对于自定义类型指针不支持，直接作为args第二个及以后的参数会导致报错