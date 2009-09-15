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
PROJECT(GuiChan_SDLuT)

#Set Mode rules
IF(NOT CMAKE_BUILD_TYPE)
	SET(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build, options are: None Debug Release." FORCE)
ENDIF(NOT CMAKE_BUILD_TYPE)

IF (CMAKE_BUILD_TYPE STREQUAL Debug)
	ADD_DEFINITIONS(-D_DEBUG -DGUICHAN_BUILD=1 -DGUICHAN_EXTENSION_BUILD=1)
	#Visual Studio Specific
	IF(MSVC)
		SET( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /wd4100 /wd4290 /wd4512 /wd4251")
		SET(CMAKE_CXX_WARNING_LEVEL 4)
		
		#enable/disable VLD mem leaks check
		SET(CHECK_MEM_LEAKS OFF CACHE BOOL "On to check memory with VLD (must be installed)")
		IF(CHECK_MEM_LEAKS)
			ADD_DEFINITIONS(-DVLD)
		ENDIF(CHECK_MEM_LEAKS)

	ENDIF(MSVC)
ENDIF (CMAKE_BUILD_TYPE STREQUAL Debug)

IF (CMAKE_BUILD_TYPE STREQUAL Release)
	ADD_DEFINITIONS(-DNDEBUG -DGUICHAN_BUILD=1 -DGUICHAN_EXTENSION_BUILD=1)
	#Visual Studio Specific
	IF(MSVC)
		SET(CMAKE_CXX_WARNING_LEVEL 2)
	ENDIF(MSVC)
ENDIF (CMAKE_BUILD_TYPE STREQUAL Release)

#Definitions needed for guichan
ADD_DEFINITIONS(-DHAVE_OPENGL)


#Compiler Specific rules
IF (CMAKE_COMPILER_IS_GNUCXX)
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
ENDIF (CMAKE_COMPILER_IS_GNUCXX)

#set where to put stuff that will be built
SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib CACHE PATH "Ouput directory for libraries")
SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE PATH "Output directory for executables")

SET(BUILD_SHARED_LIBS OFF CACHE BOOLEAN "Set it to ON if you want this library to be a shared library" )

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

		#add definitions
		ADD_DEFINITIONS(-DHAVE_OPENGL)
		ADD_DEFINITIONS(-DHAVE_SDLIMAGE)
		ADD_DEFINITIONS(-DHAVE_SDLTTF)
		ADD_DEFINITIONS(-DHAVE_SDLMIXER)
		ADD_DEFINITIONS(-DHAVE_SDLNET)

			
		SET(CMAKE_MODULE_PATH ${NEW_CMAKE_MODULE_PATH})

		#check for sdlut
		FIND_PACKAGE(SDLut REQUIRED)
		
		#test for RAGE SDLut (_FOUND is present only coz case of package : cmake BUG! )
		IF(SDLut_FOUND)
			MESSAGE (STATUS "Rage::SDLut found, adjusting build options..." )
			INCLUDE_DIRECTORIES(${SDLut_INCLUDE_DIR})
			
			IF (CMAKE_BUILD_TYPE STREQUAL Release)
				INCLUDE_DIRECTORIES(${SDLut_INCLUDE_DIR}/../src)
			ENDIF (CMAKE_BUILD_TYPE STREQUAL Release)
			
			#Include the Core for the logger.hh file
			INCLUDE_DIRECTORIES(${SDLut_INCLUDE_DIR}/../../Core/include )
			#link sdlut and sdlut dependances
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
FIND_PACKAGE(OpenGL REQUIRED)

#test for openGL
IF(OPENGL_FOUND)
	MESSAGE (STATUS "OpenGL found, adjusting build options..." )
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
	LINK_LIBRARIES (${OPENGL_LIBRARY})
ELSE(OPENGL_FOUND)
	MESSAGE ("OpenGL not found." )
ENDIF(OPENGL_FOUND)


#Include headers (sdlut FE + sdlut_ogl FE + guichan)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../GuiChan_s_SDLuT_FrontEnd/include)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../GuiChan_Sources/include)

