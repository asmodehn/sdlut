#
# Usefull MACROS
#

# This macro merges elements in sorted lists ALIST and BLIST and stored the result in OUTPUT
MACRO(MERGE ALIST BLIST OUTPUT)
   SET(BTEMP ${BLIST})
   FOREACH(A ${ALIST})
       SET(SORTED)
       SET(UNINSERTED 1)
       FOREACH(B ${BTEMP})
           IF(${UNINSERTED})
               IF(${A} STRLESS ${B})
                   SET(SORTED ${SORTED} ${A})
                   SET(UNINSERTED 0)
               ENDIF(${A} STRLESS ${B})
           ENDIF(${UNINSERTED})
           SET(SORTED ${SORTED} ${B})
       ENDFOREACH(B ${BLIST})
       IF(${UNINSERTED})
           SET(SORTED ${SORTED} ${A})
       ENDIF(${UNINSERTED})
       SET(BTEMP ${SORTED})
   ENDFOREACH(A ${ALIST})
   SET(${OUTPUT} ${BTEMP})
ENDMACRO(MERGE ALIST BLIST OUTPUT)

# macro to get the SVN Revision number
find_program( SVNVERSION
  svnversion
  /usr/local/bin
  /usr/pkg/bin
  /usr/bin
)

macro( svn_repository_version DESTVAR TOPDIR )
  exec_program( ${SVNVERSION} ${TOPDIR} ARGS "." OUTPUT_VARIABLE DESTVARORI )
  STRING(REGEX REPLACE "(.+):(.+)" "\\1_\\2" ${DESTVAR} ${DESTVARORI})
endmacro( svn_repository_version )


#
# Configure and Build process based on well-known hierarchy
#

MACRO (RAGE_BUILD project_name project_type)
	# Managing Build Types
	# default build type
	IF(NOT CMAKE_BUILD_TYPE)
	  SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel." FORCE)
	ENDIF(NOT CMAKE_BUILD_TYPE)
	
	IF (CMAKE_BUILD_TYPE STREQUAL Debug)
	#todo : use default cmake debug definition instead
		ADD_DEFINITIONS(-DDEBUG)
		SET(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "Verbose build commands enabled for Debug build" FORCE)
	ENDIF (CMAKE_BUILD_TYPE STREQUAL Debug)

	FILE(GLOB HEADERS ${CMAKE_SOURCE_DIR}/include/*.hh)

	#Including configured headers (binary for the configured header, source for the unmodified ones
	INCLUDE_DIRECTORIES( ${CMAKE_BINARY_DIR}/include ${CMAKE_SOURCE_DIR}/include )

	#Defining target
	FILE(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cc)
	MERGE("${HEADERS}" "${SOURCES}" SOURCES)

	IF(${project_type} STREQUAL "LIBRARY")
		ADD_LIBRARY(${project_name} ${SOURCES})
	ENDIF(${project_type} STREQUAL "LIBRARY")
	IF(${project_type} STREQUAL "EXECUTABLE")
		ADD_EXECUTABLE(${project_name} ${SOURCES})
	ENDIF(${project_type} STREQUAL "EXECUTABLE")

	#needed in case we dont have recognised file extension
	SET_TARGET_PROPERTIES(${project_name} PROPERTIES LINKER_LANGUAGE CXX)

	#
	#Defining where to put whats been built
	#

	SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib CACHE PATH "Ouput directory for libraries")
	SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE PATH "Output directory for executables")

ENDMACRO (RAGE_BUILD)

#
# Defining test rules
#

MACRO(RAGE_TEST project)

	SET(ENABLE_TESTS OFF CACHE BOOL "Wether or not you want the project to include the tests and enable automatic testing")

	IF (ENABLE_TESTS)
		ENABLE_TESTING()
		ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIRECTORY}/test)
	ENDIF(ENABLE_TESTS)
ENDMACRO(RAGE_TEST)


#
# Defining installation rules
#

MACRO (RAGE_INSTALL project_name)

	INSTALL ( FILES ${HEADERS} DESTINATION ${VERSION}/include )

	INSTALL	(
		TARGETS ${project_name}
		RUNTIME DESTINATION ${VERSION}/bin
		LIBRARY DESTINATION ${VERSION}/lib
		ARCHIVE DESTINATION ${VERSION}/lib/static
		)

ENDMACRO(RAGE_INSTALL project_name)

#
# Common use of Cmake in RAGE
#

svn_repository_version( SVN_REV ${CMAKE_SOURCE_DIR})
SET (VERSION ${SVN_REV} CACHE STRING "The detected revision of the source repository")

SET(BUILD_SHARED_LIBS OFF)

#
#Compiler Specific rules
#
IF(MSVC)
	MESSAGE( STATUS "Visual Studio Compiler detected. Adjusting C++ flags...")
	SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /wd4290" CACHE STRING "Flags used by the compiler during all build types" FORCE)
	#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB")
	#MODULE and SHARED also ??
ENDIF(MSVC)



