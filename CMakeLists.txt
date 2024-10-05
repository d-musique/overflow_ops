cmake_minimum_required(VERSION 3.24)

project(overflow_ops LANGUAGES C)
option(OVERFLOW_OPS_USE_PREBUILTS "Use prebuilt objects for MSVC" OFF)
option(OVERFLOW_OPS_TESTS "Build unit tests for this project" OFF)

if(NOT MSVC)
  add_library(overflow_ops INTERFACE)
  target_include_directories(overflow_ops INTERFACE "include")
else()
  add_library(overflow_ops STATIC)
  target_include_directories(overflow_ops PUBLIC "include")
  target_compile_definitions(overflow_ops PUBLIC "IOP_COMPILED_SEPARATE=1")
  set_target_properties(overflow_ops PROPERTIES LINKER_LANGUAGE C)

  if(WIN32 AND MSVC_C_ARCHITECTURE_ID MATCHES "^([xX]64|[xX]86[-_]?64|[aA][mM][dD]64)")
    set(OVERFLOW_OPS_TARGET_TRIPLE "x86_64-pc-windows-msvc")
  elseif(WIN32 AND MSVC_C_ARCHITECTURE_ID MATCHES "^([xX]86|[iI]?[3-6]86)")
    set(OVERFLOW_OPS_TARGET_TRIPLE "i686-pc-windows-msvc")
  elseif(WIN32 AND MSVC_C_ARCHITECTURE_ID MATCHES "^[aA][rR][mM]64[eE][cC]")
    set(OVERFLOW_OPS_TARGET_TRIPLE "arm64ec-pc-windows-msvc")
  elseif(WIN32 AND MSVC_C_ARCHITECTURE_ID MATCHES "^([aA][rR][mM]64|[aA][aA][rR][cC][hH]64)")
    set(OVERFLOW_OPS_TARGET_TRIPLE "aarch64-pc-windows-msvc")
  else()
    message(FATAL_ERROR "Cannot identify MSVC target triple")
  endif()

  if(OVERFLOW_OPS_USE_PREBUILTS)
    set(OVERFLOW_OPS_OBJECT_FILE
      "${CMAKE_CURRENT_SOURCE_DIR}/prebuilts/overflow_ops.${OVERFLOW_OPS_TARGET_TRIPLE}.obj")
    if(NOT EXISTS "${OVERFLOW_OPS_OBJECT_FILE}")
      unset(OVERFLOW_OPS_OBJECT_FILE)
    endif()
    if(OVERFLOW_OPS_OBJECT_FILE)
      message(STATUS "Prebuilt available: ${OVERFLOW_OPS_OBJECT_FILE}")
    else()
      message(STATUS "Prebuilt not available for this platform")
    endif()
  endif()

  if(NOT OVERFLOW_OPS_OBJECT_FILE)
    find_program(OVERFLOW_OPS_SEPARATE_C_COMPILER "clang" REQUIRED)
    add_custom_command(
      OUTPUT "overflow_ops${CMAKE_C_OUTPUT_EXTENSION}"
      COMMAND
        "${OVERFLOW_OPS_SEPARATE_C_COMPILER}" "-target" "${OVERFLOW_OPS_TARGET_TRIPLE}"
        "-O2" "-DIOP_COMPILED_SEPARATE=1" "-I${CMAKE_CURRENT_SOURCE_DIR}/include"
        "-c" "${CMAKE_CURRENT_SOURCE_DIR}/source/overflow_ops.c"
        "-o" "overflow_ops${CMAKE_C_OUTPUT_EXTENSION}"
      DEPENDS
        "source/overflow_ops.c"
        "include/overflow_ops.h"
        "include/overflow_ops_impl.h")
    set(OVERFLOW_OPS_OBJECT_FILE
      "${CMAKE_CURRENT_BINARY_DIR}/overflow_ops${CMAKE_C_OUTPUT_EXTENSION}")
  endif()

  target_sources(overflow_ops PRIVATE "${OVERFLOW_OPS_OBJECT_FILE}")
endif()

add_library(overflow_ops::overflow_ops ALIAS overflow_ops)

include(CTest)
if(BUILD_TESTING AND OVERFLOW_OPS_TESTS)
  enable_language(CXX)

  find_package(doctest CONFIG)
  if(NOT doctest_FOUND)
    include(FetchContent)
    FetchContent_Declare(
      doctest
      URL "https://github.com/doctest/doctest/archive/refs/tags/v2.4.11.tar.gz"
      URL_HASH "SHA256=632ed2c05a7f53fa961381497bf8069093f0d6628c5f26286161fbd32a560186")
    FetchContent_MakeAvailable(doctest)
    list(APPEND CMAKE_MODULE_PATH "${doctest_SOURCE_DIR}/scripts/cmake")
  endif()

  add_executable(overflow_ops_tests "test/overflow_ops_tests.cpp")
  target_link_libraries(overflow_ops_tests PRIVATE overflow_ops doctest::doctest)

  include(doctest)
  doctest_discover_tests(overflow_ops_tests)
endif()
