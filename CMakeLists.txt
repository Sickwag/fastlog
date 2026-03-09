cmake_minimum_required (VERSION 3.8)
project ("FastLogLearning")

if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/out" CACHE PATH "Install prefix" FORCE)
endif()

add_subdirectory ("fastlog")

set_target_properties(fastlog PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
)

# 为库创建pkg-config文件（可选）
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/fastlog.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/fastlog.pc"
    @ONLY
)
