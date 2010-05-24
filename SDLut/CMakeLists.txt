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

#WkTestBuild ( SDLtestPixelFormat )
#WkTestRun   ( "PixelFormat" SDLtestPixelFormat )

#WkTestBuild (SDLtestRefresh)
#WkTestData  (SDLtestRefresh smiley.bmp)

#WkTestBuild ( SDLtestApp )
#WkTestBuild ( SDLtestDumbLoop )

#WkTestBuild ( SDLtestEvents )
#WkTestBuild ( SDLtestManager )

#WkTestBuild ( SDLtestTimer )
#WkTestBuild ( SDLtestStressTimer )
#WkTestBuild ( SDLtestMutex )
#WkTestBuild ( SDLtestThread )
#WkTestBuild ( SDLtestStressThread )

WkTestBuild ( SDLtestVideo )
#WkTestBuild ( SDLtestGL )
#WkTestBuild ( SDLtestTextInput ) 

#WkTestBuild ( SDLtestFont )

#WkTestRun   ( SDL_Pixel testPixel "nogl" )
#WkTestRun   ( SDL_Pixel_Image_woAlpha testPixel "nogl" "data/test/transparency/png/pal_bk_notrns.png" )
#WkTestRun   ( SDL_Pixel_Image_wAlpha testPixel "nogl" "data/test/transparency/png/pal_bk.png" )

### Running Tests : Guidelines.
# Logical Order. for each different case of one test, the following tests should have multiple possibilities.
# For exemple, if the Screen SDL Init provides either 8, 16, 24 or 32 bits,
# the following Test Screen Blit, should be ran in either 8, 16, 24, 32 bits, which ever is working.
#
### Step 1 : SDL basic functions.
WkTestBuild ( testVersion "testVersion.cc" "TestCommon.hh" )
WkTestBuild ( testColor "testColor.cc" "TestCommon.hh" )
WkTestBuild ( testRect "testRect.cc" "TestCommon.hh")
WkTestBuild ( testScreenBufferInit "testScreenBufferInit.cc" "TestCommon.hh" )
#REMOVED WkTestBuild ( testScreenBGColor "testScreenBGColor.cc" "TestCommon.hh" )
WkTestBuild ( testScreenAccess "testScreenAccess.cc" "TestCommon.hh")
WkTestBuild ( testScreenClipRect "testScreenClipRect.cc" "TestCommon.hh")
WkTestBuild ( testScreenBlit "testScreenBlit.cc" "TestCommon.hh")
#WkTestBuild ( testImageFormat "testImageFormat.cc" "testRendering.hh" "TestCommon.hh" )
# From grounds and simple things to complex concepts
# - Test Library version access
WkTestRun( Version testVersion )
# - Test Color (Blue, red, yellow, etc.). Abstract, Logic only, no display
WkTestRun( Color testColor )
# - Test Rect ( default 1,1, size, width, etc. ). Logic only, no display
WkTestRun( Rect testRect )
# - Test Screen SDL Init ( setup, config, etc. ). Will test ScreenInfo mostly, as well as execution platform !!!
# TO UNCOMMENT when testing on separate machine / user, TODO for continuous integration... (Hudson ?)
# Will mess up desktop in fullscreen test
#WkTestRun (ScreenInit testScreenBufferInit "auto" "nogl" "640" "480" "8")
#WkTestRun (ScreenInit testScreenBufferInit "auto" "nogl" "640" "480" "16")
#WkTestRun (ScreenInit testScreenBufferInit "auto" "nogl" "640" "480" "24")
#WkTestRun (ScreenInit testScreenBufferInit "auto" "nogl" "640" "480" "32")
#WkTestRun (ScreenInit testScreenBufferInit "auto" "nogl" "800" "600" "8")
#WkTestRun (ScreenInit testScreenBufferInit "auto" "nogl" "800" "600" "16")
#WkTestRun (ScreenInit testScreenBufferInit "auto" "nogl" "800" "600" "24")
#WkTestRun (ScreenInit testScreenBufferInit "auto" "nogl" "800" "600" "32")
#WkTestRun (ScreenInit testScreenBufferInit "auto" "nogl" "1024" "768" "8")
#WkTestRun (ScreenInit testScreenBufferInit "auto" "nogl" "1024" "768" "16")
#WkTestRun (ScreenInit testScreenBufferInit "auto" "nogl" "1024" "768" "24")
#WkTestRun (ScreenInit testScreenBufferInit "auto" "nogl" "1024" "768" "32")
#WkTestRun (ScreenInit testScreenBufferInit "auto" "nogl" "1280" "1024" "8")
#WkTestRun (ScreenInit testScreenBufferInit "auto" "nogl" "1280" "1024" "16")
#WkTestRun (ScreenInit testScreenBufferInit "auto" "nogl" "1280" "1024" "24")
#WkTestRun (ScreenInit testScreenBufferInit "auto" "nogl" "1280" "1024" "32")

