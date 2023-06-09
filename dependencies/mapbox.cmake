# MPark.Variant
#
# Copyright Michael Park, 2015-2017
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)

if (MPARK_VARIANT_INCLUDE_MAPBOX_BENCHMARKS)
  include(ExternalProject)
  ExternalProject_Add(mapbox
    GIT_REPOSITORY https://github.com/mapbox/variant.git
    GIT_SHALLOW 1
    TIMEOUT 120
    SOURCE_DIR "${CMAKE_CURRENT_BINARY_DIR}/dependencies/mapbox"
    CONFIGURE_COMMAND "" # Disable configure step
    BUILD_COMMAND ""     # Disable build step
    INSTALL_COMMAND ""   # Disable install step
    TEST_COMMAND ""      # Disable test step
    UPDATE_COMMAND ""    # Disable source work-tree update
  )

  ExternalProject_Get_Property(mapbox SOURCE_DIR)
  set(mapbox_INCLUDE_DIRS ${SOURCE_DIR}/include)

  function(mapbox_add_compile_benchmark dataset repeat range)
    metabench_add_dataset(${dataset} compile.mapbox.cpp.erb ${range}
                          NAME mapbox ENV "{repeat: ${repeat}}")
    target_include_directories(${dataset} PUBLIC ${mapbox_INCLUDE_DIRS})
    add_dependencies(${dataset} mapbox)
  endfunction()

  function(mapbox_add_execute_benchmark benchmark)
    add_executable(${benchmark} execute.mapbox.cpp)
    target_include_directories(${benchmark} PUBLIC ${mapbox_INCLUDE_DIRS})
    target_link_libraries(${benchmark} PUBLIC benchmark_main)
    add_test(${benchmark} ${benchmark} --benchmark_color=true)
    add_dependencies(${benchmark} mapbox)
  endfunction()
else()
  function(mapbox_add_compile_benchmark)
  endfunction()

  function(mapbox_add_execute_benchmark)
  endfunction()
endif()
