cmake_minimum_required(VERSION 3.17)
project(cmake_conan_gtest)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
include(cmake/conan.cmake)
conan_cmake_run(REQUIRES
        gtest/1.10.0
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing)

add_library (fibonacci Fibonacci.cpp)
add_executable(test
  tiere_test.cpp schwein.cpp
  )
target_link_libraries(test PUBLIC CONAN_PKG::gtest)
add_test (NAME test COMMAND test)
