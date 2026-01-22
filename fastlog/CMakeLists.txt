set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/out/bin)
aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/src SRC_LIST)

add_executable(example
	${CMAKE_CURRENT_SOURCE_DIR}/example/example.cpp
	${SRC_LIST}
)

add_definitions(-DFILE_LOG_PATH1="${CMAKE_CURRENT_SOURCE_DIR}/logs/log1/")
add_definitions(-DFILE_LOG_PATH2="${CMAKE_CURRENT_SOURCE_DIR}/logs/log2/")

target_include_directories(example PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/include
)
