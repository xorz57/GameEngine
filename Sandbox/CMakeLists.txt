cmake_minimum_required(VERSION 3.24)

project(Sandbox)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenGL REQUIRED)
find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)

if(WIN32)
	add_executable(${PROJECT_NAME} WIN32 src/Main.cpp src/Application.cpp)
else()
	add_executable(${PROJECT_NAME} src/Main.cpp src/Application.cpp)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
