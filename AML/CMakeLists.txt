CMAKE_MINIMUM_REQUIRED ( VERSION 2.2)

#Project Definition
PROJECT(Rage_AML)

#
#Checking software dependencies
#

SET(CMAKE_MODULE_PATH ../SDL/CMake)

#check for openGL
FIND_PACKAGE(OPENGL)
FIND_PACKAGE(Rage_SDL REQUIRED)

#
#Defining Rules for building AML
#

#Compiler Specific rules
IF(CMAKE_CXX_COMPILER STREQUAL "cl")
MESSAGE( STATUS "Visual Studio Compiler detected. Adjusting C++ flags...")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /wd4290 " )
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrt.lib" )
ENDIF(CMAKE_CXX_COMPILER STREQUAL "cl")

#to put the SVN Revision number in the build
find_program( SVNVERSION
  svnversion
  /usr/local/bin
  /usr/bin
)

macro( svn_repository_version DESTVAR TOPDIR )
  exec_program( ${SVNVERSION} ${TOPDIR} ARGS "." OUTPUT_VARIABLE ${DESTVAR} )
endmacro( svn_repository_version )

svn_repository_version( SVNREV ${Rage_AML_SOURCE_DIR} )
#think about where it s better to use SVNREV...

#adding definitions for Logs and debug
ADD_DEFINITIONS(-DLOGINDENTLVL=0 -DDEBUG)

#test for Rage_SDL
IF(RAGE_SDL_FOUND)
	MESSAGE (STATUS "Rage::SDL found, adjusting build options..." )
	#adding SDL includes to the build
	INCLUDE_DIRECTORIES(${RAGE_SDL_INCLUDE_DIR})
	#adding SDL libraries to the link
	LINK_LIBRARIES (${RAGE_SDL_LIBRARY})
ENDIF(RAGE_SDL_FOUND)


INCLUDE_DIRECTORIES(include)
INSTALL_FILES(/include include)

ADD_SUBDIRECTORY(src)

SET(BUILD_TESTS OFF CACHE BOOL "Wether or not you want the project to include the tests executables")

ADD_SUBDIRECTORY(data)

IF (BUILD_TESTS)
	ADD_SUBDIRECTORY(test)
ENDIF(BUILD_TESTS)

