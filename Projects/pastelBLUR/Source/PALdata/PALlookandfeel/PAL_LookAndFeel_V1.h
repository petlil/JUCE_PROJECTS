/*
  ==============================================================================

    PAL_LookAndFeel_V1.h
    Created: 5 May 2022 10:16:04pm
    Author:  Peter Liley

  ==============================================================================
*/

#include <JuceHeader.h>

#pragma once

class PAL_LookAndFeel_V1 : public LookAndFeel_V4
{
public:
    
    enum PastelColours {
        PALE_BLUE = 0xffbcd0ff,
        DARK_BLUE = 0xffb7c0ff,
        DARK_PURPLE = 0xff806ba0,
        LIGHT_PURPLE = 0xffc8b6ff,
        DARK_PINK = 0xffe8c6ff,
        LIGHT_PINK = 0xffffd7ff,
        DARK_DARK_PURPLE = 0xff63607c
    };
    
    
    void drawLinearSlider (Graphics& g, int x, int y, int width, int height,
                                           float sliderPos,
                                           float minSliderPos,
                                           float maxSliderPos,
                                           const Slider::SliderStyle style, Slider& slider)
    {
        if (slider.isBar())
        {
            g.setColour (slider.findColour (Slider::trackColourId));
            g.fillRect (slider.isHorizontal() ? Rectangle<float> (static_cast<float> (x), (float) y + 0.5f, sliderPos - (float) x, (float) height - 1.0f)
                                              : Rectangle<float> ((float) x + 0.5f, sliderPos, (float) width - 1.0f, (float) y + ((float) height - sliderPos)));
        }
        else
        {
            
            // DEBUGGING RECTANGLE
//            g.setColour(Colours::aqua);
//            g.fillRect(x, y, width, height);
            
            // set the style depending on whether the slider is 1, 2 or 3-point
            auto isTwoVal   = (style == Slider::SliderStyle::TwoValueVertical   || style == Slider::SliderStyle::TwoValueHorizontal);
            auto isThreeVal = (style == Slider::SliderStyle::ThreeValueVertical || style == Slider::SliderStyle::ThreeValueHorizontal);

            // width of track is the smallest out of 1/4 of the slider box width and 6 pixels
            auto trackWidth = jmin (6.0f, slider.isHorizontal() ? (float) height * 0.25f : (float) width * 0.25f);

            // the start point is at one end of the box, halfway across the box
            Point<float> startPoint (slider.isHorizontal() ? (float) x : (float) x + (float) width * 0.5f,
                                     slider.isHorizontal() ? (float) y + (float) height * 0.5f : (float) (height + y));

            // the end point is the opposite end, bounded by size
            Point<float> endPoint (slider.isHorizontal() ? (float) (width + x) : startPoint.x,
                                   slider.isHorizontal() ? startPoint.y : (float) y);
            
            // instead of a track, draw the background track image:
            auto trackBackgroundImage = juce::ImageCache::getFromMemory (BinaryData::Slider_bg_png, BinaryData::Slider_bg_pngSize)
                                                .rescaled((width / 16) * 4, height, Graphics::ResamplingQuality::lowResamplingQuality);
            
            // iamge offset (for layout)
            int io = trackBackgroundImage.getWidth() / 2;
            
            g.drawImage(trackBackgroundImage,
                        x + (width / 2) - io,
                        y,
                        trackBackgroundImage.getWidth(),
                        trackBackgroundImage.getHeight(),
                        0, 0, trackBackgroundImage.getWidth(), trackBackgroundImage.getHeight());

            Path valueTrack;
            
            Point<float> minPoint, maxPoint, thumbPoint;

            if (isTwoVal || isThreeVal)
            {
                minPoint = { slider.isHorizontal() ? minSliderPos : (float) width * 0.5f,
                             slider.isHorizontal() ? (float) height * 0.5f : minSliderPos };

                if (isThreeVal)
                    thumbPoint = { slider.isHorizontal() ? sliderPos : (float) width * 0.5f,
                                   slider.isHorizontal() ? (float) height * 0.5f : sliderPos };

                maxPoint = { slider.isHorizontal() ? maxSliderPos : (float) width * 0.5f,
                             slider.isHorizontal() ? (float) height * 0.5f : maxSliderPos };
            }
            else
            {
                auto kx = slider.isHorizontal() ? sliderPos : ((float) x + (float) width * 0.5f);
                auto ky = slider.isHorizontal() ? ((float) y + (float) height * 0.5f) : sliderPos;

                minPoint = startPoint;
                maxPoint = { kx, ky };
            }

            //auto thumbWidth = getSliderThumbRadius (slider);
            
            // draw the value image on top, selecting only the pixels below the slider position
            auto trackValueImage = juce::ImageCache::getFromMemory (BinaryData::Slider_track_png, BinaryData::Slider_track_pngSize)
                                            .rescaled((width / 16) * 4, height, Graphics::ResamplingQuality::lowResamplingQuality);
            
            g.drawImage(trackValueImage,
                        x + (width / 2) - io,
                        sliderPos,
                        trackValueImage.getWidth(),
                        trackValueImage.getHeight(),
                        0,
                        (int) sliderPos - 12,
                        trackValueImage.getWidth(),
                        trackValueImage.getHeight());

            
            // draw slider thumb
            if(!isTwoVal)
            {
                auto thumbImage = juce::ImageCache::getFromMemory (BinaryData::slider_thumb_png, BinaryData::slider_thumb_pngSize)
                                        .rescaled(width, (height / 102) * 4, Graphics::ResamplingQuality::lowResamplingQuality);
                g.drawImage(thumbImage, Rectangle<float> (static_cast<float> (thumbImage.getWidth()), static_cast<float> (thumbImage.getHeight())).withCentre (isThreeVal ? thumbPoint : maxPoint), RectanglePlacement::centred);
            }

            

            if (isTwoVal || isThreeVal)
            {
                auto sr = jmin (trackWidth, (slider.isHorizontal() ? (float) height : (float) width) * 0.4f);
                auto pointerColour = slider.findColour (Slider::thumbColourId);

                if (slider.isHorizontal())
                {
                    drawPointer (g, minSliderPos - sr,
                                 jmax (0.0f, (float) y + (float) height * 0.5f - trackWidth * 2.0f),
                                 trackWidth * 2.0f, pointerColour, 2);

                    drawPointer (g, maxSliderPos - trackWidth,
                                 jmin ((float) (y + height) - trackWidth * 2.0f, (float) y + (float) height * 0.5f),
                                 trackWidth * 2.0f, pointerColour, 4);
                }
                else
                {
                    drawPointer (g, jmax (0.0f, (float) x + (float) width * 0.5f - trackWidth * 2.0f),
                                 minSliderPos - trackWidth,
                                 trackWidth * 2.0f, pointerColour, 1);

                    drawPointer (g, jmin ((float) (x + width) - trackWidth * 2.0f, (float) x + (float) width * 0.5f), maxSliderPos - sr,
                                 trackWidth * 2.0f, pointerColour, 3);
                }
            }
        }
    }
    
    
    
