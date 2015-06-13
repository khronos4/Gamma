/*	Gamma - Generic processing library
        See COPYRIGHT file for authors and license information

        File Description: Header to present Gamma classes with minimum templating
*/

#ifndef SIMPLEGAMMA_H
#define SIMPLEGAMMA_H

#ifdef GAMMA_GAMMA_H_INC
#error "Gamma.h shouldn't be included if you plan to use SimpleGamma.h"
#endif

#define GAMMA_H_INC_ALL
#include "Gamma.h"

/// \defgroup SimpleGamma

/// \ingroup SimpleGamma

#ifndef SIMPLEGAMMA_FLOATS
#define NAMESPACE_NAME gamd
#define REAL double
#else
#define NAMESPACE_NAME gamf
#define REAL float
#endif

namespace NAMESPACE_NAME {

/// Sets the global sample rate for all Gamma generators and processors that
/// are not linked explicitly to a different Domain.
static void setGlobalSampleRate(double sampleRate)
{
    gam::sampleRate(sampleRate);
}


static bool startAudio(double sampleRate = 44100,
					   void (* callback)(gam::AudioIOData &) = 0,
					   void * userData = 0,
					   int framesPerBuf=64,
					   int outChannels = 2,
					   int inChannels = 0)
{
	static gam::AudioIO io_(framesPerBuf, sampleRate, callback, userData, outChannels, inChannels);
	setGlobalSampleRate(io_.framesPerSecond());
	return io_.start();
}


// From Gamma/Oscillator.h ----------------------------------------------
/// \ingroup SimpleGamma
class Accum: public gam::Accum<> {
public:
    Accum(REAL frq=0.0, REAL phs=0.0) : gam::Accum<>(frq, phs) {}
};

//typedef gam::Sweep<> Sweep;
//typedef gam::AccumPhase<> AccumPhase;
//typedef gam::CSine<> CSine;

/// \ingroup SimpleGamma
class Osc: public gam::Osc<REAL> {
public:
    Osc(REAL frq=440, REAL phs=0, uint32_t size=512) : gam::Osc<REAL>(frq, phs, size) {}
    Osc(REAL frq, REAL phs, ArrayPow2<REAL>& src) : gam::Osc<REAL>(frq, phs, src) {}
};

/// \ingroup SimpleGamma
class Sine: public gam::Sine<REAL> {
public:
    Sine(REAL frq = 440.0, REAL phs = 0.0) : gam::Sine<REAL>(frq, phs) {}
};

//typedef gam::SineR<> SineR;
//typedef gam::SineRs<> SineRs;
//typedef gam::SineD<> SineD;
//typedef gam::SineDs<> SineDs;
//typedef gam::Buzz<> Buzz;

class LFO: public gam::LFO<REAL> {
public:
	LFO(REAL frq = 440.0, REAL phs = 0.0, REAL mod = 0.5)
		: gam::LFO<REAL>(frq, phs, mod) {}
};

class Impulse: public gam::Impulse<REAL> {
public:
	Impulse(REAL frq = 440.0, REAL phs = 0.0) : gam::Impulse<REAL>(frq, phs) {}
};

class Saw: public gam::Saw<REAL> {
public:
	Saw(REAL frq = 440.0, REAL phs = 0.0) : gam::Saw<REAL>(frq, phs) {}
};

class Square: public gam::Square<REAL> {
public:
	Square(REAL frq = 440.0, REAL phs = 0.0) : gam::Square<REAL>(frq, phs) {}
};

class DSF: public gam::DSF<REAL> {
public:
	DSF(REAL frq=440, REAL freqRatio=1, REAL ampRatio=0.5, REAL harmonics=8) :
		gam::DSF<REAL>(frq, freqRatio, ampRatio, harmonics) {}
};

//typedef gam::ImpulseFast ImpulseFast;

// From Gamma/Delay.h -------------------------------------

class Delay: public gam::Delay<REAL, gam::ipl::Cubic  > {
public:
	Delay(REAL delay) :
		gam::Delay<REAL, gam::ipl::Cubic >(delay) {}
	Delay(REAL maxDelay, REAL delay) :
		gam::Delay<REAL, gam::ipl::Cubic >(maxDelay, delay) {}
};

class Delay1: public gam::Delay1<REAL> {
public:
	Delay1(REAL initialValue = 0.0) :
		gam::Delay1<REAL>(initialValue) {}
};

// From Gamma/Filter.h --------------------------------------
// TODO: Is res required in low pass, hi pass and all pass biquads here?
class LowPass: public gam::Biquad<REAL, REAL> {
public:
    LowPass(REAL frq = 1000.0, REAL res = 1.0) :
        gam::Biquad<REAL, REAL>(frq, res, gam::LOW_PASS) {}

};

class HiPass: public gam::Biquad<REAL, REAL> {
public:
	HiPass(REAL frq = 1000.0, REAL res = 1.0) :
		gam::Biquad<REAL, REAL>(frq, res, gam::HIGH_PASS) {}

};

class AllPass: public gam::Biquad<REAL, REAL> {
public:
	AllPass(REAL frq = 1000.0, REAL res = 1.0) :
		gam::Biquad<REAL, REAL>(frq, res, gam::ALL_PASS) {}

};



// From Gamma/Envelope.h -------------------------------------

class Curve : public gam::Curve<REAL, REAL> {
public:
	Curve() : gam::Curve<REAL, REAL>() {}
	Curve(REAL length, REAL curve, REAL start= 1.0, REAL end= 0.0) :
		gam::Curve<REAL, REAL>(length, curve, start, end)
	{}
};

class ADSR : public gam::ADSR<REAL, REAL> {
public:
    ADSR(REAL att = 0.01, REAL dec = 0.1, REAL sus = 0.7, REAL rel = 1.,
         REAL amp = 1.0, REAL crv = -4.0) :
        gam::ADSR<REAL, REAL>(att, dec, sus, rel, amp, crv) {}
};

// From Gamma/Noise.h ----------------------------------------

class NoiseWhite: public gam::NoiseWhite<> {
public:
    NoiseWhite() : gam::NoiseWhite<>() {} // TODO: should seed from current time
    NoiseWhite(uint32_t seed) : gam::NoiseWhite<>(seed) {}
};

/// \ingroup SimpleGamma
typedef gam::AudioDevice AudioDevice;

/// \ingroup SimpleGamma
typedef gam::AudioIO AudioIO;

/// \ingroup SimpleGamma
typedef gam::AudioIOData AudioIOData;

namespace rnd {
/// \ingroup SimpleGamma
using gam::rnd::pick;
}

namespace scl {
using gam::scl::clip;
}

/// \ingroup SimpleGamma
typedef gam::Domain Domain;
}


#endif // SIMPLEGAMMA_H

