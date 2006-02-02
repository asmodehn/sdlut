
ADD_LIBRARY(	Rage_SDL
		SDLConfig.cc
		Logger.cc
		SDLApp.cc
		SDLWindow.cc
		SDLBaseSurface.cc
		SDLCDRom.cc
		SDLCursor.cc
		SDLVideoSurface.cc
		SDLCriticalEvent.cc
		SDLEvent.cc
		SDLEventManager.cc
		SDLKeyboard.cc
		SDLMouse.cc
		SDLJoystick.cc
		SDLGLManager.cc
		SDLGLSurface.cc
		SDLManager.cc
		SDLOverlay.cc
		SDLPixelFormat.cc
		SDLPoint.cc
		SDLRect.cc
		SDLRGBSurface.cc
		SDLVideoInfo.cc
	)


# installing main library
INSTALL_TARGETS(/. FILES Rage_SDL)
