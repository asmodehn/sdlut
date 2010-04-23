CMAKE_MINIMUM_REQUIRED ( VERSION 2.6)
INCLUDE ( CMake/WkCMake.cmake )
WkCMakeDir ( CMake )

WkProject ( SDLut CXX)

WkDepends ( Core REQUIRED )
WkDepends ( SDL REQUIRED )
WkDepends ( OpenGL )
WkDepends ( SDL_image)
WkDepends ( SDL_ttf)
WkDepends ( SDL_mixer)
WkDepends ( SDL_net)

WkBuild ( LIBRARY STATIC )

WkDoc()


WkTestBuild ( testRect "testRect.cc" "TestCommon.hh")

WkTestBuild ( SDLtestColor )

WkTestBuild ( testScreenBufferInit "testScreenBufferInit.cc" "TestCommon.hh" )

WkTestBuild ( testPixel "testPixel.cc" "TestCommon.hh")
WkTestRun   ( SDL_Pixel testPixel "nogl" )
WkTestRun   ( SDL_Pixel_Image_woAlpha testPixel "nogl" "data/test/transparency/png/pal_bk_notrns.png" )
WkTestRun   ( SDL_Pixel_Image_wAlpha testPixel "nogl" "data/test/transparency/png/pal_bk.png" )
WkTestRun   ( OpenGL_Pixel testPixel )
WkTestRun   ( OpenGL_Pixel_Image_woAlpha testPixel "data/test/transparency/png/pal_bk_notrns.png" )
WkTestRun   ( OpenGL_Pixel_Image_wAlpha testPixel "data/test/transparency/png/pal_bk.png" )

#WkTestBuild ( testScreenClipRect "testScreenClipRect.cc" "TestCommon.hh")

WkTestBuild ( testImageFormat "testImageFormat.cc" "testRendering.hh" "TestCommon.hh" )
WkTestRun   ( SDL_GIF testImageFormat "auto" "data/test/imageformat/ColorTest.gif" )
WkTestRun   ( SDL_JPEG testImageFormat "auto" "data/test/imageformat/ColorTest.jpg" )
WkTestRun   ( SDL_LBM testImageFormat "auto" "data/test/imageformat/ColorTest.lbm" )
WkTestRun   ( SDL_PCX testImageFormat "auto" "data/test/imageformat/ColorTest.pcx" )
WkTestRun   ( SDL_PNG testImageFormat "auto" "data/test/imageformat/ColorTest.png" )
WkTestRun   ( SDL_PNM testImageFormat "auto" "data/test/imageformat/ColorTest.pnm" )
WkTestRun   ( SDL_TGA testImageFormat "auto" "data/test/imageformat/ColorTest.tga" )
WkTestRun   ( SDL_TIFF testImageFormat "auto" "data/test/imageformat/ColorTest.tif" )

