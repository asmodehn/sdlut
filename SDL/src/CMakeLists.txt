#adding with headers just to have them in generated projects
ADD_LIBRARY(	Rage_SDL ../include/SDL.hh
		SDLConfig.cc ../include/SDLConfig.hh
		Logger.cc ../include/Logger.hh
		SDLApp.cc ../include/SDLApp.hh
		SDLWindow.cc ../include/SDLWindow.hh
		SDLBaseSurface.cc ../include/SDLBaseSurface.hh
		SDLCDRom.cc ../include/SDLCDRom.hh
		SDLCursor.cc ../include/SDLCursor.hh
		SDLVideoSurface.cc ../include/SDLVideoSurface.hh
		SDLCriticalEvent.cc ../include/SDLCriticalEvent.hh
		SDLEvent.cc ../include/SDLEvent.hh
		SDLEventManager.cc ../include/SDLEventManager.hh
		SDLKeyboard.cc ../include/SDLKeyboard.hh
		SDLMouse.cc ../include/SDLMouse.hh
		SDLJoystick.cc ../include/SDLJoystick.hh
		SDLGLManager.cc ../include/SDLGLManager.hh
		SDLGLSurface.cc ../include/SDLGLSurface.hh
		SDLManager.cc ../include/SDLManager.hh
		SDLOverlay.cc ../include/SDLOverlay.hh
		SDLPixelFormat.cc ../include/SDLPixelFormat.hh
		SDLPoint.cc ../include/SDLPoint.hh
		SDLRect.cc ../include/SDLRect.hh
		SDLRGBSurface.cc ../include/SDLRGBSurface.hh
		SDLVideoInfo.cc ../include/SDLVideoInfo.hh
	)


# installing main library
INSTALL_TARGETS(/. FILES Rage_SDL)
