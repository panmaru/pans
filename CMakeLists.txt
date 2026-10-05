cmake_minimum_required(VERSION 3.24)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(pans VERSION 0.0.1 LANGUAGES CXX C)

include(GNUInstallDirs)

# TODO: Use target_compile_features() instead of CMAKE_CXX_STANDARD
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(PANS_BUILD_EXAMPLES "Build examples" ${PROJECT_IS_TOP_LEVEL})
option(PANS_BUILD_TESTS    "Build tests"    ${PROJECT_IS_TOP_LEVEL})
option(PANS_BUILD_TOOLS    "Build tools"    ${PROJECT_IS_TOP_LEVEL})

if(NOT DEFINED CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_BUILD_TYPE)
	set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS Debug Release RelWithDebInfo MinSizeRel)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: Debug Release RelWithDebInfo MinSizeRel." FORCE)
endif()

include(cmake/pansOptions.cmake)

add_subdirectory(pans)

if(PANS_BUILD_EXAMPLES)
	add_subdirectory(examples)
endif()

if(PANS_BUILD_TESTS)
	include(CTest)
	add_subdirectory(tests)
endif()

if(PANS_BUILD_TOOLS)
	add_subdirectory(tools)
endif()

install(TARGETS pans_options EXPORT pansTargets)
# TODO: Add install(EXPORT pansTargets ...)
