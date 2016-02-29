cmake_minimum_required(VERSION 3.0)
project(fmo CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release CACHE STRING "" FORCE)
endif(NOT CMAKE_BUILD_TYPE)

if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/products/${CMAKE_BUILD_TYPE}/bin")
endif(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/Modules")

set(CMAKE_CXX_FLAGS "-std=c++14 -pedantic -Wall -Wextra -Werror")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g3 -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  string(APPEND CMAKE_CXX_FLAGS_DEBUG " -fsanitize=address,undefined")
endif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")

option(CPA_BUILD_UNIT_TESTS "Build CPA unit tests" ON)
if(CPA_BUILD_UNIT_TESTS)
  option(CPA_SKIP_RUN_UNIT_TESTS "Skip running each unit test after its built" OFF)
  if(CPA_SKIP_RUN_UNIT_TESTS)
    set(CUTE_SKIP_RUN_UNIT_TESTS ON)
  endif(CPA_SKIP_RUN_UNIT_TESTS)

  include(CUTE)
  include_directories(SYSTEM "third_party/cute/include")
  include_directories(SYSTEM "include")
  add_subdirectory(test)
endif(CPA_BUILD_UNIT_TESTS)

option(CPA_BUILD_DOCUMENTATION "Build the API documentation" OFF)
if(CPA_BUILD_DOCUMENTATION)
  find_package(Doxygen REQUIRED)
  configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
  add_custom_target(doc ALL ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    COMMENT "Generating API documentation" VERBATIM)
endif(CPA_BUILD_DOCUMENTATION)