    void drawRotarySlider (Graphics& g, int x, int y, int width, int height, float sliderPos,
                                           const float rotaryStartAngle, const float rotaryEndAngle, Slider& slider)
    {
        // debugging rectangle
//        g.setColour(Colours::aqua);
//        g.fillRect(x, y, width, height);
        
        
        // draw background image
        auto knobImage = juce::ImageCache::getFromMemory (BinaryData::knob_blue_noline_png, BinaryData::knob_blue_noline_pngSize)
                                    .rescaled(width, height, Graphics::ResamplingQuality::lowResamplingQuality);

//        DropShadow dropShadow { Colour(PastelColours::DARK_DARK_PURPLE), width / 2, Point<int>(width/10, height/10) };
//        dropShadow.drawForImage(g, knobImage);
        
        g.drawImage(knobImage,
                    x,
                    y,
                    knobImage.getWidth(),
                    knobImage.getHeight(),
                    0, 0, knobImage.getWidth(), knobImage.getHeight());

        
        

        // draw rectangle for pointer line
        // (code stolen from tutorials)
        // https://docs.juce.com/master/tutorial_look_and_feel_customisation.html
        auto bounds = Rectangle<int> (x, y, width, height).toFloat().reduced (10);
        auto radius = jmin (bounds.getWidth(), bounds.getHeight()) / 2.0f;
        auto centreX = (float) x + (float) width  * 0.5f;
        auto centreY = (float) y + (float) height * 0.5f;
        auto angle = rotaryStartAngle + sliderPos * (rotaryEndAngle - rotaryStartAngle);
        
        juce::Path p;
        auto pointerLength = radius * 0.6f;
        auto pointerThickness = height / 15;
        p.addRectangle (-pointerThickness * 0.5f, -radius * 1.2, pointerThickness, pointerLength);
        p.applyTransform (juce::AffineTransform::rotation (angle).translated (centreX, centreY));
        
        g.setColour (juce::Colour(PastelColours::DARK_PURPLE));
        g.fillPath (p);
    }
    
