CMAKE_MINIMUM_REQUIRED ( VERSION 2.2)

#Project Definition
PROJECT(Rage_AML)

#
#Checking software dependencies
#

INCLUDE (${CMAKE_ROOT}/Modules/FindOpenGL.cmake)

#check for openGL
FIND_PACKAGE(OPENGL)

#calling cmake for SDL
ADD_SUBDIRECTORY(../SDL SDL_cbuild EXCLUDE_FROM_ALL)

#
#Defining Rules for building AML
#

#compiler generic config
INCLUDE_DIRECTORIES(${Rage_AML_SOURCE_DIR}/include ../SDL/include)

#adding SDL libraries to the link
LINK_LIBRARIES (${SDLMAIN_LIBRARY} ${SDL_LIBRARY} ${Rage_SDL_LIBRARY})


#Compiler Specific rules
IF(CMAKE_CXX_COMPILER STREQUAL "cl")
MESSAGE( STATUS "Visual Studio Compiler detected. Adjusting C++ flags...")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /wd4290 " )
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrt.lib" )
ENDIF(CMAKE_CXX_COMPILER STREQUAL "cl")



#adding definitions for Logs and debug
ADD_DEFINITIONS(-DLOGINDENTLVL=0 -DDEBUG)

#listing headers as well to have them easily accessible in many IDE, not sure about the effect on the make build...
ADD_LIBRARY(	Rage_AML
		include/AML.hh
		include/Config.hh
		include/Camera.hh src/Camera.cc
		include/Layer.hh src/Layer.cc
		include/Math2D.hh
		include/Scene.hh src/Scene.cc
		include/Sprite.hh src/Sprite.cc
		include/Window.hh src/Window.cc
	)

ADD_DEPENDENCIES(Rage_AML Rage_SDL)

#
#Adding targets for tests
#Not in a subdir, because of the actual dependency being the other way around than the directory hierarchy
#
#TODO : add custom build command to move the needed files for testing (without installing)...

#linking SDLWrap to all other following libraries
LINK_LIBRARIES(Rage_AML)

#linking opengl for all other tests if detected
IF(OPENGL_FOUND)
	LINK_LIBRARIES (${OPENGL_LIBRARIES})
ENDIF(OPENGL_FOUND)

ADD_EXECUTABLE(AMLtest include/AML.hh test/test.cc)
ADD_DEPENDENCIES(AMLtest Rage_AML)

#
#Adding rules for installation
#

# installing main library
INSTALL_TARGETS(/. FILES AML)
INSTALL_FILES(/include FILES "^include/*.hh$")

# installing dependency if needed
#

# installing main shared data
INSTALL_FILES(/data FILES data/AML_ico.bmp data/AML_sprite.gif)

# installing tests
INSTALL_TARGETS(/test FILES AMLtest)

# installing tests data
#
