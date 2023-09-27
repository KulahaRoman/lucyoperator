cmake_minimum_required(VERSION 3.15)

project(lucyoperator-test)

set(LUCYOPERATOR_TEST_SRC	main.cpp
)

add_executable(${PROJECT_NAME} ${LUCYOPERATOR_TEST_SRC})

target_link_libraries(${PROJECT_NAME} PUBLIC GTest::gtest)
target_include_directories(${PROJECT_NAME} PRIVATE "../src/")

config_compiler_and_linker()

if(MSVC)
	target_compile_options(${PROJECT_NAME} PRIVATE "/EHsc")
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION ${LUCYOPERATOR_INSTALL_BIN})