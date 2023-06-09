# MPark.Variant
#
# Copyright Michael Park, 2015-2017
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

if (MPARK_VARIANT_INCLUDE_EGGS_BENCHMARKS)
  include(ExternalProject)
  ExternalProject_Add(eggs
    GIT_REPOSITORY https://github.com/eggs-cpp/variant.git
    GIT_SHALLOW 1
    TIMEOUT 120
    SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/dependencies/eggs"
    CONFIGURE_COMMAND "" # Disable configure step
    BUILD_COMMAND ""     # Disable build step
    INSTALL_COMMAND ""   # Disable install step
    TEST_COMMAND ""      # Disable test step
    UPDATE_COMMAND ""    # Disable source work-tree update
  )

  ExternalProject_Get_Property(eggs SOURCE_DIR)
  set(eggs_INCLUDE_DIRS ${SOURCE_DIR}/include)

  function(eggs_add_compile_benchmark dataset repeat range)
    metabench_add_dataset(${dataset} compile.eggs.cpp.erb ${range}
                          NAME eggs ENV "{repeat: ${repeat}}")
    target_include_directories(${dataset} PUBLIC ${eggs_INCLUDE_DIRS})
    add_dependencies(${dataset} eggs)
  endfunction()

  function(eggs_add_execute_benchmark benchmark)
    add_executable(${benchmark} execute.eggs.cpp)
    target_include_directories(${benchmark} PUBLIC ${eggs_INCLUDE_DIRS})
    target_link_libraries(${benchmark} PUBLIC benchmark_main)
    add_test(${benchmark} ${benchmark} --benchmark_color=true)
    add_dependencies(${benchmark} eggs)
  endfunction()
else()
  function(eggs_add_compile_benchmark)
  endfunction()

  function(eggs_add_execute_benchmark)
  endfunction()
endif()
