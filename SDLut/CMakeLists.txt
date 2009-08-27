CMAKE_MINIMUM_REQUIRED ( VERSION 2.6)


INCLUDE ( CMake/WkBuild.cmake )
INCLUDE ( CMake/WkTest.cmake )
INCLUDE ( CMake/WkDoc.cmake )

WkProject ( SDLut CXX)

# this should be a dependency
INCLUDE_DIRECTORIES(${SDLut_SOURCE_DIR}/../Core/include )

WkDepends ( SDL REQUIRED )
WkDepends ( OpenGL )
WkDepends ( SDL_image)
WkDepends ( SDL_ttf)
WkDepends ( SDL_mixer)
WkDepends ( SDL_net)

WkBuild ( LIBRARY STATIC )

WkDependsLink ( SDL )
WkDependsLink ( OpenGL )
WkDependsLink ( SDL_image)
WkDependsLink ( SDL_ttf)
WkDependsLink ( SDL_mixer)
WkDependsLink ( SDL_net)

WkDoc()

WkTestBuild (SDLtestColor)
WkTestRun (SDLtestColor)

WkTestBuild (SDLtestScene)
WkTestRun (SDLtestScene)

