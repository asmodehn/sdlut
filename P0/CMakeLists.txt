CMAKE_MINIMUM_REQUIRED ( VERSION 2.4)

#Project Definition
PROJECT(Project_0)

#Compiler Specific rules (Visual Studio)

IF(CMAKE_CXX_COMPILER STREQUAL "cl")
	MESSAGE( STATUS "Visual Studio Compiler detected. Adjusting C++ flags...")
	SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /wd4290 /W2" )
	#SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /wd4290 " )
	#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrt.lib" )
	ADD_DEFINITIONS(-DVISUAL_STUDIO)
ENDIF(CMAKE_CXX_COMPILER STREQUAL "cl")
IF(CMAKE_COMPILER_IS_GNUCXX)
	MESSAGE( STATUS "GCC Compiler detected. Adjusting C++ flags...")
	SET( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wabi" CACHE STRING
	    "Flags used by the C++ compiler during debug builds."
	    FORCE )
	SET( CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -pedantic" CACHE STRING
	    "Flags used by the C compiler during debug builds."
	    FORCE )
	SET( CMAKE_EXE_LINKER_FLAGS_DEBUG
	    "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -Wl,--warn-unresolved-symbols,--warn-once" CACHE STRING
	    "Flags used for linking binaries during debug builds."
	    FORCE )
	SET( CMAKE_SHARED_LINKER_FLAGS_DEBUG
	    "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} -Wl,--warn-unresolved-symbols,--warn-once" CACHE STRING
	    "Flags used by the shared libraries linker during debug builds."
	    FORCE )
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


#Include Core
INCLUDE_DIRECTORIES(${Project_0_SOURCE_DIR}/../Core/include )


#include headers
INCLUDE_DIRECTORIES(${Project_0_SOURCE_DIR}/include )

#copy Config
ADD_SUBDIRECTORY( ${Project_0_SOURCE_DIR}/Config/ )

#copy Datas
ADD_SUBDIRECTORY( ${Project_0_SOURCE_DIR}/Datas/ )


#adding with headers to have them in generated projects
ADD_EXECUTABLE(
		Project_0
		${Project_0_SOURCE_DIR}/src/Project0.cpp ${Project_0_SOURCE_DIR}/include/Project0.hh 
		${Project_0_SOURCE_DIR}/src/Base.cpp ${Project_0_SOURCE_DIR}/include/Base.hh 
		${Project_0_SOURCE_DIR}/src/BattleField.cpp ${Project_0_SOURCE_DIR}/include/BattleField.hh
		${Project_0_SOURCE_DIR}/src/Player_Base.cpp ${Project_0_SOURCE_DIR}/include/Player_Base.hh
		${Project_0_SOURCE_DIR}/src/Daemons.cpp ${Project_0_SOURCE_DIR}/include/Daemons.hh
		${Project_0_SOURCE_DIR}/src/Input_Management.cpp ${Project_0_SOURCE_DIR}/include/Input_Management.hh
		${Project_0_SOURCE_DIR}/src/Menus.cpp ${Project_0_SOURCE_DIR}/include/Menus.hh
		${Project_0_SOURCE_DIR}/src/Monster_Base.cpp ${Project_0_SOURCE_DIR}/include/Monster_Base.hh
		${Project_0_SOURCE_DIR}/src/Monster_Factory.cpp ${Project_0_SOURCE_DIR}/include/Monster_Factory.hh
		${Project_0_SOURCE_DIR}/src/Monsters.cpp ${Project_0_SOURCE_DIR}/include/Monsters.hh
		${Project_0_SOURCE_DIR}/src/Render_Engine.cpp ${Project_0_SOURCE_DIR}/include/Render_Engine.hh
		${Project_0_SOURCE_DIR}/src/Sounds.cpp ${Project_0_SOURCE_DIR}/include/Sounds.hh
		${Project_0_SOURCE_DIR}/src/Character_Base.cpp ${Project_0_SOURCE_DIR}/include/Character_Base.hh
		${Project_0_SOURCE_DIR}/src/Ini_Manager.cpp ${Project_0_SOURCE_DIR}/include/Ini_Manager.hh
		${Project_0_SOURCE_DIR}/src/Player.cpp ${Project_0_SOURCE_DIR}/include/Player.hh
		${Project_0_SOURCE_DIR}/src/NPCs.cpp ${Project_0_SOURCE_DIR}/include/NPCs.hh

#adding spec to have it in generated projects
		"${Project_0_SOURCE_DIR}/Specifs/2D/2D Design v0.03.odt"
	)


#adding definitions for Logs and debug
#ADD_DEFINITIONS(-DLOGINDENTLVL=1)
#ADD_DEFINITIONS(-DLOGPREFIX=\"RAGE_SDL\")
