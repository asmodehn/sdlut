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

#copy data
ADD_SUBDIRECTORY( ${Project_0_SOURCE_DIR}/data/ )


#adding with headers to have them in generated projects
ADD_EXECUTABLE(
		Project_0
		${Project_0_SOURCE_DIR}/src/Project0.cpp ${Project_0_SOURCE_DIR}/include/Project0.hh 
		${Project_0_SOURCE_DIR}/src/Base.cpp ${Project_0_SOURCE_DIR}/include/Base.hh 
		${Project_0_SOURCE_DIR}/src/BattleField.cpp ${Project_0_SOURCE_DIR}/include/BattleField.hh
		${Project_0_SOURCE_DIR}/src/Character_Base.cpp ${Project_0_SOURCE_DIR}/include/Character_Base.hh
		${Project_0_SOURCE_DIR}/src/Daemons.cpp ${Project_0_SOURCE_DIR}/include/Daemons.hh
		${Project_0_SOURCE_DIR}/src/Input_Management.cpp ${Project_0_SOURCE_DIR}/include/Input_Management.hh
		${Project_0_SOURCE_DIR}/src/Menus.cpp ${Project_0_SOURCE_DIR}/include/Menus.hh
		${Project_0_SOURCE_DIR}/src/Monster_Base.cpp ${Project_0_SOURCE_DIR}/include/Monster_Base.hh
		${Project_0_SOURCE_DIR}/src/Monster_Factory.cpp ${Project_0_SOURCE_DIR}/include/Monster_Factory.hh
		${Project_0_SOURCE_DIR}/src/Monsters.cpp ${Project_0_SOURCE_DIR}/include/Monsters.hh
		${Project_0_SOURCE_DIR}/src/Render_Engine.cpp ${Project_0_SOURCE_DIR}/include/Render_Engine.hh
		${Project_0_SOURCE_DIR}/src/Sounds.cpp ${Project_0_SOURCE_DIR}/include/Sounds.hh

#adding data to have them in generated projects
		#Cmake BUG on copying arrow.bmp file: copy failed, dest file 8k instead of src 13k
		${Project_0_SOURCE_DIR}/data/Arrow.bmp
		${Project_0_SOURCE_DIR}/data/BackGround_Map.txt
		${Project_0_SOURCE_DIR}/data/Character_Archer.bmp
		${Project_0_SOURCE_DIR}/data/Character_Fighter.bmp
		${Project_0_SOURCE_DIR}/data/SlimSansSerif.ttf
		${Project_0_SOURCE_DIR}/data/Environment_Map.txt
		${Project_0_SOURCE_DIR}/data/Grass.png
		"${Project_0_SOURCE_DIR}/data/Houses Tileset.png"
		${Project_0_SOURCE_DIR}/data/LeaveMenu_NoSelected.png
		${Project_0_SOURCE_DIR}/data/LeaveMenu_YesSelected.png
		${Project_0_SOURCE_DIR}/data/Monsters5.bmp
		${Project_0_SOURCE_DIR}/data/Rock.png
		"${Project_0_SOURCE_DIR}/data/Sand Tileset.png"
		"${Project_0_SOURCE_DIR}/data/Trees Tileset.png"
		"${Project_0_SOURCE_DIR}/data/tankbrigade.bmp"
		${Project_0_SOURCE_DIR}/data/Wall.png
		${Project_0_SOURCE_DIR}/data/Water.png
		${Project_0_SOURCE_DIR}/data/esc_menu_sound.wav
		${Project_0_SOURCE_DIR}/data/null.wav

#adding spec to have it in generated projects
		"${Project_0_SOURCE_DIR}/Specifs/2D/2D Design v0.02.odt"
	)


#adding definitions for Logs and debug
#ADD_DEFINITIONS(-DLOGINDENTLVL=1)
#ADD_DEFINITIONS(-DLOGPREFIX=\"RAGE_SDL\")
