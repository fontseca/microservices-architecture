cmake_minimum_required(VERSION 3.24)

project(
  ApiGatewayService 
    VERSION 1.0.0
    LANGUAGES C CXX
)

add_executable(
  ${PROJECT_NAME}
    Includes/Core/BaseController.hpp
    Includes/Controllers/ApiGatewayController.hpp

    Sources/Core/BaseController.cpp
    Sources/Controllers/ApiGatewayController.cpp
    Sources/Main.cpp
)

target_link_libraries(
  ${PROJECT_NAME}
    PRIVATE
      cpprestsdk::cpprest
      mongo::bsoncxx_static
      mongo::mongocxx_static
      cpp-jwt::cpp-jwt
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