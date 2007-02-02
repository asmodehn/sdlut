CMAKE_MINIMUM_REQUIRED ( VERSION 2.4)

#Project Definition
PROJECT(Project_0)

#### from SDLut for includes #####
#### Temporary. SDLut should hide dependencies as much as possible, for the user not to take care about it...
#INCLUDE(../RageCommon.cmake)

#
#Checking software dependencies
#

#Default Check for SDL
MESSAGE(STATUS "Checking for SDL")
FIND_PACKAGE(SDL REQUIRED)

#If not found ask the user for the location of it
IF ( NOT SDL_FOUND )
	MESSAGE(SEND_ERROR "SDL Not Found - please specify manually")
ENDIF(NOT SDL_FOUND )

#check for openGL
FIND_PACKAGE(OpenGL)
#opengl optional

#check for sdl_image
FIND_PACKAGE(SDL_image)
#sdl_image optional

#check for sdl_ttf
FIND_PACKAGE(SDL_ttf)
#sdl_ttf optional

#check for sdl_mixer
FIND_PACKAGE(SDL_mixer)
#sdl_mixer optional

#check for sdl_net
FIND_PACKAGE(SDL_net)
#sdl_net optional

#
#Defining Rules for building SDL Utility Toolkit
#

# this should be a dependency
INCLUDE_DIRECTORIES(${SDLut_SOURCE_DIR}/../Core/include )

#test for SDL
IF(SDL_FOUND)
	MESSAGE (STATUS "SDL found, adjusting build options..." )
	#adding SDL includes to the build
	INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})
	#adding SDL libraries to the link
	LINK_LIBRARIES (${SDL_LIBRARY})
ENDIF(SDL_FOUND)

#test for openGL
IF(OPENGL_FOUND)
	MESSAGE (STATUS "OpenGL found, adjusting build options..." )
	ADD_DEFINITIONS(-DHAVE_OPENGL)
	INCLUDE_DIRECTORIES(${OPENGL_INCLUDE_DIR})
ELSE (OPENGL_FOUND)
	MESSAGE (STATUS "OpenGL not found." )
ENDIF(OPENGL_FOUND)
#linking late to test dynamic linking of opengl libs

#test for sdl_image
IF(SDLIMAGE_FOUND)
	MESSAGE (STATUS "SDL_image found, adjusting build options..." )
	ADD_DEFINITIONS(-DHAVE_SDLIMAGE)
	INCLUDE_DIRECTORIES(${SDLIMAGE_INCLUDE_DIR})
	LINK_LIBRARIES (${SDLIMAGE_LIBRARY})
ELSE (SDLIMAGE_FOUND)
	MESSAGE (STATUS "SDL_image not found." )
ENDIF(SDLIMAGE_FOUND)
	
#test for sdl_ttf
IF(SDLTTF_FOUND)
	MESSAGE (STATUS "SDL_ttf found, adjusting build options..." )
	ADD_DEFINITIONS(-DHAVE_SDLTTF)
	INCLUDE_DIRECTORIES(${SDLTTF_INCLUDE_DIR})
	LINK_LIBRARIES (${SDLTTF_LIBRARY})
ELSE (SDLTTF_FOUND)
	MESSAGE (STATUS "SDL_ttf not found." )
ENDIF(SDLTTF_FOUND)

#test for sdl_mixer
IF(SDLMIXER_FOUND)
	MESSAGE (STATUS "SDL_mixer found, adjusting build options..." )
	ADD_DEFINITIONS(-DHAVE_SDLMIXER)
	INCLUDE_DIRECTORIES(${SDLMIXER_INCLUDE_DIR})
	LINK_LIBRARIES (${SDLMIXER_LIBRARY})
ELSE (SDLMIXER_FOUND)
	MESSAGE (STATUS "SDL_mixer not found." )
ENDIF(SDLMIXER_FOUND)

#test for sdl_net
IF(SDLNET_FOUND)
	MESSAGE (STATUS "SDL_Net found, adjusting build options..." )
	ADD_DEFINITIONS(-DHAVE_SDLNET)
	INCLUDE_DIRECTORIES(${SDLNET_INCLUDE_DIR})
	LINK_LIBRARIES (${SDLNET_LIBRARY})
ELSE (SDLNET_FOUND)
	MESSAGE (STATUS "SDL_Net not found." )
ENDIF(SDLNET_FOUND)	
	
######## from SDLut for includes #######


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


#adding datas to have them in generated projects
	#Battlefield
		${Project_0_SOURCE_DIR}/Datas/Battlefield/BackGround_Map.txt
		${Project_0_SOURCE_DIR}/Datas/Battlefield/Environment_Map.txt
		${Project_0_SOURCE_DIR}/Datas/Battlefield/Grass.png
		"${Project_0_SOURCE_DIR}/Datas/Battlefield/Houses Tileset.png"
		${Project_0_SOURCE_DIR}/Datas/Battlefield/Rock.png
		"${Project_0_SOURCE_DIR}/Datas/Battlefield/Sand Tileset.png"
		"${Project_0_SOURCE_DIR}/Datas/Battlefield/Trees Tileset.png"
		"${Project_0_SOURCE_DIR}/Datas/Battlefield/tankbrigade.bmp"
		${Project_0_SOURCE_DIR}/Datas/Battlefield/Wall.png
		${Project_0_SOURCE_DIR}/Datas/Battlefield/Water.png

	#Characters
		${Project_0_SOURCE_DIR}/Datas/Characters/Character_Archer.bmp
		${Project_0_SOURCE_DIR}/Datas/Characters/Character_Fighter.bmp
		${Project_0_SOURCE_DIR}/Datas/Characters/Monsters5.bmp
		"${Project_0_SOURCE_DIR}/Datas/Characters/Life Bar Tile.bmp"

	#Fonts
		${Project_0_SOURCE_DIR}/Datas/Fonts/SlimSansSerif.ttf

	#Interface
		${Project_0_SOURCE_DIR}/Datas/Interface/LeaveMenu_NoSelected.png
		${Project_0_SOURCE_DIR}/Datas/Interface/LeaveMenu_YesSelected.png	

	#Items
		${Project_0_SOURCE_DIR}/Datas/Items/Arrow.bmp

	#Movies


	#Musics
		"${Project_0_SOURCE_DIR}/Datas/Musics/Global Music.wav"

	#SFXs
		${Project_0_SOURCE_DIR}/Datas/SFXs/esc_menu_sound.wav
		${Project_0_SOURCE_DIR}/Datas/SFXs/null.wav

#adding spec to have it in generated projects
		"${Project_0_SOURCE_DIR}/Specifs/2D/2D Design v0.03.odt"
	)


#adding definitions for Logs and debug
#ADD_DEFINITIONS(-DLOGINDENTLVL=1)
#ADD_DEFINITIONS(-DLOGPREFIX=\"RAGE_SDL\")
