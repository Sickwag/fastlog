add_executable(test_simple
    ${CMAKE_CURRENT_SOURCE_DIR}/test_simple.cpp
)

add_executable(test_long
    ${CMAKE_CURRENT_SOURCE_DIR}/test_long.cpp
)

target_link_libraries(test_simple PRIVATE fastlog)
target_link_libraries(test_long PRIVATE fastlog)

target_include_directories(test_simple PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_include_directories(test_long PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../include
)

# 安装测试程序（可选）
install(TARGETS test_simple test_long
    RUNTIME DESTINATION test
)
