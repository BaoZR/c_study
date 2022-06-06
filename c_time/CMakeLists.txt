cmake_minimum_required(VERSION 3.14)

project(c_time
  VERSION 1.0
  LANGUAGES CXX)

set(SOURCES
	main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})