########################################################################
## Build SoapySDR support module for Novena-RF SDR
##
## Copyright (c) 2015-2015 Lime Microsystems
## Copyright (c) 2015-2015 Andrew "bunnie" Huang
## SPDX-License-Identifier: Apache-2.0
## http://www.apache.org/licenses/LICENSE-2.0
########################################################################

cmake_minimum_required(VERSION 2.6)
project(SoapySDRNovenaRF CXX)
enable_testing()

#select the release build type by default to get optimization flags
if(NOT CMAKE_BUILD_TYPE)
   set(CMAKE_BUILD_TYPE "Release")
   message(STATUS "Build type not specified: defaulting to release.")
endif(NOT CMAKE_BUILD_TYPE)
set(CMAKE_BUILD_TYPE ${CMAKE_BUILD_TYPE} CACHE STRING "")

########################################################################
# lms suite sources
########################################################################
set(LMS_SUITE_BASE ${PROJECT_SOURCE_DIR}/../../lms-suite/lms-suite/src)
get_filename_component(LMS_SUITE_BASE ${LMS_SUITE_BASE} ABSOLUTE)
message(STATUS "LMS_SUITE_BASE: ${LMS_SUITE_BASE}")

#glob for sources
file(GLOB LMS_SOURCES "${LMS_SUITE_BASE}/src/*.cpp")
file(GLOB LMS6_SOURCES "${LMS_SUITE_BASE}/src/lms6/*.cpp")
list(APPEND LMS_SOURCES ${LMS6_SOURCES})

#lms include directories
include_directories(${LMS_SUITE_BASE}/include)
include_directories(${LMS_SUITE_BASE}/include/lms6)

#hide noisy warnings
set_source_files_properties(${LMS_SOURCES} NovenaLMS6.cpp
    PROPERTIES "COMPILE_FLAGS" "-Wno-unused-parameter")
#add_definitions(-Wno-unused-parameter)

#libraries: pthread, and usb
#usb not really needed, but its part of the build
#it should be ifdef'd out to reduce dependencies
set(LMS_LIBRARIES
    pthread
    usb-1.0
)

########################################################################
# build the module
########################################################################
find_package(SoapySDR CONFIG)

if (NOT SoapySDR_FOUND)
    message(FATAL_ERROR "SoapySDR development files not found")
endif ()

if(CMAKE_COMPILER_IS_GNUCXX)
    #C++11 is a required language feature for this project
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif()

add_compile_options(-mfloat-abi=hard -mfpu=neon)

include_directories(../kernel)

SOAPY_SDR_MODULE_UTIL(
    TARGET NovenaRF
    SOURCES
        Streaming.cpp
        NovenaRF.cpp
        NovenaLMS6.cpp
        LoadFPGA.cpp
        ${LMS_SOURCES}
    LIBRARIES
        ${LMS_LIBRARIES}
)