    /**
     Draw the borders and corners of the window.
     Scales to any window dimensions, and can be given a
     scale value to scale the borders (thicker or thinner)
     */
    void drawBorders(juce::Graphics& g, int windowWidth, int windowHeight, int scale) {
        
        // get side border image
        auto sideImg = juce::ImageCache::getFromMemory(BinaryData::box_side_png, BinaryData::box_side_pngSize)
                            .rescaled(4 * scale, 1 * scale, Graphics::ResamplingQuality::lowResamplingQuality);
        for(int y = 0; y < windowHeight; y++) {
            // right border
            g.drawImage(sideImg,
                        0,
                        y,
                        sideImg.getWidth(),
                        sideImg.getHeight(),
                        0, 0, sideImg.getWidth(), sideImg.getHeight());
            // left border
            g.drawImage(sideImg,
                        windowWidth - sideImg.getWidth(),
                        y,
                        sideImg.getWidth(),
                        sideImg.getHeight(),
                        0, 0, sideImg.getWidth(), sideImg.getHeight());
        }
        
        // get top / bottom border image
        auto topBtmImg = juce::ImageCache::getFromMemory(BinaryData::box_top_png, BinaryData::box_top_pngSize)
                                .rescaled(1 * scale, 4 * scale, Graphics::ResamplingQuality::lowResamplingQuality);;
        for(int x = 0; x < windowWidth; x++) {
            // top border
            g.drawImage(topBtmImg,
                        x,
                        0,
                        topBtmImg.getWidth(),
                        topBtmImg.getHeight(),
                        0, 0, topBtmImg.getWidth(), topBtmImg.getHeight());
            
            // bottom border
            g.drawImage(topBtmImg,
                        x,
                        windowHeight - topBtmImg.getHeight(),
                        topBtmImg.getWidth(),
                        topBtmImg.getHeight(),
                        0, 0, topBtmImg.getWidth(), topBtmImg.getHeight());
        }
        
        auto cornerImage = juce::ImageCache::getFromMemory(BinaryData::corner_png, BinaryData::corner_pngSize)
                                .rescaled(7 * scale, 7 * scale, Graphics::ResamplingQuality::lowResamplingQuality);;
        
        // set up transforms constants for corner images
        AffineTransform transform;
        int centreX = (cornerImage.getWidth() * scale) / 2;
        int centreY = (cornerImage.getHeight() * scale) / 2;
        typedef MathConstants<float> math;
        
        // padding values for corner images
        int rightPadding = windowWidth - (cornerImage.getWidth() * scale);
        int bottomPadding = windowHeight - (cornerImage.getHeight() * scale);
        
        // draw corner image at top left
        transform = transform.rotation(0, centreX, centreY).translated(0, 0);
        g.drawImageTransformed(cornerImage, transform, false);
        
        // top right
        transform = transform.rotation(math::halfPi, centreX, centreY).translated(rightPadding, 0);
        g.drawImageTransformed(cornerImage, transform, false);
        
        // bottom left
        transform = transform.rotation(math::pi + math::halfPi, centreX, centreY).translated(0, bottomPadding);
        g.drawImageTransformed(cornerImage, transform, false);
        
        // bottom right
        transform = transform.rotation(math::pi, centreX, centreY).translated(rightPadding, bottomPadding);
        g.drawImageTransformed(cornerImage, transform, false);
        
    }
    
