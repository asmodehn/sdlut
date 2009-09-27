CMAKE_MINIMUM_REQUIRED ( VERSION 2.6)

INCLUDE ( CMake/WkBuild.cmake )
INCLUDE ( CMake/WkTest.cmake )
INCLUDE ( CMake/WkDoc.cmake )

WkProject ( Guichan_SDLut_FE CXX)

WkDependsInclude ( SDLut REQUIRED )
WkDependsInclude ( Guichan REQUIRED )
WkBuild ( LIBRARY STATIC )
WkDependsLink ( SDLut )
WkDependsLink ( Guichan )

WkDoc()

WkTestBuild(sdlutaction action.hpp sdlutaction.cpp)
WkTestData(sdlutaction fixedfont.bmp )

WkTestBuild(sdluthelloworld helloworld.hpp sdluthelloworld.cpp)
WkTestData(sdluthelloworld fixedfont.bmp )

WkTestBuild(sdlutwidgets widgets.hpp sdlutwidgets.cpp)
WkTestData(sdlutwidgets fixedfont.bmp gui-chan.bmp darkbitslogo_by_haiko.bmp)
