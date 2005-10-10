#ifndef CAMERA_HH
#define CAMERA_HH

#include "Config.hh"

#include "GraphicElement.hh"
#include "Layer.hh"

class Camera :  public GraphicElement
{
	private:
		static std::vector<Camera*> cameraList;
		static std::vector<Vector2> positionList;
  
  unsigned int camID;
  
  public:
  Camera(const Vector2 & position = Vector2(0.0,0.0));
  
  static Camera * getCamera(unsigned int index = 0);
  
  //overriding move : The Camera manage his own position
  bool move(const Vector2& deltap);
  
  //overriding render to handle camera position
  //camera usually in the middle of the screen
  void render(unsigned int myPixCenterX = 0, unsigned int myPixCenterY = 0);
};


#endif
