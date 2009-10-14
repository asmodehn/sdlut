CMAKE_MINIMUM_REQUIRED ( VERSION 2.6)
INCLUDE ( CMake/WkCMake.cmake )
WkCMakeDir ( CMake )

WkProject ( SDLut CXX)

# this should be a dependency
#INCLUDE_DIRECTORIES(${SDLut_SOURCE_DIR}/../Core/include )

WkDependsInclude ( Core REQUIRED )
WkDependsInclude ( SDL REQUIRED )
WkDependsInclude ( OpenGL )
WkDependsInclude ( SDL_image)
WkDependsInclude ( SDL_ttf)
WkDependsInclude ( SDL_mixer)
WkDependsInclude ( SDL_net)

WkBuild ( LIBRARY STATIC )

WkDependsLink ( Core )
WkDependsLink ( SDL )
WkDependsLink ( OpenGL )
WkDependsLink ( SDL_image)
WkDependsLink ( SDL_ttf)
WkDependsLink ( SDL_mixer)
WkDependsLink ( SDL_net)

WkLink ()

WkDoc()

WkTestBuild (SDLtestColor)
WkTestRun (SDLtestColor)

WkTestBuild (SDLtestScene)
WkTestRun (SDLtestScene)

