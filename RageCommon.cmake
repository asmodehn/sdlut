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
  exec_program( ${SVNVERSION} ${TOPDIR} ARGS "." OUTPUT_VARIABLE ${DESTVAR} )
endmacro( svn_repository_version )

#think about where it s better to use svn_repository_version...


#
# Common use of Cmake
#

#
#Compiler Specific rules
#
IF(MSVC)
MESSAGE( STATUS "Visual Studio Compiler detected. Adjusting C++ flags...")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /wd4290" CACHE STRING "Flags used by the compiler during all build types" FORCE)
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB")
#MODULE and SHARED also ??
ENDIF(MSVC)



#
# Managing Build Types
#

# default build type
IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug CACHE STRING
      "Choose the type of build, options are: None Debug Release RelWithDebInfo MinSizeRel."
      FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

IF (CMAKE_BUILD_TYPE STREQUAL Debug)
#todo : use default cmake debug definition instead
	ADD_DEFINITIONS(-DDEBUG)
	SET(CMAKE_VERBOSE_MAKEFILE ON CACHE BOOL "Verbose build commands enabled for Debug build" FORCE)
ENDIF (CMAKE_BUILD_TYPE STREQUAL Debug)


#
#Defining where to put whats been built
#
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib CACHE STRING "Ouput directory for Library")
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE STRING "Output directory for Tests")



