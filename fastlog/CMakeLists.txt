project(fastlog)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出路径
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../out/bin/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../out/bin)

# 收集源文件
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

# 创建静态库
add_library(fastlog STATIC ${SRC_LIST})

# 设置库的输出路径
set_target_properties(fastlog PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH}
    LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH}
)

# 设置头文件目录
target_include_directories(fastlog PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 添加预定义宏
add_definitions(-DFILE_LOG_PATH1="${PROJECT_SOURCE_DIR}/../logs/log1/")
add_definitions(-DFILE_LOG_PATH2="${PROJECT_SOURCE_DIR}/../logs/log2/")

# 创建示例程序（链接静态库）
add_executable(example
    ${CMAKE_CURRENT_SOURCE_DIR}/example/example.cpp
)

target_link_libraries(example PRIVATE fastlog)
target_include_directories(example PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 安装规则
install(TARGETS fastlog
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
)

install(TARGETS example
    RUNTIME DESTINATION bin
)

# 安装pkg-config文件
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/../fastlog.pc.in
    ${CMAKE_CURRENT_BINARY_DIR}/fastlog.pc
    @ONLY
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/fastlog.pc
    DESTINATION lib/pkgconfig
)
