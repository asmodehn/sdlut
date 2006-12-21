CMAKE_MINIMUM_REQUIRED ( VERSION 2.4)

#Project Definition
PROJECT(Project_0)



#Compiler Specific rules
IF(CMAKE_CXX_COMPILER STREQUAL "cl")
MESSAGE( STATUS "Visual Studio Compiler detected. Adjusting C++ flags...")
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /wd4290 " )
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} /W2 " )
#SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /NODEFAULTLIB:msvcrt.lib" )
ENDIF(CMAKE_CXX_COMPILER STREQUAL "cl")


#For future dev try to make this work (when P0 will be separated from RAGE)
#Check For SDLut
SET(CMAKE_MODULE_PATH C:/Boulot/Project0/AML/trunk/SDLut/CMake/)
#SET(CMAKE_MODULE_PATH ${Project_O_SOURCE_DIR}/../SDLut/CMake/)

#include sdlut dependances
INCLUDE(C:/Boulot/Project0/AML/trunk/SDLut/build/CMakeDepends.txt)

#Check dependencies
FIND_PACKAGE(SDLut REQUIRED)

#test for RAGE SDLut
IF(SDLut_FOUND)
	MESSAGE (STATUS "Rage::SDLut found, adjusting build options..." )
	INCLUDE_DIRECTORIES(${SDLut_INCLUDE_DIR})
	#link sdlut and sdlut dependances
	TARGET_LINK_LIBRARIES( Project_0 ${SDLut_LIBRARY} SDLut_LIB_DEPENDS )
	#TARGET_LINK_LIBRARIES (${SDLut_LIBRARY})
	#INCLUDE_DIRECTORIES(${Project_0_SOURCE_DIR}/../SDLut/include)
	#LINK_LIBRARIES ({Project_0_SOURCE_DIR}/../SDLut/build/lib/debug/SDLut.lib)
ELSE ( NOT SDLut_FOUND )
	MESSAGE("Rage::SDLut Not Found - Please Specify Manually")
ENDIF(SDLut_FOUND)

#Include Core
INCLUDE_DIRECTORIES(${Project_0_SOURCE_DIR}/../Core/include )



#SUBDIRS (include src data specifs/2D)


#include headers
INCLUDE_DIRECTORIES(${Project_0_SOURCE_DIR}/include )
#ADD_DEFINITIONS(-DLOGPREFIX=\"RAGE_SDL\")

#Add dir to the project
ADD_SUBDIRECTORY(${Project_0_SOURCE_DIR}/src)



#adding definitions for Logs and debug

#ADD_DEFINITIONS(-DLOGINDENTLVL=1)





#where to put them
#SET(EXECUTABLE_OUTPUT_PATH ${Project_O_SOURCE_DIR}/build CACHE STRING "Output directories for built executables")

#Generate executable
#ADD_EXECUTABLE(
#	Project_0
#	${Project_0_SOURCE_DIR}/src/Project0
#	${Project_0_SOURCE_DIR}/src/Base
#	${Project_0_SOURCE_DIR}/src/BattleField
#	${Project_0_SOURCE_DIR}/src/Character_Base
#	${Project_0_SOURCE_DIR}/src/Daemons
#	${Project_0_SOURCE_DIR}/src/Input_Management
#	${Project_0_SOURCE_DIR}/src/Menus
#	${Project_0_SOURCE_DIR}/src/Monster_Base
#	${Project_0_SOURCE_DIR}/src/Monster_Factory
#	${Project_0_SOURCE_DIR}/src/Monsters
#	${Project_0_SOURCE_DIR}/src/Render_Engine	
#)




