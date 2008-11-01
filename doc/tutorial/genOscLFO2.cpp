/*	Gamma - Generic processing library
	See COPYRIGHT file for authors and license information
	
	Tutorial:		Generator/Oscillator/LFO
	Description:	Using an LFO as an amplitude and frequency envelope.	
*/

#include "tutorial.h"

Accum<> tmr(0.5,2);			// timer to switch between LFO types
NoiseWhite<> noise;			// source noise
LFO<> env(5,0,0.25);		// LFO as amplitude envelope
LFO<> osc(100, 0, 0.25);    // Oscillator for pitch modulation
LFO<> mod(0.5);				// modulator of envelope's modifier parameter
gen::Trigger cnt(10,10);	// counter for LFO type

bool modMode = false;		// True = amplitude modulation, False = Frequency Modulation

void audioCB(AudioIOData& io){

	for(uint32_t i=0; i<io.numFrames(); i++){
	
		if(tmr()){
			if(cnt()) 
			{
				modMode ^= true;			// increment LFO type, switch mod mode when wraps
				printf("\nMod mode: %s modulation\n", modMode? "Amp" : "Freq");
			}
		}
			
		env.mod(mod.cosU());	// modulate modifier parameter with unipolar cosine wave

		float s = 0.f;			// initialize current sample to zero

		switch(cnt.val){			
				
			// non-modifiable generators ordered from smooth to sharp:
			case  0: s = env.cosU();	break;	// unipolar cosine
			case  1: s = env.hann();	break;	// a computed hann window (inverted cosU)
			case  2: s = env.triU();	break;	// unipolar triangle
			case  3: s = env.upU();		break;  // unipolar upward ramp
			case  4: s = env.downU();	break;  // unipolar downward ramp
			case  5: s = env.sqrU();	break;	// unipolar square

			// modifiable generator ordered from smooth to sharp:
			case  6: s = env.pulseU();	break;	// Mix between upward ramp and downward ramp
			case  7: s = env.stairU();	break;	// Mix between a square and impulse. 
			case  8: s = env.line2U();	break;	// Mix between a ramp and a triangle
			case  9: s = env.up2U();	break;  // Mix between two ramps			
		}
		
		if(modMode){			// amplitude modulate noise with envelope
			s *= noise();
		}
		else{					   // frequency modulate oscillator with envelope
			osc.freq(s*400 + 200); // between 100 and 200 hz
			s = osc.cos();
		}
		
		io.out(0)[i] = io.out(1)[i] = s * 0.4f; // apply envelope to noise generator
	}
}


int main(int argc, char* argv[]){
	AudioIO io(256, 44100., audioCB, NULL, 2);
	Sync::master().spu(io.fps());
	
	io.start();
	printf("\nPress 'enter' to quit...\n"); getchar();
	return 0;
}
