CMAKE_MINIMUM_REQUIRED ( VERSION 2.6)

INCLUDE ( CMake/WkBuild.cmake )
INCLUDE ( CMake/WkTest.cmake )
INCLUDE ( CMake/WkDoc.cmake )

WkProject ( Core CXX)

WkBuild ( LIBRARY STATIC )

WkDoc()

