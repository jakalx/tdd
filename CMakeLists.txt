cmake_minimum_required(VERSION 3.17)
project(cmake_conan_gtest)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

# Instruct CMake to run qt tools automatically when needed
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

include(cmake/conan.cmake)
conan_cmake_run(REQUIRES
        gtest/1.10.0
        fmt/7.1.3
        BASIC_SETUP CMAKE_TARGETS
        BUILD missing)

find_package(Qt5 COMPONENTS Core Gui Widgets Test REQUIRED)

add_executable(test
  tiere_test.cpp schwein.cpp
  calc_test.cpp
  people_test.cpp
  people/Person.cpp
  people/personen_service_exception.cpp
  people/person_service_impl.cpp
  fake/myservice_using_dependency_test.cpp
  )
target_link_libraries(test PUBLIC CONAN_PKG::gtest)
target_include_directories(test PRIVATE people)
add_test (NAME test COMMAND test)

# NB: export Qt5_DIR to MSVC installation
# NB: export PATH to include Qt5 bin installation
add_executable (gui
  gui/EuroToDollarCalculatorApplication.cpp
  gui/main.cpp
  )
target_link_libraries(gui Qt5::Core Qt5::Gui Qt5::Widgets)

add_executable (test_gui
  gui/EuroToDollarCalculatorApplication.cpp
  gui/EuroToDollarCalculatorApplicationTest.cpp
  gui/test_euro_to_dollar_presenter.cpp
  )
target_link_libraries(test_gui Qt5::Core Qt5::Gui Qt5::Widgets Qt5::Test CONAN_PKG::gtest CONAN_PKG::fmt)
add_test (NAME test_gui COMMAND test_gui)
