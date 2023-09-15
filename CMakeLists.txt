cmake_minimum_required(VERSION 3.15)

# Example Audio Plugin CMakeLists.txt

# Sets the minimum macOS version
if (APPLE)
	set(CMAKE_OSX_DEPLOYMENT_TARGET "10.13" CACHE STRING "Minimum version of the target platform" FORCE) 
	if(CMAKE_OSX_DEPLOYMENT_TARGET)
		message("The minimum macOS version is set to " $CACHE{CMAKE_OSX_DEPLOYMENT_TARGET}.)
	endif()
endif ()

if(APPLE)
	set (FORMATS_TO_BUILD AU VST3 Standalone)
else()
	set (FORMATS_TO_BUILD VST3 Standalone)
endif()

cmake_minimum_required(VERSION 3.15)

set (PROJECT_NAME seamless-plugin-suite)

# The top-level CMakeLists.txt file for a project must contain a literal, direct call to the
# `project()` command. `project()` sets up some helpful variables that describe source/binary
# directories, and the current project version. This is a standard CMake command.

project (${PROJECT_NAME} VERSION 0.0.1)

# Sets the cpp language minimum
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Export only public symbols
# We set this option for all our libraries since the google benchmark lib are setup with hidden visibility
set(CMAKE_CXX_VISIBILITY_PRESET hidden)
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

# Compilation options
if(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE "Release")
endif()

# Juce is included via a submodule
add_subdirectory(modules/JUCE)

# Include the assets and common directories
add_subdirectory(assets)
add_subdirectory(common)

# The following list will hold all the plug-ins which will be built.
# Simply comment them out if you want to build only a subset of the plug-ins.
set (PLUGIN_LIST
        SeamLess_Main
        SeamLess_Client
    )

foreach (PLUGIN IN LISTS PLUGIN_LIST)
    add_subdirectory (${PLUGIN})
endforeach()

# enable ctest
enable_testing()

# this is a test on application level starting the app and checking if it is running
# add_test(NAME RegularUsage COMMAND "SeamLess_Client/SeamLess_Client_artefacts/Debug/Standalone/SeamLess_Client.app")
# we can specify som REGEX to check the output of the application
# set_tests_properties(RegularUsage
#   PROPERTIES FAIL_REGULAR_EXPRESSION "Custom Slider Component"
#   )

# This module enables populating content at configure time via any method supported by the ExternalProject module. Whereas ExternalProject_Add() downloads at build time, the FetchContent module makes content available immediately, allowing the configure step to use the content in commands like add_subdirectory(), include() or file() operations.
include(FetchContent)

# Externally provided libraries
# Using zip files instead is faster
FetchContent_Declare(googletest
	URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)

FetchContent_Declare(benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.8.0)

# This command ensures that each of the named dependencies are made available to the project by the time it returns. If the dependency has already been populated the command does nothing. Otherwise, the command populates the dependency and then calls add_subdirectory() on the result.
FetchContent_MakeAvailable(googletest)

# For benchmark we want to set the BENCMARK_ENABLE_TESTING to OFF therefore we cannot use FetchContent_MakeAvailable()
# Check if population has already been performed
FetchContent_GetProperties(benchmark)
if(NOT benchmark_POPULATED)
  # Fetch the content using previously declared details
  FetchContent_Populate(benchmark)

  # Set custom variables, policies, etc.
  set(BENCHMARK_ENABLE_TESTING OFF)

  # Bring the populated content into the build
  add_subdirectory(${benchmark_SOURCE_DIR} ${benchmark_BINARY_DIR})
endif()

# Make a test executable for every plugin
foreach(PLUGIN IN LISTS PLUGIN_LIST)

    # get all test cpp and header files
    file(GLOB_RECURSE TEST_SOURCES_${PLUGIN} CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/${PLUGIN}/test/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/${PLUGIN}/test/*.h)
    source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR}/${PLUGIN}/test PREFIX "test_${PLUGIN}" FILES ${TEST_SOURCES_${PLUGIN}})

    # Setup the test executable
    add_executable(Test_${PLUGIN} ${TEST_SOURCES_${PLUGIN}})
    set_property(TARGET Test_${PLUGIN} PROPERTY CXX_STANDARD 20)

    # Add include directories for all folders in test
    file(GLOB_RECURSE TEST_DIRS_${PLUGIN} LIST_DIRECTORIES true ${CMAKE_CURRENT_LIST_DIR}/${PLUGIN}/test)

    foreach (DIR ${TEST_DIRS}_${PLUGIN})
        if (IS_DIRECTORY ${DIR})
            target_include_directories(Test_${PLUGIN} PRIVATE ${DIR})
        endif ()
    endforeach ()

    # Link the test executable against gtest_main and google benchmark
    target_link_libraries(Test_${PLUGIN} PRIVATE gtest_main benchmark::benchmark)

    # We can't link again to the shared juce target without ODL violations (https://github.com/sudara/pamplejuce/issues/31, https://forum.juce.com/t/windows-linker-issue-on-develop/55524/2)
    # Therefore we steal the compile definitions and include directories from the main target and pass them to our test target
    # Since we linked the shared juce targets in PRIVATE mode, they are not linked to the test target again
	target_link_libraries(Test_${PLUGIN} PRIVATE ${PLUGIN})
	target_compile_definitions(Test_${PLUGIN} PRIVATE $<TARGET_PROPERTY:${PLUGIN},COMPILE_DEFINITIONS>)
	target_include_directories(Test_${PLUGIN} PRIVATE $<TARGET_PROPERTY:${PLUGIN},INCLUDE_DIRECTORIES>)

    # include Loads and runs CMake code from the file given. Loads and runs CMake code from the file given.
    include(GoogleTest)
    # gtest_discover_tests will register a CTest test for each gtest and run them all in parallel with the rest of the Test.
    gtest_discover_tests(Test_${PLUGIN})
    
endforeach()