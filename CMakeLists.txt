cmake_minimum_required(VERSION 3.2)
project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

set(CMAKE_CXX_STANDARD 14)

#find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(ip_filter ip_filter.cpp)

#add_library(ip_filter_lib ip_filter.cpp ip_filter.h)
#add_executable(test_functional test_functional.cpp)

set_target_properties(ip_filter PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )


#set_target_properties(test_functional PROPERTIES
#        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
#        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
#        )
#
#target_link_libraries(test_functional ${Boost_LIBRARIES} ip_filter_lib)
#
#enable_testing()
#
#add_test(test_functional test_functional)

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT artbataev@gmail.com)

include(CPack)
