cmake_minimum_required(VERSION 3.15)

project(project-lucyoperator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(LUCYOPERATOR_INSTALL_BIN ${CMAKE_CURRENT_SOURCE_DIR}/bin)

if(UNIX)
  set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++ -static")
elseif(WIN32)
  string(REGEX REPLACE "(/MD|/MDd)" "" CMAKE_C_FLAGS "${CMAKE_C_FLAGS}")
  string(REGEX REPLACE "(/MD|/MDd)" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

if(NOT TARGET lucycore)
	add_subdirectory(libs/lucycore)
endif()
if(NOT TARGET lucynet)
	add_subdirectory(libs/lucynet)
endif()

if(NOT TARGET lucyoperator)
	add_subdirectory(src)
	add_subdirectory(test)
endif()