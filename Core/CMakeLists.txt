CMAKE_MINIMUM_REQUIRED ( VERSION 2.6)
INCLUDE ( CMake/WkCMake.cmake )
WkCMakeDir ( CMake )

WkProject ( Core CXX)

WkDependsInclude ( SigC++ REQUIRED )

WkBuild ( LIBRARY STATIC )

WkDependsLink ( SigC++ REQUIRED )
WkLink()

WkDoc()

WkTestBuild( TestDbgMem )
WkTestBuild( TestLogger )
WkTestBuild( TestStaticAssert )
WkTestBuild( TestTime )
WkTestBuild ( TestFunctor )
WkTestBuild ( TestCallback )
WkTestBuild ( TestAdapter )


