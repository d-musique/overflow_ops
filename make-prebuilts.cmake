#!/usr/bin/cmake -P

find_program(CLANG_PROGRAM "clang" REQUIRED)

set(targets
  "i686-pc-windows-msvc"
  "x86_64-pc-windows-msvc"
  "aarch64-pc-windows-msvc"
  "arm64ec-pc-windows-msvc")

file(MAKE_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/prebuilts")

foreach(target IN LISTS targets)
  execute_process(
    COMMAND
      "${CLANG_PROGRAM}" "-target" "${target}"
      "-O2" "-DIOP_COMPILED_SEPARATE=1" "-Iinclude"
      "-c" "source/overflow_ops.c"
      "-o" "prebuilts/overflow_ops.${target}.obj"
    WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}"
    COMMAND_ERROR_IS_FATAL ANY)
endforeach()
