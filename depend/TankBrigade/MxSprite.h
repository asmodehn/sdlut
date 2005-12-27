#if !defined(MX_SPRITE_H_)
#define MX_SPRITE_H_

#include "MxSDL.h"
#include <vector>

namespace MxLib
{

    class MxScene;

    class MxSprite
    {
        friend class MxScene;

    protected :
        MxScene * m_scene;
        int m_sceneindex;

        SDL::RGBSurface & m_BitmapOri;
        SDL::Rect m_bboxOri;

        bool m_collision;

				std::vector<SDL::Rect> m_frame;
        unsigned int m_currentframe;

        void setScene(MxScene * scene)
        {
            m_scene = scene;
        }
        void setSceneIndex(int index)
        {
            m_sceneindex = index;
        }

    public:
        MxSprite (SDL::RGBSurface & , unsigned int coordOriX, unsigned int coordOriY, unsigned int size);
        MxSprite (SDL::RGBSurface & , unsigned int coordOriX, unsigned int coordOriY, unsigned int sizeOriX, unsigned int sizeOriY);


        unsigned int loadFrame(unsigned int coordOriX, unsigned int coordOriY, unsigned int size)
        {
            m_frame.push_back(SDL::Rect(coordOriX,coordOriY, size, size));
            return m_frame.size() -1;
        }

        unsigned int loadFrame(unsigned int coordOriX, unsigned int coordOriY, unsigned int sizeOriX, unsigned int sizeOriY)
        {
            m_frame.push_back(SDL::Rect(coordOriX,coordOriY, sizeOriX, sizeOriY));
            return m_frame.size() -1;
        }

        bool changeFrame(unsigned int newframe)
        {
            if ( newframe < m_frame.size() )
                m_currentframe = newframe;
            else
                return false;
            return true;
        }

        bool render(int pixX, int pixY) const;

        bool move (int deltax, int deltay) const;

        virtual void update();
        virtual bool collide (const SDL::Rect & intersection);
        virtual bool bordercollide(void) {return true;}
        virtual bool collideActive(void) {return m_collision;}

    };

}
#endif
