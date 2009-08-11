#include "Video/Scene.hh"
#include "SDLConfig.hh"

namespace RAGE
{
namespace SDL
{

Scene::Scene(int width, int height)
        : m_width(width), m_height(height)
{
}

Scene::Scene( const Scene & s )
        : m_width(s.m_width),m_height(s.m_height)
{
    //TODO : copy hte content of the vector
    //we probably also need to copy the sprites..
    // -> deep copy
}

Scene::~Scene()
{
    //shall we here delete all sprites ???
    //TODO -> think about allocation strategy
}


bool Scene::setWidth(int width)
{
    m_width = width;
    return true;
}

bool Scene::setHeight(int height)
{
    m_height = height;
    return true;
}



bool Scene::add( Sprite * s)
{
    m_spritelist.push_back(s);
    return true; //todo
}

//This return the list of sprite that need to be displayed, with the correct screen coordinates and dimensions
std::vector<Sprite*> Scene::getRenderList() const
{
    std::vector<Sprite*> res;

    for ( unsigned int i=0; i<m_spritelist.size(); i++)
    {

        int posx = m_spritelist[i]->posX();
        int posy = m_spritelist[i]->posY();
//#ifdef DEBUG
        Log << nl << "X = " << posx << " Y= " << posy;
//#endif
        if ( ( posx > 0 && posx < m_width ) //TODO : correct this
                && ( posy>0 && posy< m_height ) ) //TODO : and that
        {
            res.push_back(m_spritelist[i]);
        }
    }
    return res;
}

//this methods sets in which order the sprites should be rendered.
void Scene::setRenderPriorityPolicy()
{
}





}//SDL

}//RAGE

