/**
 * Widget ImageSlider 
 *
 * Author: Asmodehn's Corp <http://asmodehn.com> ; VERAN PC <http://veranpc.fr>
 */

#ifndef GCN_IMAGESLIDER_HH
#define GCN_IMAGESLIDER_HH

#include <math.h>

#include "../sdlut/sdlutdepends.hpp"

#include "guichan/image.hpp"
#include "guichan/imageloader.hpp"

#include "guichan/widgets/label.hpp"
#include "guichan/widgets/slider.hpp"
#include "guichan/widgets/container.hpp"

namespace gcn
{
    class Image; //fwd def

	class GCN_CORE_DECLSPEC ImageSlider : public gcn::Slider
    {
	protected:
		 /**
         * The image to display.
         */
        const Image *myBGImage, *myMarkerImage;
        
		/**
		 * Marker shift relative to BG.
		 * Initialy the middle of the marker is the same as the middle of the BG
		 * The shift is used regarding orientation
		 */
		int marker_shift;


        /**
         * True if the images has been loaded internally, false otherwise.
         * An image not loaded internally is not deleted in the class destructor.
         */
        bool BGIsInternalImage, MarkerIsInternalImage;

		/**
         * the maker value displayed as a label
         */
		gcn::Label *markerValue;

		/**
         * Default constructor
         */
        ImageSlider();

    public:

		/**
         * Constructor.
         *
         * @marker_filename The filename of the marker image to display. Must be a square image. The created Image is own by the ImageSlider and will be automatically deleted.
		 * @scaleStart The start value of the slider scale.
         * @scaleEnd The end value of the slider scale.
         */
        ImageSlider(const std::string& marker_filename, double scaleStart, double scaleEnd);

        /**
         * Full Constructor.
         *
         * @filename The filename of the image to display in slider's bg. The created Image is own by the ImageSlider and will be automatically deleted.
		 * @marker_filename The filename of the marker image to display. Must be a square image. The created Image is own by the ImageSlider and will be automatically deleted.
		 * @scaleStart The start value of the slider scale.
         * @scaleEnd The end value of the slider scale.
         */
        ImageSlider(const std::string& bg_filename, const std::string& marker_filename, double scaleStart, double scaleEnd);

        /**
         * Constructor.
         *
         * @marker_image The image to display as slider's marker. Must be a square image. 
		 * @scaleStart The start value of the slider scale.
         * @scaleEnd The end value of the slider scale.
         */
        ImageSlider(const Image*& marker_image, double scaleStart, double scaleEnd);
		
		/**
         * Full Constructor.
         *
         * @bg_image The image to display in slider's bg.
		 * @marker_image The image to display as slider's marker. Must be a square image.
		 * @scaleStart The start value of the slider scale.
         * @scaleEnd The end value of the slider scale.
         */
        ImageSlider(const Image*& bg_image, const Image*& marker_image, double scaleStart, double scaleEnd);

        /**
         * Destructor.
         */
        virtual ~ImageSlider();

        /**
         * Sets the BG image to display.
		 * Existing Image is freed automatically IF it was loaded internally.
         *
         * @param image The image to display.
         */
        void setImageBG(const Image* image);

        /**
         * Gets current BG image.
         *
         * @return The current image.
         */
        const Image* getImageBG() const;

		/**
         * Sets the Marker image to display. Must be a square image.
		 * Existing Image is freed automatically IF it was loaded internally.
         *
         * @param image The image to display.
         */
        void setImageMarker(const Image* image);

        /**
         * Gets current Marker image.
         *
         * @return The current image.
         */
        const Image* getImageMarker() const;


		inline void Set_Marker_Shift(int newmMarkerShift)
		{
			marker_shift = newmMarkerShift;
		}
		inline int& Get_Marker_Shift()
		{
			return marker_shift;
		}

        // Inherited from Widget
        virtual void draw(gcn::Graphics* graphics);

		/**
		 * If true, delete current marker label, create a new markerValue label w current value as Caption, add it to parent container of this widget
		 * If false, delete current marker label
		 *
		 * Warning : The widdget must be added to a container before calling this function !!
		 */
		void Display_Value_On_Marker(bool show = true);

    protected:       
		// Inherited from Slider
        virtual void drawMarker(gcn::Graphics* graphics);

		/**
		 * Display the value of this widget in top of the marker
		 */
        virtual void drawValueLabel(gcn::Graphics* graphics);
    };
}
#endif

