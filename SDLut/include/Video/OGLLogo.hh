#ifndef OGLLOGO_HH
#define OGLLOGO_HH

/*******************************************************************************
 * Class implementing an OpenGL Logo
 ******************************************************************************/

#include "Logo.hh"

namespace RAGE
{
namespace SDL
{

class OGLLogo : public Logo
{

#ifdef WK_OPENGL_FOUND
//GLint to store the gllist index for the logo
int _glLogoList;

//defining a structur to store a material
struct Material{
 float ambient[3];
 float diffuse[3];
 float specular[3];
 float emission[3];
 float alpha;
 float phExp;
};

//Material for the Logo
static Material material;

// 1372 Vertices
static const float vertices [1372][3];

// 1338 Normals
static const float normals [1338][3];

// 2732 Triangles
static const short face_indices[2732][6];

void setMaterial(int mode,float *f,float alpha) const;


public:

	OGLLogo();
    virtual ~OGLLogo(){};


bool init();
bool render(VideoSurface & screen) const;




};

#else
/* OGLLogo is defined only if Built with OpenGL */
#endif // WK_OPENGL_FOUND



} //SDL
} //RAGE




#endif //OGLLOGO_HH

