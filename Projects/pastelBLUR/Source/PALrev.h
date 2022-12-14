/*
  ==============================================================================

    PALrev.h
    Created: 24 Jun 2022 3:11:11pm
    Author:  Peter Liley

  ==============================================================================
*/

#pragma once
#ifndef PALrev_h
#define PALrev_h


class PALrev {
public:
    PALrev(){}
    ~PALrev(){};
    
    /**
     Adds a sample to the reverberator and inserts two floats
     (left and right channels) into given return address as output.
     */
    inline void processSample(float samp, float* returnAddr) {
        // early reflections
        predelay.pushSample(samp);
        samp = predelay.getSample();
        samp *= bandwidth;
        samp += delayEarly.getSample() * 0.1; // tiny amount of early-stage feedback
        samp = highShelf2.processSample(samp); // control the highs on the early feedback
        samp = highShelf1.processSample(samp);
        samp = apf1.processSample(samp);
        samp = apf3.processSample(samp);
        samp = apf4.processSample(samp);
        samp = apf5.processSample(samp);
        samp = apf6.processSample(samp) * 0.5;
        samp = apf7.processSample(samp) * 0.3;
        samp = apf8.processSample(samp) * 0.2;
        delayEarly.pushSample(samp);


        // A PROCESSING SIDE
        float sampA = samp + (delayB2.getSample() * tankDecay);
        sampA = apfA1.processSample(sampA);
        delayA1.pushSample(sampA);
        sampA = delayA1.getSample();
        sampA = highShelfA1.processSample(sampA);
        sampA *= tankDecay;
        sampA = apfA2.processSample(sampA);
        delayA2.pushSample(sampA);

        // B PROCESSING SIDE
        float sampB = samp + (delayA2.getSample() * tankDecay);
        sampB = apfB1.processSample(sampB);
        delayB1.pushSample(sampB);
        sampB = delayB1.getSample();
        sampB = highShelfB1.processSample(sampB);
        sampB *= tankDecay;
        sampB = apfB2.processSample(sampB);
        delayB2.pushSample(sampB);


        // TAP REVERB TANK
        float accumulatorL = 0;
        accumulatorL = 0.6 * delayB1.tap(266);
        accumulatorL += 0.6 * delayB1.tap(2974);
        accumulatorL -= 0.6 * apfB2.tap(1913);
        accumulatorL += 0.6 * delayB2.tap(1996);
        accumulatorL -= 0.6 * delayA1.tap(1990);
        accumulatorL -= 0.6 * apfA2.tap(187);
        accumulatorL -= 0.6 * delayA2.tap(1066);
        returnAddr[0] = hpfR.processSample(accumulatorL) * level;

        float accumulatorR = 0;
        accumulatorR = 0.6 * delayA1.tap(353);
        accumulatorR += 0.6 * delayA1.tap(3627);
        accumulatorR -= 0.6 * apfA2.tap(1228);
        accumulatorR += 0.6 * delayA2.tap(2673);
        accumulatorR -= 0.6 * delayB1.tap(2111);
        accumulatorR -= 0.6 * apfB2.tap(335);
        accumulatorR -= 0.6 * delayB2.tap(121);
        returnAddr[1] = hpfL.processSample(accumulatorR) * level;
    }
    
    
    // SETTERS ==========================
    
    void setPredelayLength(float length) {
        predelay.setReadHeadDelay(length);
    }
    
    void setTankDecay(float decay) {
        jassert(decay <= 1 && decay >= 0);
        tankDecay = decay;
    }
    
    void setTankLengthFactor(float factor) {
        jassert(factor > 0);
        tankLengthFactor = factor;
    }
    
    void setLevel(float newLevel) {
        jassert(newLevel >= 0 && newLevel <= 1);
        level = newLevel;
    }
    
    // GETTERS ===========================
    
    int getPredelayLength() {
        return predelay.getMaxLatency();
    }
    
    float getTankDecay() {
        return tankDecay;
    }

    float getTankLengthFactor() {
        return tankLengthFactor;
    }
    
    float getLevel() {
        return level;
    }
    
    
private:
    
    CircularBufferLong predelay { 0.01f }; // predelay
    float tankLengthFactor = 1.0f; // coefficient of tank delay lengths
    float level = 1.0f; // output level
    float tankDecay = 0.6f; // tank decay coefficient
    float bandwidth = 0.5f; // basically 'gain in'
    
    float lowpassFreq = 1000.0f;
    // early stage filters
    HighShelfFilter highShelf1 { HighShelfFilter::BIQUAD, lowpassFreq, 1.0f, -9.0f };
    HighShelfFilter highShelf2 { HighShelfFilter::BIQUAD, 10000, 1.0f, -5.0f };
    // tank filters
    HighShelfFilter highShelfA1 { HighShelfFilter::BIQUAD, lowpassFreq, 1.0f, -9.0f };
    HighShelfFilter highShelfB1 { HighShelfFilter::BIQUAD, lowpassFreq, 1.0f, -9.0f };

    
    // filter for removing lows from output
    HPF hpfL { HPF::BIQUAD, 100, 1.0f };
    HPF hpfR { HPF::BIQUAD, 100, 1.0f };
    
    // early stage APFs
    AllPassFilter apf1 { 211, -0.75, 0.75 };
    AllPassFilter apf3 { 157, -0.75, 0.75 };
    AllPassFilter apf4 { 563, -0.625, 0.625 };
    AllPassFilter apf5 { 409, -0.625, 0.625 };
    AllPassFilter apf6 { 3361, -0.625, 0.625 };
    AllPassFilter apf7 { 7789, -0.625, 0.625 };
    AllPassFilter apf8 { 16741, -0.625, 0.625 };
    // tank APFs
    AllPassFilter apfA1 { 997 * 3, -0.7, 0.7, 0.5f, 24}; // modulated
    AllPassFilter apfA2 { 2663 * 3, -0.5, 0.5 };
    AllPassFilter apfB1 { 1327 * 3, -0.7, 0.7, 0.6f, 24 }; // modulated
    AllPassFilter apfB2 { 3931 * 3, -0.5, 0.5 };
    
    // early stage feedback line delay
    CircularBufferShort delayEarly { 34211 };
    
    // tank delays
    int delayA1Length = 6590;
    int delayA2Length = 5505;
    int delayB1Length = 6241;
    int delayB2Length = 4641;
    CircularBufferShort delayA1 { delayA1Length };
    CircularBufferShort delayA2 { delayA2Length };
    CircularBufferShort delayB1 { delayB1Length };
    CircularBufferShort delayB2 { delayB2Length };
};


#endif /* PALrev_h */