    /**
     Draws a box with givenn coordinates using pixel art image assets.
     */
    void drawBox(Graphics& g, int boxX, int boxY, int boxWidth, int boxHeight, int scale, PastelColours fill) {
        
        g.setColour(Colour(fill));
        g.fillRect(boxX, boxY, boxWidth, boxHeight);
        
        // get side border image
        auto sideImg = juce::ImageCache::getFromMemory(BinaryData::box_side_png, BinaryData::box_side_pngSize)
                            .rescaled(4 * scale, 1 * scale, Graphics::ResamplingQuality::lowResamplingQuality);
        for(int y = boxY; y < boxY + boxHeight; y += scale) {
            // right border
            g.drawImage(sideImg,
                        boxX,
                        y,
                        sideImg.getWidth(), //SPEEDUP
                        sideImg.getHeight(),
                        0, 0, sideImg.getWidth(), sideImg.getHeight());
            // left border
            g.drawImage(sideImg,
                        boxX + boxWidth - sideImg.getWidth(),
                        y,
                        sideImg.getWidth(),
                        sideImg.getHeight(),
                        0, 0, sideImg.getWidth(), sideImg.getHeight());
        }
        
        // get top / bottom border image
        auto topBtmImg = juce::ImageCache::getFromMemory(BinaryData::box_top_png, BinaryData::box_top_pngSize)
                                .rescaled(1 * scale, 4 * scale, Graphics::ResamplingQuality::lowResamplingQuality);;
        for(int x = boxX; x < boxX + boxWidth; x += scale) {
            // top border
            g.drawImage(topBtmImg,
                        x,
                        boxY,
                        topBtmImg.getWidth(),
                        topBtmImg.getHeight(),
                        0, 0, topBtmImg.getWidth(), topBtmImg.getHeight());
            
            // bottom border
            g.drawImage(topBtmImg,
                        x,
                        boxY + boxHeight - topBtmImg.getHeight(),
                        topBtmImg.getWidth(),
                        topBtmImg.getHeight(),
                        0, 0, topBtmImg.getWidth(), topBtmImg.getHeight());
        }
        
        auto cornerImage = juce::ImageCache::getFromMemory(BinaryData::corner_png, BinaryData::corner_pngSize)
                                .rescaled(7 * scale, 7 * scale, Graphics::ResamplingQuality::lowResamplingQuality);;
        
        // set up transforms constants for corner images
        AffineTransform transform;
        int centreX = (cornerImage.getWidth() * scale) / 2;
        int centreY = (cornerImage.getHeight() * scale) / 2;
        typedef MathConstants<float> math;
        
        // padding values for corner images
        int rightPadding = boxWidth - (cornerImage.getWidth() * scale);
        int bottomPadding = boxHeight - (cornerImage.getHeight() * scale);
        
        // draw corner image at top left
        transform = transform.rotation(0, centreX, centreY).translated(boxX, boxY);
        g.drawImageTransformed(cornerImage, transform, false);
        
        // top right
        transform = transform.rotation(math::halfPi, centreX, centreY).translated(boxX + rightPadding, boxY);
        g.drawImageTransformed(cornerImage, transform, false);
        
        // bottom left
        transform = transform.rotation(math::pi + math::halfPi, centreX, centreY).translated(boxX, boxY + bottomPadding);
        g.drawImageTransformed(cornerImage, transform, false);
        
        // bottom right
        transform = transform.rotation(math::pi, centreX, centreY).translated(boxX + rightPadding, boxY + bottomPadding);
        g.drawImageTransformed(cornerImage, transform, false);
    }


    
    
private:
    
    
    
};
