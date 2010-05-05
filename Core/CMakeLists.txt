CMAKE_MINIMUM_REQUIRED ( VERSION 2.6)
INCLUDE ( CMake/WkCMake.cmake )
WkCMakeDir ( CMake )

WkProject ( Core CXX)

WkDepends ( SigC++ REQUIRED )
WkBuild ( LIBRARY STATIC )

WkDoc()
WkSvn()

#TestBed

# From most basic feature to most advanced :
# Logger
WkTestBuild( TestLogger )
WkTestRun( Logger TestLogger )
# Time
WkTestBuild( TestTime )
WkTestRun( Time TestTime )
# Randomizer
WkTestBuild ( TestRandomizer )
WkTestRun ( Randomizer TestRandomizer )

#others... to organise...
WkTestBuild( TestError )
WkTestBuild( TestDbgMem )
WkTestRun( DbgMem TestDbgMem )
WkTestBuild( TestStaticAssert )
WkTestRun( StaticAssert TestStaticAssert )
WkTestBuild ( TestFunctor )
WkTestRun( Functor TestFunctor )
WkTestBuild ( TestCallback )
WkTestRun( Callback TestCallback )
WkTestBuild ( TestAdapter )
WkTestRun( Adapter TestAdapter )
