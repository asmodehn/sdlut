#ifndef CAMERA_HH
#define CAMERA_HH

#include "Config.hh"

#include "GraphicElement.hh"
#include "Layer.hh"

class Camera :  public GraphicElement //private to prevent access to base class methods handling referent...
{
	private:
		static std::vector<Camera*> cameraList;
		static std::vector<Vector2> positionList;
  
  unsigned int camID;
  
  public:
  Camera(const Vector2 & position = Vector2(0.0,0.0));
  
  static Camera * getCamera(unsigned int index);
  
  //overriding move : The Camera manage his own position
  bool move(const Vector2& deltap);
  
  //overriding render to handl camera position
  //camera usually in the midle of the screen
  void render(unsigned int myPixCenterX = 0, unsigned int myPixCenterY = 0);
};


#endif