#Will test SDL advised video mode ( at desktop size ) -> harmless on user machine
WkTestRun (ScreenInit testScreenBufferInit "auto" "nogl")

# - Test Screen Access. Will test Filling pixel and rectangle directly on screen (slow), and getPixel.
WkTestRun (ScreenAccess testScreenAccess "auto" "nogl")

# - Test Screen Clipping.
WkTestRun (ScreenAccess_Clipping testScreenClipRect "auto" "nogl")

# - Test Screen Blit. Will test blitting of surfaces filled with color squares.
WkTestRun (ScreenBlit testScreenBlit "auto" "nogl")

# - Test Screen Blit Alpha. Will test blitting of surfaces filled with color squares with alpha.

# - Test Surface Access. Will test Filling pixel and rectnagle on a surface and then display on screen.
# - Test Surface Blit. Will test blitting of surfaces fill of one color, on another surface, and then displayed on screen.
# - Test Surface Blit Alpha. Will test blitting of surfaces fill of one color with alpha, on another surface, and then displayed on screen.

# - Test Image BMP Display ( loading and display ). Will test Image, mostly.
WkTestRun   ( SDL_BMP_Image testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.bmp" )
# - Test Screen Refresh. Will test ScreenBuffer, mostly.

# Step 1.5 : Performances in real life use cases with Step 1 tested features
# - Perf Screen Refresh
# - Perf Screen Refresh Alpha

# Step 2 : Testing optional, but very likely, extensions : OpenGL
# - Same tests as Step 1, all in OpenGL mode

WkTestRun (ScreenInit testScreenBufferInit "auto")
WkTestRun (ScreenAccess testScreenAccess "auto")
WkTestRun (ScreenAccess_Clipping testScreenClipRect "auto")
WkTestRun (ScreenBlit testScreenBlit "auto" )
WkTestRun ( OpenGL_BMP_Image testImageFormat "auto" "data/test/imageformat/ColorTest.bmp" )

# Step 2.5 : Performances in real life use cases with Step 2 tested features
#

# Step 3 : Testing optional, less likely, extensions. Need to group by dependency required
WkTestBuild ( testTransparency "testTransparency.cc" "testRendering.hh" "TestCommon.hh")
WkTestBuild (testGrayscaleAlphaTransparency "testGrayscaleAlphaTransparency.cc" "testRendering.hh" "TestCommon.hh" )
# - Image formats ( PNG, JPG, etc. ) Display SDL. Will test ImageLoader a bit.
WkTestRun   ( SDL_GIF_Image testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.gif" )
WkTestRun   ( SDL_JPEG_Image testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.jpg" )
WkTestRun   ( SDL_LBM_Image testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.lbm" )
WkTestRun   ( SDL_PCX_Image testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.pcx" )
WkTestRun   ( SDL_PNG_Image testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.png" )
WkTestRun   ( SDL_PNM_Image testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.pnm" )
WkTestRun   ( SDL_TGA_Image testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.tga" )
WkTestRun   ( SDL_TIFF_Image testImageFormat "auto" "nogl" "data/test/imageformat/ColorTest.tif" )
# - PNG Transparency Test
WkTestRun   ( SDL_Palette_BG_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/pal_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( SDL_Palette_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/pal.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( SDL_32bits_BG_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba8_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( SDL_32bits_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba8.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( SDL_64bits_BG_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba16_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( SDL_64bits_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba16.png" "data/test/transparency/png/stripe.gif")
# - PNG grayscale Transparency Test
WkTestRun (SDL_16bits_Gray_BG_Transparency testGrayscaleAlphaTransparency "nogl" "auto" "data/test/transparency/png/gray8a_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun (SDL_16bits_Gray_Transparency testGrayscaleAlphaTransparency "nogl" "auto" "data/test/transparency/png/gray8a.png" "data/test/transparency/png/stripe.gif")
WkTestRun (SDL_32bits_Gray_BG_Transparency testGrayscaleAlphaTransparency "nogl" "auto" "data/test/transparency/png/gray16a_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun (SDL_32bits_Gray_Transparency testGrayscaleAlphaTransparency "nogl" "auto" "data/test/transparency/png/gray16a.png" "data/test/transparency/png/stripe.gif")

# - Fonts display , SDL.
# - etc. 

#Step 4 : Testing same as Step 3, but render in GL
WkTestRun   ( OpenGL_GIF_Image testImageFormat "auto" "data/test/imageformat/ColorTest.gif" )
WkTestRun   ( OpenGL_JPEG_Image testImageFormat "auto" "data/test/imageformat/ColorTest.jpg" )
WkTestRun   ( OpenGL_LBM_Image testImageFormat "auto" "data/test/imageformat/ColorTest.lbm" )
WkTestRun   ( OpenGL_PCX_Image testImageFormat "auto" "data/test/imageformat/ColorTest.pcx" )
WkTestRun   ( OpenGL_PNG_Image testImageFormat "auto" "data/test/imageformat/ColorTest.png" )
WkTestRun   ( OpenGL_PNM_Image testImageFormat "auto" "data/test/imageformat/ColorTest.pnm" )
WkTestRun   ( OpenGL_TGA_Image testImageFormat "auto" "data/test/imageformat/ColorTest.tga" )
WkTestRun   ( OpenGL_TIFF_Image testImageFormat "auto" "data/test/imageformat/ColorTest.tif" )
# - PNG Transparency Test
WkTestRun   ( OpenGL_Palette_BG_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/pal_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( OpenGL_Palette_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/pal.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( OpenGL_32bits_BG_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba8_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( OpenGL_32bits_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba8.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( OpenGL_64bits_BG_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba16_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun   ( OpenGL_64bits_Transparency testTransparency "auto" "nogl" "data/test/transparency/png/rgba16.png" "data/test/transparency/png/stripe.gif")
# - PNG grayscale Transparency Test
WkTestRun (OpenGL_16bits_Gray_BG_Transparency testGrayscaleAlphaTransparency "auto" "data/test/transparency/png/gray8a_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun (OpenGL_16bits_Gray_Transparency testGrayscaleAlphaTransparency "auto" "data/test/transparency/png/gray8a.png" "data/test/transparency/png/stripe.gif")
WkTestRun (OpenGL_32bits_Gray_BG_Transparency testGrayscaleAlphaTransparency "auto" "data/test/transparency/png/gray16a_bk.png" "data/test/transparency/png/stripe.gif")
WkTestRun (OpenGL_32bits_Gray_Transparency testGrayscaleAlphaTransparency "auto" "data/test/transparency/png/gray16a.png" "data/test/transparency/png/stripe.gif")


#Step 5 : Testing complex situation, unexpected, that are known to cause problems sometimes, and for which none of the previous tests detect the failure

