/*
 * For comments regarding functions please see the header file.
 */

#include "guichan/widgets/widget_ImageSlider.hh"

namespace gcn
{

    ImageSlider::ImageSlider() : 
		myBGImage(NULL), myMarkerImage(NULL), BGIsInternalImage(false), MarkerIsInternalImage(false), marker_shift(0), markerValue(NULL)
    { /*Protected*/ }

	ImageSlider::ImageSlider(const std::string& marker_filename, double scaleStart, double scaleEnd) :
		myBGImage(NULL), myMarkerImage(NULL), BGIsInternalImage(false), MarkerIsInternalImage(true), marker_shift(0), markerValue(NULL)
	{
		myMarkerImage = Image::load(marker_filename);

		mDragged = false;

        mScaleStart = scaleStart;
        mScaleEnd = scaleEnd;

        setFocusable(true);
        setFrameSize(0);
        setValue(scaleStart);

		setMarkerLength(myMarkerImage->getHeight());
		setStepLength( static_cast<int>(scaleEnd  - scaleStart)/getMarkerLength() );

		setOrientation(HORIZONTAL);

		addMouseListener(this);
        addKeyListener(this);
	}
	 
	ImageSlider::ImageSlider(const std::string& bg_filename, const std::string& marker_filename, double scaleStart, double scaleEnd) :
		myBGImage(NULL), myMarkerImage(NULL), BGIsInternalImage(true), MarkerIsInternalImage(true), markerValue(NULL)
	{
		myBGImage = Image::load(bg_filename);
		myMarkerImage = Image::load(marker_filename);

		mDragged = false;

        mScaleStart = scaleStart;
        mScaleEnd = scaleEnd;

        setFocusable(true);
        setFrameSize(0);       
        setValue(scaleStart);

		setWidth(myBGImage->getWidth());
        setHeight(myBGImage->getHeight());

		setMarkerLength(myMarkerImage->getHeight());
		setStepLength( static_cast<int>(scaleEnd  - scaleStart)/getMarkerLength() );

		setOrientation(HORIZONTAL);

		marker_shift = myBGImage->getHeight()/2 - myMarkerImage->getHeight()/2; //we're horizontal !

		addMouseListener(this);
        addKeyListener(this);

	}
	
	ImageSlider::ImageSlider(const Image*& marker_image, double scaleStart, double scaleEnd) :
		myBGImage(NULL), myMarkerImage(marker_image), BGIsInternalImage(false), MarkerIsInternalImage(false), marker_shift(0), markerValue(NULL)
	{
		mDragged = false;

        mScaleStart = scaleStart;
        mScaleEnd = scaleEnd;

        setFocusable(true);
        setFrameSize(0);       
        setValue(scaleStart);

		setMarkerLength(myMarkerImage->getHeight());
		setStepLength( static_cast<int>(scaleEnd  - scaleStart)/getMarkerLength() );

		setOrientation(HORIZONTAL);

		addMouseListener(this);
        addKeyListener(this);
	}
	 
	ImageSlider::ImageSlider(const Image*& bg_image, const Image*& marker_image, double scaleStart, double scaleEnd) :
		myBGImage(bg_image), myMarkerImage(marker_image), BGIsInternalImage(false), MarkerIsInternalImage(false), markerValue(NULL)
	{
		mDragged = false;

        mScaleStart = scaleStart;
        mScaleEnd = scaleEnd;

        setFocusable(true);
        setFrameSize(0);       
        setValue(scaleStart);

		setWidth(myBGImage->getWidth());
        setHeight(myBGImage->getHeight());

		setMarkerLength(myMarkerImage->getHeight());
		setStepLength( static_cast<int>(scaleEnd  - scaleStart)/getMarkerLength() );

		setOrientation(HORIZONTAL);

		marker_shift = myBGImage->getHeight()/2 - myMarkerImage->getHeight()/2; //we're horizontal !

		addMouseListener(this);
        addKeyListener(this);
	}

    ImageSlider::~ImageSlider()
    {
        if (BGIsInternalImage)
        {
            delete myBGImage, myBGImage = NULL;
        }
		if (MarkerIsInternalImage)
        {
            delete myMarkerImage, myMarkerImage = NULL;
        }

		delete markerValue, markerValue = NULL;
    }

    void ImageSlider::setImageBG(const Image* image)
    {
        if (BGIsInternalImage)
        {
            delete myBGImage;
        }

        myBGImage = image;
        BGIsInternalImage = false;
    }   

    const Image* ImageSlider::getImageBG() const
    {
        return myBGImage;
    }

	void ImageSlider::setImageMarker(const Image* image)
    {
        if (MarkerIsInternalImage)
        {
            delete myMarkerImage;
        }

        myMarkerImage = image;
        myMarkerImage = false;
    }

	const Image* ImageSlider::getImageMarker() const
    {
        return myMarkerImage;
    }

  	void ImageSlider::draw(gcn::Graphics* graphics)
    {		
		//App_Logger << nl << getValue() << std::endl;

		if (myBGImage != NULL)
		{
			(getOrientation() == HORIZONTAL)
				? graphics->drawImage(myBGImage, myMarkerImage->getWidth()/2, 0)
				: graphics->drawImage(myBGImage, 0, myMarkerImage->getHeight()/2);
		}

        drawMarker(graphics);

		if (markerValue != NULL)
		{
			drawValueLabel(graphics);
		}
    }

    void ImageSlider::drawMarker(gcn::Graphics* graphics)
    {
		(getOrientation() == HORIZONTAL)
			? graphics->drawImage(myMarkerImage, getMarkerPosition(), marker_shift)
			: graphics->drawImage(myMarkerImage, marker_shift, (getHeight() - getMarkerLength()) - getMarkerPosition());
    }

	void ImageSlider::Display_Value_On_Marker(bool show /*=true*/)
	{
		if (show)
		{
			delete markerValue, markerValue = NULL;

			int to_convert = static_cast<int>(floor(this->getValue()+0.5));
			std::stringstream s;
			s << to_convert;

			markerValue = new Label( s.str() );
			dynamic_cast<gcn::Container*>( this->getParent() )->add(markerValue);
			markerValue->setVisible(true);
			markerValue->setAlignment(Graphics::CENTER);
		}
		else 
		{
			markerValue->setVisible(false);
			delete markerValue, markerValue = NULL;
		}
	}

	void ImageSlider::drawValueLabel(gcn::Graphics* graphics)
    {
		int to_convert = static_cast<int>(floor(this->getValue()+0.5));
		std::stringstream s;
		s << to_convert;

		markerValue->setCaption( s.str() );
		markerValue->adjustSize();
		
		//set position depending on orientation.
		//position is: slider position + marker position + positionned to the center of the marker
		(getOrientation() == HORIZONTAL)
		? markerValue->setPosition( this->getX() + getMarkerPosition()   + myMarkerImage->getWidth()/2 - markerValue->getWidth()/2,
									this->getY() + marker_shift   +  myMarkerImage->getHeight()/2 - markerValue->getHeight()/2)
		: markerValue->setPosition( this->getX() + marker_shift   + myMarkerImage->getWidth()/2 - markerValue->getWidth()/2,
									this->getY() + (getHeight() - getMarkerLength()) - getMarkerPosition()   + myMarkerImage->getHeight()/2 - markerValue->getHeight()/2);

    }

} //namespace
