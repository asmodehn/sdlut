#ifndef CAMERA_HH
#define CAMERA_HH

#include "Config.hh"

#include "GraphicElement.hh"

class Camera : public GraphicElement
{
	private:
		static std::vector<Camera*> cameraList;
  
  public:
  Camera(void);
  
  static Camera * getCamera(unsigned int index);
  
  #ifdef USE_DEPEND_SDLwrap
	
	void setRenderArea( SDLBaseSurface * _graphic );
	
	#else 
	#error "No library defined to handle 2D graphics"
  #endif

};


#endif
