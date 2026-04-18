aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

add_library(fastlog STATIC ${SRC_LIST})

set_target_properties(fastlog PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH}
    LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_PATH}
)

# `PUBLIC` allows fastlog to be import with source code
target_include_directories(fastlog PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# test pre-define Macros
add_definitions(-DFILE_LOG_PATH1="${PROJECT_SOURCE_DIR}/../logs/log1/")
add_definitions(-DFILE_LOG_PATH2="${PROJECT_SOURCE_DIR}/../logs/log2/")

add_executable(example
    ${CMAKE_CURRENT_SOURCE_DIR}/example/example.cpp
)

target_link_libraries(example PRIVATE fastlog)
target_include_directories(example PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# install rules
install(TARGETS fastlog
    EXPORT fastlogTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING PATTERN "*.hpp" PATTERN "*.h"
)

install(TARGETS example
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Install export targets
install(EXPORT fastlogTargets
    FILE fastlogTargets.cmake
    NAMESPACE fastlog::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/fastlog
)
