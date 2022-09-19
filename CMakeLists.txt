cmake_minimum_required(VERSION 3.24)

set(Boost_NO_WARN_NEW_VERSIONS ON)

project(
  EcosystemOfServices
)

find_package(
  cpprestsdk
    CONFIG REQUIRED
)

add_subdirectory(InvestorService)

# add_subdirectory(ApiGateway)

# add_subdirectory(Authentication)
