# ⚡ FastLog

<div align="center">

🚀 一个现代化的 C++ 快速异步日志记录器

[![C++](https://img.shields.io/badge/C++-20-blue?logo=cplusplus)](https://isocpp.org/)
[![License](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Platform](https://img.shields.io/badge/Platform-Windows%20%7C%20Linux%20%7C%20macOS-lightgrey)](README.md)

</div>

---

## 📖 目录

- [简介](#-简介)
- [特性](#-特性)
- [快速开始](#-快速开始)
- [使用示例](#-使用示例)
- [API 参考](#-api-参考)
- [构建与安装](#-构建与安装)
- [性能特点](#-性能特点)
- [项目结构](#-项目结构)
- [贡献](#-贡献)
- [许可证](#-许可证)

---

## 📌 简介

**FastLog** 是一个高性能、线程安全的 C++ 日志库，采用现代 C++20 标准编写。它提供了简洁易用的 API 接口，支持控制台和文件两种输出方式，特别适合需要高性能日志记录的应用场景。

### 为什么选择 FastLog？

- ✨ **现代 C++20** - 利用最新语言特性，代码简洁优雅
- 🚀 **高性能** - 异步写入，双缓冲机制，最小化 I/O 阻塞
- 🔒 **线程安全** - 多线程环境下安全使用
- 🎨 **易用性** - 类似 `std::format` 的格式化语法
- 📦 **轻量级** - 头文件为主，集成简单

---

## ✨ 特性

| 特性 | 描述 |
|------|------|
| 🎯 **多日志级别** | Trace / Debug / Info / Warn / Error / Fatal |
| 🖥️ **控制台输出** | 彩色日志输出，快速调试 |
| 📁 **文件输出** | 异步写入，自动轮转，支持多日志文件 |
| 🔀 **线程安全** | 锁机制 + 条件变量，多线程安全 |
| 📊 **双缓冲机制** | 高效内存管理，减少内存分配 |
| 🛠️ **C++20 format** | 类型安全的格式化输出 |
| 📍 **源码位置** | 自动捕获文件、行号信息 |
| 🌐 **跨平台** | Windows / Linux / macOS 支持 |

---

## 🚀 快速开始

### 最小化示例

```cpp
#include <fastlog.hpp>

int main() {
    // 控制台日志
    fastlog::console.info("Hello, World!");
    fastlog::console.error("Error occurred at line {}", 42);

    // 文件日志
    auto& logger = fastlog::file::make_logger("my_logger", "/path/to/logs/");
    logger->debug("Debug message with value: {}", 123);

    return 0;
}
```

### 输出效果

```
2026-03-09 10:30:45 [INFO] 12345 main.cpp:10 Hello, World!
2026-03-09 10:30:45 [ERROR] 12345 main.cpp:11 Error occurred at line 42
```

---

## 📚 使用示例

### 1️⃣ 控制台日志

```cpp
#include <fastlog.hpp>

int main() {
    // 设置日志级别
    fastlog::set_console_log_level(fastlog::LogLevel::Debug);

    // 各种日志级别
    fastlog::console.trace("Trace message");
    fastlog::console.debug("Debug message");
    fastlog::console.info("Info message");
    fastlog::console.warn("Warning message");
    fastlog::console.error("Error message");
    fastlog::console.fatal("Fatal message");

    // 格式化输出（支持任意类型）
    int value = 42;
    std::string name = "FastLog";
    fastlog::console.info("Name: {}, Value: {}", name, value);

    return 0;
}
```

### 2️⃣ 文件日志

```cpp
#include <fastlog.hpp>

int main() {
    // 创建文件日志记录器
    auto& logger1 = fastlog::file::make_logger("app_log", "./logs/app/");
    auto& logger2 = fastlog::file::make_logger("error_log", "./logs/error/");

    // 异步写入日志
    logger1->info("Application started");
    logger2->error("Something went wrong: {}", "error details");

    // 获取已存在的日志记录器
    auto* existing_logger = fastlog::file::get_logger("app_log");
    if (existing_logger) {
        existing_logger->debug("Debug from existing logger");
    }

    // 删除日志记录器
    fastlog::file::delete_logger("error_log");

    return 0;
}
```

### 3️⃣ 多线程日志

```cpp
#include <fastlog.hpp>
#include <thread>
#include <vector>

void worker(int id) {
    auto& logger = fastlog::file::get_logger("worker_log");
    for (int i = 0; i < 100; ++i) {
        logger->info("Worker {} processing item {}", id, i);
    }
}

int main() {
    auto& logger = fastlog::file::make_logger("worker_log", "./logs/");

    std::vector<std::thread> threads;
    for (int i = 0; i < 4; ++i) {
        threads.emplace_back(worker, i);
    }

    for (auto& t : threads) {
        t.join();
    }

    return 0;
}
```

---

## 📖 API 参考


### 控制台日志 API

| 函数 | 描述 |
|------|------|
| `fastlog::console` | 全局控制台日志对象 |
| `fastlog::set_console_log_level(level)` | 设置控制台日志级别 |

### 文件日志 API

| 函数 | 描述 |
|------|------|
| `fastlog::file::make_logger(name, path)` | 创建文件日志记录器 |
| `fastlog::file::get_logger(name)` | 获取已存在的日志记录器 |
| `fastlog::file::delete_logger(name)` | 删除日志记录器 |
| `fastlog::file::file_logger_manager` | 全局日志管理器单例 |

### 日志方法

所有日志器支持以下方法：

```cpp
logger.trace(format, args...);   // 追踪日志
logger.debug(format, args...);   // 调试日志
logger.info(format, args...);    // 信息日志
logger.warn(format, args...);    // 警告日志
logger.error(format, args...);   // 错误日志
logger.fatal(format, args...);   // 致命日志
logger.set_level(level);         // 设置日志级别
```

---

## 🛠️ 构建与安装

### 系统要求

- **编译器**: GCC 13+ / Clang 16+ / MSVC 2022+
- **CMake**: 3.8+
- **C++ 标准**: C++20

### 克隆项目

```bash
git clone https://github.com/yourusername/FastLogLearning.git
cd FastLogLearning
```

### 使用 CMake 构建

```bash
# 创建构建目录
mkdir build && cd build

# 配置项目
cmake ..

# 构建
cmake --build .

# 安装
cmake --install . --prefix ../out
```

### Windows 用户

可以使用提供的批处理脚本：

```batch
build_and_install.bat
```

### 使用 pkg-config (可选)

```bash
export PKG_CONFIG_PATH=/path/to/out/lib/pkgconfig
g++ -o myapp myapp.cpp $(pkg-config --cflags --libs fastlog)
```

---

## ⚡ 性能特点

### 异步写入机制

FastLog 采用生产者 - 消费者模型实现异步日志写入：

```
┌─────────────┐     ┌──────────────┐     ┌─────────────┐
│   应用线程   │────▶│  双缓冲队列  │────▶│  后台写入线程 │
│  (生产者)   │     │  (无锁缓冲)  │     │   (消费者)   │
└─────────────┘     └──────────────┘     └─────────────┘
```

### 双缓冲设计

- **缓冲区大小**: 默认 4MB 可配置
- **内存效率**: 复用缓冲区，减少内存分配
- **批量写入**: 累积日志后批量写入磁盘，减少 I/O 次数

### 日志格式

```
时间戳 [日志级别] 线程 ID  文件名：行号 日志内容
```

示例：
```
2026-03-09 10:30:45 [INFO] 12345  main.cpp:42 Application started successfully
```

---

## 📁 项目结构

```
FastLogLearning/
├── CMakeLists.txt          # 顶层 CMake 配置
├── README.md               # 项目文档
├── build_and_install.bat   # Windows 构建脚本
├── fastlog.pc.in           # pkg-config 模板
│
└── fastlog/
    ├── CMakeLists.txt      # 库 CMake 配置
    │
    ├── include/            # 头文件目录
    │   ├── fastlog.hpp     # 主入口头文件
    │   ├── logger.hpp      # 日志器核心实现
    │   ├── logbuffer.hpp   # 双缓冲实现
    │   ├── logfstream.hpp  # 文件流封装
    │   ├── loglevel.hpp    # 日志级别定义
    │   ├── manager.hpp     # 日志管理器
    │   └── util.hpp        # 工具函数
    │
    ├── src/                # 源文件目录
    │   ├── logger.cpp      # 日志器实现
    │   ├── logfstream.cpp  # 文件流实现
    │   ├── loglevel.cpp    # 日志级别实现
    │   └── util.cpp        # 工具函数实现
    │
    ├── example/            # 示例代码
    │   └── example.cpp     # 使用示例
    │
    └── test/               # 测试代码
```

---

## 🤝 贡献

欢迎贡献代码、报告问题或提出建议！

### 贡献流程

1. Fork 本仓库
2. 创建特性分支 (`git checkout -b feature/AmazingFeature`)
3. 提交更改 (`git commit -m 'Add some AmazingFeature'`)
4. 推送到分支 (`git push origin feature/AmazingFeature`)
5. 开启 Pull Request

### 开发指南

- 遵循现有的代码风格
- 添加必要的注释
- 确保代码通过编译和测试

---

## 🙏 致谢

感谢所有为这个项目做出贡献的开发者！

---

<div align="center">

**Made with ❤️ using C++20**

如果这个项目对你有帮助，请给一个 ⭐️ Star！

</div>
