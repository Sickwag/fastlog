# FastLog Static Library Installation Guide

## Overview
FastLog is a high-performance C++ logging library that has been packaged as a static library for easy integration into other projects.

## Build and Install

### Prerequisites
- CMake 3.8 or higher
- A C++23 compatible compiler

### Building the Library

1. **Clone or navigate to the project directory**
2. **Run the build script** (on Windows):
   ```cmd
   build_and_install.bat
   ```

Or build manually:
```bash
mkdir build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Debug
cmake --build . --config Debug
cmake --install . --config Debug
```

### Installation Locations
- **Library files**: `./out/bin/lib/`
- **Header files**: `./out/bin/include/`
- **Package config**: `./out/bin/lib/pkgconfig/fastlog.pc`

## Using the Library in Your Project

### Method 1: Direct CMake Integration
Create a CMakeLists.txt for your project:
```cmake
cmake_minimum_required(VERSION 3.8)
project(MyProject)

set(CMAKE_CXX_STANDARD 23)

# Set the path to the installed library
set(FASTLOG_ROOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../out")

# Find the library
find_library(FASTLOG_LIB fastlog PATHS ${FASTLOG_ROOT_DIR}/bin/lib)
find_path(FASTLOG_INCLUDE_DIR fastlog.hpp PATHS ${FASTLOG_ROOT_DIR}/bin/include)

# Create your executable
add_executable(my_app main.cpp)

# Link the library
target_link_libraries(my_app PRIVATE ${FASTLOG_LIB})
target_include_directories(my_app PRIVATE ${FASTLOG_INCLUDE_DIR})
```

### Method 2: Using pkg-config (Linux/Unix-like systems)
```cmake
find_package(PkgConfig REQUIRED)
pkg_check_modules(FASTLOG REQUIRED fastlog)

target_link_libraries(my_app ${FASTLOG_LDFLAGS})
target_include_directories(my_app ${FASTLOG_CFLAGS})
```

### Method 3: Manual Setup
Add the following to your build system:
- Include directory: `./out/bin/include/`
- Library directory: `./out/bin/lib/`
- Link against: `libfastlog.a` (Linux/Mac) or `fastlog.lib` (Windows)

## Example Usage
```cpp
#include "fastlog.hpp"

int main() {
    // Set console log level
    fastlog::set_consolelog_level(fastlog::LogLevel::Trace);

    // Write console log
    fastlog::console.info("Hello from my application!");
    fastlog::console.warn("This is a warning");

    // Create file logger
    auto& logger = fastlog::file::make_logger("my_app_log");
    logger.info("Application started successfully");

    return 0;
}
```

## Build Configurations
- **Debug**: Use `-DCMAKE_BUILD_TYPE=Debug` for debugging
- **Release**: Use `-DCMAKE_BUILD_TYPE=Release` for optimized builds

## Troubleshooting
1. **C++23 Support**: Ensure your compiler supports C++23 features
2. **Path Issues**: Make sure the library paths are correctly set in your project
3. **Linking Errors**: Verify that all required libraries are linked properly

## Notes
- The library is compiled as a static library (.lib/.a)
- All headers are installed in the include directory
- The example program is also built and installed for testing