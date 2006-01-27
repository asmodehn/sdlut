#include "Scene.hh"
namespace RAGE
{
    namespace AML
    {
        Scene::Scene()
        {
#ifdef DEBUG
            Log << nl << "Scene::Scene() called ";
#endif


#ifdef DEBUG

            Log << nl << "Scene::Scene() done ";
#endif

        }

        Scene::~Scene()
        {}

        bool Scene::init (int width, int height)
        {
            return true;
        }

        bool Scene::resize (int width, int height)
        {
            return true;
        }


        void Scene::put(Sprite * sprite)
        {
#ifdef DEBUG
            Log << nl << "Scene::put() called ... ";
#endif

            _spritelist.push_back(sprite);
#ifdef DEBUG

            Log << nl << "Scene::put() done. ";
#endif

        }

        bool Scene::render() const
        {
#if (DEBUG == 2)
            Log << nl << "Scene::render() called ..." << std::endl;
#endif

            bool res = true;
            for (std::list<Sprite*>::const_iterator it = _spritelist.begin() ; it != _spritelist.end() ; it++ )
            {
                res = res && (*it)->render(_screen);
            }

#if (DEBUG == 2)
            Log << nl << "Scene::render() done." << std::endl;
#endif

            return res;
        }

    }
}
