# CMakeList.txt: 顶层 CMake 项目文件，在此处执行全局配置
# 并包含子项目。
#
cmake_minimum_required (VERSION 3.8)

# 如果支持，请为 MSVC 编译器启用热重载。
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("FastLogLearning")

# 设置默认安装前缀
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/out" CACHE PATH "Install prefix" FORCE)
endif()

# 包含子项目。
add_subdirectory ("fastlog")

# 设置包配置
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
