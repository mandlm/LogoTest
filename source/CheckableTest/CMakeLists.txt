cmake_minimum_required(VERSION 3.6)

project(CheckableTest LANGUAGES CXX)

find_package(Qt5Core REQUIRED)

add_library(${PROJECT_NAME}
        CheckableTest.cpp
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES CXX_STANDARD 14
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
	PRIVATE
		CheckableItem
		Qt5::Core
)
