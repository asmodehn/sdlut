#include "MxSprite.h"
#include "MxScene.h"

namespace MxLib
{

    MxSprite::MxSprite (MxBitmap & bitmapOri , unsigned int coordOriX, unsigned int coordOriY, unsigned int size)
            : m_BitmapOri(bitmapOri)
    {
        m_bboxOri.setx(coordOriX);
        m_bboxOri.sety(coordOriY);
        m_bboxOri.setw(size);
        m_bboxOri.seth(size);
    }

    MxSprite::MxSprite (MxBitmap & bitmapOri, unsigned int coordOriX, unsigned int coordOriY, unsigned int sizeOriX, unsigned int sizeOriY)
            : m_BitmapOri(bitmapOri)
    {
        m_bboxOri.setx(coordOriX);
        m_bboxOri.sety(coordOriY);
        m_bboxOri.setw(sizeOriX);
        m_bboxOri.seth(sizeOriY);
    }

    bool MxSprite::collide (const SDL::Rect & intersection)
    {
        return false;
    }

    void MxSprite::update()
    {
        //TODO
    }

    bool MxSprite::move (int deltax, int deltay) const
    {
        m_scene->moveSprite(m_sceneindex,deltax,deltay);
    }

    bool MxSprite::render(int pixX, int pixY) const
    {
        return MxInit::getDisplay()->blit(*m_BitmapOri.getRawSurface(),SDL::Point(pixX,pixY),m_bboxOri);
    }


    MxAnimatedSprite::MxAnimatedSprite (MxBitmap & bitmapOri, unsigned int coordOriX, unsigned int coordOriY, unsigned int size)
            : MxSprite(bitmapOri, coordOriX, coordOriY, size), m_currentframe(0)
    {
        m_frame.push_back(m_bboxOri);
    }
    MxAnimatedSprite::MxAnimatedSprite (MxBitmap & bitmapOri, unsigned int coordOriX, unsigned int coordOriY, unsigned int sizeOriX, unsigned int sizeOriY)
            : MxSprite(bitmapOri, coordOriX, coordOriY, sizeOriX, sizeOriY), m_currentframe(0)
    {
        m_frame.push_back(m_bboxOri);
    }

    bool MxAnimatedSprite::collide (const SDL::Rect & intersection)
    {
        std::cout << intersection << std::endl;
        // move back as needed // TO IMPROVE
        if ( intersection.getw() < intersection.geth() )
            move ( - intersection.getw(), 0 );
        else
            move  ( 0 , - intersection.geth() );
        return true;
    }

    void MxAnimatedSprite::update()
    {
        //TODO
    }

    bool MxAnimatedSprite::render(int pixX, int pixY) const
    {
        return MxInit::getDisplay()->blit(*m_BitmapOri.getRawSurface(),SDL::Point(pixX,pixY),m_frame[m_currentframe]);
    }

}