WkTestRun   ( OpenGL_GIF testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.gif" )
WkTestRun   ( OpenGL_JPEG testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.jpg" )
WkTestRun   ( OpenGL_LBM testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.lbm" )
WkTestRun   ( OpenGL_PCX testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.pcx" )
WkTestRun   ( OpenGL_PNG testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.png" )
WkTestRun   ( OpenGL_PNM testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.pnm" )
WkTestRun   ( OpenGL_TGA testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.tga" )
WkTestRun   ( OpenGL_TIFF testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.tif" )

WkTestBuild ( testTransparency "testTransparency.cc" "testRendering.hh" "TestCommon.hh")
WkTestRun   ( SDL_Palette_BG_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/pal_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( SDL_Palette_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/pal.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( SDL_32bits_BG_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba8_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( SDL_32bits_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba8.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( SDL_64bits_BG_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba16_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( SDL_64bits_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba16.png" "data/test/transparency/png/stripe.gif")

WkTestRun   ( OpenGL_Palette_BG_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/pal_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( OpenGL_Palette_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/pal.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( OpenGL_32bits_BG_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba8_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( OpenGL_32bits_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba8.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( OpenGL_64bits_BG_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba16_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( OpenGL_64bits_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba16.png" "data/test/transparency/png/stripe.gif")

WkTestBuild (testGrayscaleAlphaTransparency "testGrayscaleAlphaTransparency.cc" "testRendering.hh" "TestCommon.hh" )
WkTestRun (SDL_16bits_Gray_BG_Transparency testGrayscaleAlphaTransparency "nogl" "auto" "data/test/transparency/png/gray8a_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun (SDL_16bits_Gray_Transparency testGrayscaleAlphaTransparency "nogl" "auto" "data/test/transparency/png/gray8a.png" "data/test/transparency/png/stripe.gif")
WkTestRun (SDL_32bits_Gray_BG_Transparency testGrayscaleAlphaTransparency "nogl" "auto" "data/test/transparency/png/gray16a_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun (SDL_32bits_Gray_Transparency testGrayscaleAlphaTransparency "nogl" "auto" "data/test/transparency/png/gray16a.png" "data/test/transparency/png/stripe.gif")

WkTestRun (OpenGL_16bits_Gray_BG_Transparency testGrayscaleAlphaTransparency "auto" "data/test/transparency/png/gray8a_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun (OpenGL_16bits_Gray_Transparency testGrayscaleAlphaTransparency "auto" "data/test/transparency/png/gray8a.png" "data/test/transparency/png/stripe.gif")
WkTestRun (OpenGL_32bits_Gray_BG_Transparency testGrayscaleAlphaTransparency "auto" "data/test/transparency/png/gray16a_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun (OpenGL_32bits_Gray_Transparency testGrayscaleAlphaTransparency "auto" "data/test/transparency/png/gray16a.png" "data/test/transparency/png/stripe.gif")

WkTestBuild ( SDLtestPixelFormat )
WkTestRun   ( "PixelFormat" SDLtestPixelFormat )

WkTestBuild (SDLtestRefresh)
WkTestData  (SDLtestRefresh smiley.bmp)

WkTestBuild ( SDLtestApp )
WkTestBuild ( SDLtestDumbLoop )
WkTestBuild ( SDLtestver )

WkTestBuild ( SDLtestEvents )
WkTestBuild ( SDLtestManager )

#WkTestBuild ( SDLtestTimer )
#WkTestBuild ( SDLtestStressTimer )
#WkTestBuild ( SDLtestMutex )
#WkTestBuild ( SDLtestThread )
#WkTestBuild ( SDLtestStressThread )

WkTestBuild ( SDLtestVideo )
WkTestBuild ( SDLtestGL )
WkTestBuild ( SDLtestTextInput ) 

WkTestBuild ( SDLtestFont )


# Running Tests : Guidelines.
# Logical Order. for each different case of one test, the following tests should have multiple possibilities.
# For exemple, if the Screen SDL Init provides either 8, 16, 24 or 32 bits, the following Test Screen Blit, should be ran in either 8, 16, 24, 32 bits, which ever is working.
#
# Step 1 : SDL basic functions.
# From grounds and simple things to complex concepts
# - Test Color (Blue, red, yellow, etc.). Abstract, Logic only, no display
# - Test Rect ( default 1,1, size, widht, etc. ). Logic only, no display
# - Test Screen SDL Init ( setup, config, etc. ). Will test ScreenInfo mostly, as well as execution platform !!!
# - Test Screen Access. Will test Filling pixel and rectangle directly on screen (slow), and getPixel.
# - Test Screen Blit. Will test blitting of surfaces filled with color squares.
# - Test Screen Blit Alpha. Will test blitting of surfaces filled with color squares with alpha.
# - Test Surface Blit. Will test blitting of surfaces fill of one color, on another surface, and then displayed on screen.
# - Test Surface Blit Alpha. Will test blitting of surfaces fill of one color with alpha, on another surface, and then displayed on screen.
# - Test Image BMP Display ( loading and display ). Will test Image, mostly.
# - Test Screen Refresh. Will test ScreenBuffer, mostly.

# Step 1.5 : Performances in real life use cases with Step 1 tested features
# - Perf Screen Refresh
# - Perf Screen Refresh Alpha

# Step 2 : Testing optional, but very likely, extensions : OpenGL
# - Same tests as Step 1, all in OpenGL mode


# Step 2.5 : Performances in real life use cases with Step 2 tested features
#
# Step 3 : Testing optional, less likely, extensions. Need to group by dependency required
# - Image formats ( PNG, JPG, etc. ) Display SDL et GL. Will test ImageLoader a bit.
# - Fonts display , SDL et GL.
# - etc. 

#Step 4 : Testing complex situation, unexpected, that are known to cause problems sometimes, and for which none of the previous tests detect the failure
