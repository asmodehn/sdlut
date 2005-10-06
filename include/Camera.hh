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
  
};


#endif
