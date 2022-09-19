cmake_minimum_required(VERSION 3.24)

project(
  InvestorService
    VERSION 1.0.0
    LANGUAGES C CXX
)

add_executable(
  ${PROJECT_NAME}
    Includes/Core/BaseController.hpp
    Includes/Controllers/InvestorController.hpp

    Sources/Main.cpp
    Sources/Core/BaseController.cpp
    Sources/Controllers/InvestorController.cpp
)

target_link_libraries(
  ${PROJECT_NAME}
    PRIVATE
      cpprestsdk::cpprest
)

target_include_directories(
  ${PROJECT_NAME}
    PUBLIC
      ${CMAKE_CURRENT_SOURCE_DIR}/
)

target_compile_features(
  ${PROJECT_NAME}
    PUBLIC
      cxx_std_20
)