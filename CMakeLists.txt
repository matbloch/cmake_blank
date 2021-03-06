# CmakeBlank - Blank Template for Cmake based projects
#
# Search and replace: cmakeblank (project name), CMAKEBLANK (uppercase)
# VENDORNAME (software contributor)
#
# Project constants:
# PROJECT_BINARY_DIR: Full path to build directory for project
# PROJECT_SOURCE_DIR: Top level source directory for the current project
#
# WIN32: true for all windows systems (including x64)
#
# Userdefined:
# DYNAMIC_OR_STATIC_LIBS
# ----------------------------------------------

cmake_minimum_required(VERSION 3.2 FATAL_ERROR)

project (cmakeblank)

# CMAKEBLANK_VERSION: <major>.<minor>.<patch>
SET(CMAKEBLANK_MAJOR_VERSION 0) # major version
SET(CMAKEBLANK_MINOR_VERSION 1)	# feature version
SET(CMAKEBLANK_PATCH_VERSION 0) # patch version
SET(CMAKEBLANK_VERSION ${CMAKEBLANK_MAJOR_VERSION}.${CMAKEBLANK_MINOR_VERSION}.${CMAKEBLANK_PATCH_VERSION})

# Change the default build type to Release
IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None, Debug, Release." FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

# Set cmake module search path
set(CMAKE_MODULE_PATH 
	${CMAKE_MODULE_PATH} 
	${CMAKE_SOURCE_DIR}/cmake
)

# build dynamic/static libraries
# [STATIC | SHARED | MODULE]
SET(DYNAMIC_OR_STATIC_LIBS STATIC)

# enable IDE solution folders
set_property(GLOBAL PROPERTY USE_FOLDERS ON) 

#-------------------------------------------------
# Include headers
#-------------------------------------------------

INCLUDE_DIRECTORIES(
    ${cmakeblank_SOURCE_DIR}/include	# project headers
    #${OPENGL_INCLUDE_DIR}				# additional headers (e.g. Eigen)
)

#-------------------------------------------------
# Options
#-------------------------------------------------

# Applications
OPTION(BUILD_CMAKEBLANK_APPLICATIONS "Enable to build Applications" ON)

# Examples
OPTION(BUILD_CMAKEBLANK_EXAMPLES "Enable to build Examples" OFF)

#-------------------------------------------------
# Config header
#-------------------------------------------------

SET(CONFIG_HEADER "${PROJECT_BINARY_DIR}/include/Config.h")
CONFIGURE_FILE("${CMAKE_CURRENT_SOURCE_DIR}/src/Config.cmake.in"
               "${CONFIG_HEADER}")


#-------------------------------------------------
# 3rd Party Dependency
#-------------------------------------------------

# example: find_package(OpenCV 2.4 REQUIRED)

# Platform specific:
IF(WIN32)
	
ENDIF()

IF(APPLE)

ENDIF()

# Include macro utilities
INCLUDE(ProjectMacros)
#-------------------------------------------------
# Optional build components
#-------------------------------------------------

# optional example related dependencies
IF   (BUILD_CMAKEBLANK_EXAMPLES)
	# use find_package() here
ENDIF()

#-------------------------------------------------
# Setup output folders
#-------------------------------------------------

SET(OUTPUT_BINDIR ${PROJECT_BINARY_DIR}/bin)		# builddir/bin
SET(OUTPUT_LIBDIR ${PROJECT_BINARY_DIR}/lib)		# builddir/lib

# create bin and lib folders
MAKE_DIRECTORY(${OUTPUT_BINDIR})		# builddir/bin
MAKE_DIRECTORY(${OUTPUT_LIBDIR})		# builddir/lib

# Generic no-config case (e.g. with mingw)

# 1. CMAKE_RUNTIME_OUTPUT_DIRECTORY
# Executables are always treated as runtime targets
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BINDIR})		# builddir/bin

# 2. CMAKE_ARCHIVE_OUTPUT_DIRECTORY
# Static libraries are always treated as archive targets
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_LIBDIR})

# 3. CMAKE_LIBRARY_OUTPUT_DIRECTORY
# Module libraries are always treated as library targets

IF(WIN32)
	# (.dll) output must bin in /bin folder (together with .exe) in order for Windows to find it
    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_BINDIR})
ELSE(WIN32)
	# (.a) otherwise place them in lib folder
    SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_LIBDIR})
ENDIF(WIN32)

# For non-DLL platforms shared libraries are treated as library targets. 
# For DLL platforms the DLL part of a shared library is treated as a runtime target and 
# the corresponding import library is treated as an archive target (.lib). 
# All Windows-based systems including Cygwin are DLL platforms.

FOREACH(CONF ${CMAKE_CONFIGURATION_TYPES})        # For each configuration (Debug, Release, Minsizerel, ... )
	STRING(TOUPPER "${CONF}" CONF)
	SET("CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONF}" "${OUTPUT_BINDIR}")
	SET("CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONF}" "${OUTPUT_LIBDIR}")
	IF(WIN32)
		# Windows looks for the .dll in the same folder as the .exe, which goes in the /bin folder
		SET("CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONF}" "${OUTPUT_BINDIR}")
	ELSE()
		SET("CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONF}" "${OUTPUT_LIBDIR}")
	ENDIF()
ENDFOREACH()

#-------------------------------------------------
# User Options
#-------------------------------------------------

# Expose CMAKE_INCLUDE_PATH and CMAKE_LIBARY_PATH to the GUI so users
# may set these values without needing to manipulate the environment.
SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} CACHE STRING "You may add additional search paths here. Use ; to separate multiple paths.")
SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} CACHE STRING "You may add additional search paths here. Use ; to separate multiple paths.")

#-------------------------------------------------
# Preprocessor Directives
#-------------------------------------------------

# debugging preprocessor
SET(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D_DEBUG") 

SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

# all errors
#SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror")
#SET(CMAKE_VERBOSE_MAKEFILE ON)

#-------------------------------------------------
# Add sources
#-------------------------------------------------

# Core
ADD_SUBDIRECTORY(src)

# Applications
IF   (BUILD_CMAKEBLANK_APPLICATIONS)
    ADD_SUBDIRECTORY(applications)
ENDIF()

# Examples
IF   (BUILD_CMAKEBLANK_EXAMPLES)
    ADD_SUBDIRECTORY(examples)
ENDIF()

