add_executable(test_simple
	${CMAKE_CURRENT_SOURCE_DIR}/test_simple.cpp
	${SRC_LIST}
)

add_executable(test_long
	${CMAKE_CURRENT_SOURCE_DIR}/test_long.cpp
	${SRC_LIST}
)

target_include_directories(test_simple PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/../include
)

target_include_directories(test_long PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/../include
)