#Get SDLuT FrontEnd's Headers & merge them
FILE(GLOB FE_HEADERS1 ${CMAKE_SOURCE_DIR}/../GuiChan_s_SDLuT_FrontEnd/include/guichan/*.hpp)
FILE(GLOB FE_HEADERS2 ${CMAKE_SOURCE_DIR}/../GuiChan_s_SDLuT_FrontEnd/include/guichan/sdlut/*.hpp)
MERGE("${FE_HEADERS1}" "${FE_HEADERS2}" FE_HEADERS)

#Get SDLuT FrontEnd's Srcs & merge them
FILE(GLOB FE_SOURCES ${CMAKE_SOURCE_DIR}/../GuiChan_s_SDLuT_FrontEnd/src/sdlut/*.cpp)

#merge FrontEnd's headers + srcs
MERGE("${FE_HEADERS}" "${FE_SOURCES}" FE_CODE_SRC)

#Get GuiChan's headers & merge them
FILE(GLOB GC_HEADERS1 ${CMAKE_SOURCE_DIR}/../GuiChan_Sources/include/*.hpp)
FILE(GLOB GC_HEADERS2 ${CMAKE_SOURCE_DIR}/../GuiChan_Sources/include/guichan/*.hpp)
MERGE("${GC_HEADERS1}" "${GC_HEADERS2}" GC_HEADERS1_2)
FILE(GLOB GC_HEADERS3 ${CMAKE_SOURCE_DIR}/../GuiChan_Sources/include/guichan/widgets/*.hpp)
MERGE("${GC_HEADERS1_2}" "${GC_HEADERS3}" GC_HEADERS)

#Get GuiChan's srcs & merge them
FILE(GLOB GC_SOURCES1 ${CMAKE_SOURCE_DIR}/../GuiChan_Sources/src/*.cpp)
FILE(GLOB GC_SOURCES2 ${CMAKE_SOURCE_DIR}/../GuiChan_Sources/src/widgets/*.cpp)
MERGE("${GC_SOURCES1}" "${GC_SOURCES2}" GC_SOURCES)

#merge GuiChan's headers + srcs
MERGE("${GC_HEADERS}" "${GC_SOURCES}" GUICHAN_CODE_SRC)

#merge FrontEnds's Code & GuiChan's code
MERGE("${FE_CODE_SRC}" "${GUICHAN_CODE_SRC}" CODE_SRC)

#Generate libraries from the CODE_SRC
ADD_LIBRARY(GuiChan_SDLuT ${CODE_SRC} )

################## Examples ##################
SET(ENABLE_EXAMPLES ON CACHE BOOL "Wether or not you want the project to include the examples")

IF(ENABLE_EXAMPLES)

	INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/../GuiChan_Sources/examples)

	CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/../GuiChan_Sources/examples/darkbitslogo_by_haiko.bmp ${CMAKE_BINARY_DIR}/darkbitslogo_by_haiko.bmp COPYONLY)
	CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/../GuiChan_Sources/examples/fixedfont.bmp ${CMAKE_BINARY_DIR}/fixedfont.bmp COPYONLY)
	CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/../GuiChan_Sources/examples/gui-chan.bmp ${CMAKE_BINARY_DIR}/gui-chan.bmp COPYONLY)
	CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/examples/data/SlimSansSerif.ttf ${CMAKE_BINARY_DIR}/SlimSansSerif.ttf COPYONLY)

	LINK_LIBRARIES(GuiChan_SDLuT)

	
	ADD_EXECUTABLE(GuiChan_SDLuT_Action examples/sdlutaction.cpp)
	#ADD_DEPENDENCIES(GuiChan_Action GuiChan_SDL)
	#ADD_TEST(Version ${EXECUTABLE_OUTPUT_PATH}/GuiChan_Action)

	ADD_EXECUTABLE(GuiChan_SDLuT_HelloWorld examples/sdluthelloworld.cpp)
	#ADD_DEPENDENCIES(GuiChan_HelloWorld GuiChan_SDL)
	#ADD_TEST(Version ${EXECUTABLE_OUTPUT_PATH}/GuiChan_HelloWorld)

	ADD_EXECUTABLE(GuiChan_SDLuT_Widgets examples/sdlutwidgets.cpp)
	#ADD_DEPENDENCIES(GuiChan_Widgets GuiChan_SDL)
	#ADD_TEST(Version ${EXECUTABLE_OUTPUT_PATH}/GuiChan_Widgets)

ENDIF(ENABLE_EXAMPLES)


