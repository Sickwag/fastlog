cmake_minimum_required(VERSION 3.8)

project(fastlog VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/bin/lib)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/out/bin)

# Set default install prefix to install folder
if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install" CACHE PATH "Install prefix" FORCE)
endif()

# Include GNUInstallDirs for standard installation directories
include(GNUInstallDirs)

add_subdirectory("fastlog")

set_target_properties(fastlog PROPERTIES
    VERSION 1.0.0
    SOVERSION 1
)

# Create and install config files for find_package support
include(CMakePackageConfigHelpers)

# Create a version file
write_basic_package_version_file(
    "${CMAKE_CURRENT_BINARY_DIR}/fastlogConfigVersion.cmake"
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

# Configure the config file template
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/fastlogConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/fastlogConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fastlog
)

# Install config files
install(
    FILES
    "${CMAKE_CURRENT_BINARY_DIR}/fastlogConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/fastlogConfigVersion.cmake"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fastlog
)

# create pkgconfig.pc files(optional)
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/fastlog.pc.in"
    "${CMAKE_CURRENT_BINARY_DIR}/fastlog.pc"
    @ONLY
)

# Install pkg-config file
install(
    FILES "${CMAKE_CURRENT_BINARY_DIR}/fastlog.pc"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)