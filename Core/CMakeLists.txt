CMAKE_MINIMUM_REQUIRED ( VERSION 2.4)

#Project Definition : Rage::Core
PROJECT(Core)


INCLUDE(../RageCommon.cmake)

#
#Checking software dependencies
#

# --- None ---

#
#Defining Rules for building Core
#

INCLUDE_DIRECTORIES(include)

	
#
#Compiler Specific rules
#
IF(CMAKE_CXX_COMPILER STREQUAL "cl")
	MESSAGE( STATUS "Visual Studio Compiler detected. Adjusting C++ flags...")
	SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /wd4290 " )
ENDIF(CMAKE_CXX_COMPILER STREQUAL "cl")

#
# Managing relation between source and builds 
#
find_program( SVNVERSION
  svnversion
  /usr/local/bin
  /usr/bin
)

macro( svn_repository_version DESTVAR TOPDIR )
  exec_program( ${SVNVERSION} ${TOPDIR} ARGS "." OUTPUT_VARIABLE ${DESTVAR} )
endmacro( svn_repository_version )

svn_repository_version( SVNREV ${Core_SOURCE_DIR} )
#think about where it s better to use the revision...

#
# Managing Build Types
#

#adding definitions for Logs and debug
ADD_DEFINITIONS(-DLOGINDENTLVL=1)

#default value
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug CACHE STRING
      "Choose the type of build, options are: Debug Release."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

IF (CMAKE_BUILD_TYPE STREQUAL Debug)
	ADD_DEFINITIONS(-DDEBUG)
ENDIF (CMAKE_BUILD_TYPE STREQUAL Debug)

#
# Definining what to build
#

SET(BUILD_TESTS OFF CACHE BOOL "Wether or not you want the project to include the tests executables")

INCLUDE_DIRECTORIES(include)
INSTALL_FILES(/include include)

ADD_SUBDIRECTORY(src)

IF (BUILD_TESTS)
	ADD_SUBDIRECTORY(test)
ENDIF(BUILD_TESTS)



#defining usefull variables.
#GET_TARGET_PROPERTY(SDLut_LIBRARY SDLut LOCATION)
#SET(SDLut_INCLUDE ${SDLut_SOURCE_DIR}/include)
#todo set the dependencies


