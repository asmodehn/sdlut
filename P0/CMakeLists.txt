CMAKE_MINIMUM_REQUIRED ( VERSION 2.4)


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



#Project Definition
PROJECT(Project_0)

#Set Mode rules
IF(NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: None Debug Release." FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

IF (CMAKE_BUILD_TYPE STREQUAL Debug)
	ADD_DEFINITIONS(-D_DEBUG)
	#Visual Studio Specific
	IF(MSVC)
		SET( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /wd4100 /wd4290 /wd4512")
		SET(CMAKE_CXX_WARNING_LEVEL 4)

		#enable/disable VLD mem leaks check
		SET(CHECK_MEM_LEAKS OFF CACHE BOOL "On to check memory with VLD (must be installed)")
		IF(CHECK_MEM_LEAKS)
			ADD_DEFINITIONS(-DVLD)
		ENDIF(CHECK_MEM_LEAKS)

	ENDIF(MSVC)
ENDIF (CMAKE_BUILD_TYPE STREQUAL Debug)

IF (CMAKE_BUILD_TYPE STREQUAL Release)
	ADD_DEFINITIONS(-DNDEBUG)
	#Visual Studio Specific
	IF(MSVC)
		SET( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /NODEFAULTLIB:msvcrt.lib" )
		SET(CMAKE_CXX_WARNING_LEVEL 2)
	ENDIF(MSVC)
ENDIF (CMAKE_BUILD_TYPE STREQUAL Release)


#Compiler Specific rules
IF(CMAKE_COMPILER_IS_GNUCXX)
	MESSAGE( STATUS "GCC Compiler detected. Adjusting C++ flags...")
	SET( CMAKE_CXX_FLAGS_DEBUG "-g -D_DEBUG -Wall -Wabi" CACHE STRING
	    "Flags used by the C++ compiler during debug builds." )
	SET( CMAKE_C_FLAGS_DEBUG "-g -D_DEBUG -Wall -pedantic" CACHE STRING
	    "Flags used by the C compiler during debug builds." )
	
	IF (MSYS)
	    SET( CMAKE_EXE_LINKER_FLAGS_DEBUG
	     " -Wl,--warn-once" CACHE STRING
	     "Flags used for linking binaries during debug builds."
	     FORCE )
	    SET( CMAKE_SHARED_LINKER_FLAGS_DEBUG
	     " -Wl,--warn-once" CACHE STRING
	     "Flags used by the shared libraries linker during debug builds." )
	ELSE (MSYS)
	    SET( CMAKE_EXE_LINKER_FLAGS_DEBUG
	     " -Wl,--warn-unresolved-symbols,--warn-once" CACHE STRING
	     "Flags used for linking binaries during debug builds." )
	    SET( CMAKE_SHARED_LINKER_FLAGS_DEBUG
	     " -Wl,--warn-unresolved-symbols,--warn-once" CACHE STRING
	     "Flags used by the shared libraries linker during debug builds." )
	ENDIF (MSYS)

ENDIF(CMAKE_COMPILER_IS_GNUCXX)



#Check For SDLut cmake module file
FIND_PATH(NEW_CMAKE_MODULE_PATH FindSDLut.cmake DOC "Please specify where the file 'FindSDLut.cmake' is" NO_DEFAULT_PATH REQUIRED)


#when we now know where the FindSlut module is
IF(NEW_CMAKE_MODULE_PATH)
	
	#Check For SDLut depends file
	FIND_FILE(SDLUT_DEPENDS CMakeDepends.txt DOC "Please specify where the file 'CMakeDepends.txt' is" NO_DEFAULT_PATH REQUIRED)
	
	#when we know where sdlut's dependencies are
	IF(SDLUT_DEPENDS)
		#include sdlut dependances
		INCLUDE(${SDLUT_DEPENDS})

		SET(CMAKE_MODULE_PATH ${NEW_CMAKE_MODULE_PATH})

		#Check dependencies
		FIND_PACKAGE(SDLut REQUIRED)

		#test for RAGE SDLut (_FOUND is present only coz case of package : cmake BUG! )
		IF(SDLut_FOUND)
			MESSAGE (STATUS "Rage::SDLut found, adjusting build options..." )
			INCLUDE_DIRECTORIES(${SDLut_INCLUDE_DIR})
			#link sdlut and sdlut dependances
			#TARGET_LINK_LIBRARIES(Project_0 ${SDLut_LIBRARY} @SDLut_LIB_DEPENDS@ )
			LINK_LIBRARIES (${SDLut_LIBRARY} ${SDLut_LIB_DEPENDS})
		ELSE(SDLut_FOUND)
			#bug here: msg allways seems to popup
			MESSAGE("Rage::SDLut Not Found - Please Specify Manually")
		ENDIF(SDLut_FOUND)

	ELSE(SDLUT_DEPENDS)

		MESSAGE("File 'CMakeDepends.txt' Not Found - Please Specify Manually")

	ENDIF(SDLUT_DEPENDS)

ELSE(NEW_CMAKE_MODULE_PATH)

	MESSAGE("File 'FindSDLut.cmake Not' Found - Please Specify Manually")

ENDIF(NEW_CMAKE_MODULE_PATH)


#check for openGL
FIND_PACKAGE(OpenGL)

#test for openGL
IF(OPENGL_FOUND)
	MESSAGE (STATUS "OpenGL found, adjusting build options..." )
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
	LINK_LIBRARIES (${OPENGL_LIBRARY})
ELSE(OPENGL_FOUND)
	MESSAGE (STATUS "OpenGL not found." )
ENDIF(OPENGL_FOUND)


#check for libxml2
FIND_PACKAGE(LibXml2 REQUIRED)

#Clear the ADVANCED default status for libxml2
MARK_AS_ADVANCED(CLEAR LIBXML2_INCLUDE_DIR LIBXML2_LIBRARIES)

#test for libxml2
IF(LIBXML2_FOUND)
	MESSAGE (STATUS "LibXml2 found, adjusting build options..." )
	INCLUDE_DIRECTORIES(${LIBXML2_INCLUDE_DIR})
	LINK_LIBRARIES (${LIBXML2_LIBRARIES})
ELSE(LIBXML2_FOUND)
	MESSAGE (STATUS "LibXml2 not found." )
ENDIF(LIBXML2_FOUND)

#copy the icon
CONFIGURE_FILE( P0_ico.png ${Project_0_BINARY_DIR}/P0_ico.png COPYONLY )

#Include headers
INCLUDE_DIRECTORIES(${Project_0_SOURCE_DIR}/../Core/include )
INCLUDE_DIRECTORIES(${Project_0_SOURCE_DIR}/include )


#copy useful directories
ADD_SUBDIRECTORY( ${Project_0_SOURCE_DIR}/Config/ )
ADD_SUBDIRECTORY( ${Project_0_SOURCE_DIR}/Data/ )
ADD_SUBDIRECTORY( ${Project_0_SOURCE_DIR}/Saves/ )



#Get headers+sources
FILE(GLOB HEADERS ${CMAKE_SOURCE_DIR}/include/*.hh)
FILE(GLOB SOURCES ${CMAKE_SOURCE_DIR}/src/*.cpp)

#merge them
MERGE("${HEADERS}" "${SOURCES}" CODE_SRC)

#Generate executable project with the CODE_SRC & the specs
ADD_EXECUTABLE(Project_0
		${CODE_SRC}
		"${Project_0_SOURCE_DIR}/Specifs/2D/2D Design v0.04.odt"
		)
