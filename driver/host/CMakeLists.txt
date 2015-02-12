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

include_directories(../kernel)

SOAPY_SDR_MODULE_UTIL(
    TARGET NovenaRF
    SOURCES
        Streaming.cpp
        NovenaRF.cpp
        LoadFPGA.cpp
)
