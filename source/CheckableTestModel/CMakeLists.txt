cmake_minimum_required(VERSION 3.6)

project(CheckableTestModel LANGUAGES CXX)

find_package(Qt5Core REQUIRED)

add_library(${PROJECT_NAME}
        CheckableTestModel.cpp
)

set_target_properties(${PROJECT_NAME}
	PROPERTIES CXX_STANDARD 14
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(${PROJECT_NAME}
	PUBLIC
		CheckableItem
		CheckableTest
	PRIVATE
		Qt5::Core
)
