#ifndef INTENSITY_CALC_H
#define INTENSITY_CALC_H

#include <iostream>
#include <vector>
#include "objects.h"
using namespace std;

struct SurfaceK {
	float KR;
	float KG;
        float KB;

	SurfaceK(float kR, float kG, float kB): KR(kR), KG(kG), KB(kB) {}
};

struct Intensity {
	float IR;
	float IG;
	float IB;

	Intensity(): IR(0), IG(0), IB(0) {}
	Intensity(float iR, float iG, float iB): IR(iR), IG(iG), IB(iB) {}
	void intensityMulK(SurfaceK K) {
		IR *= K.KR; IG *= K.KG; IB *= K.KB;
	}
	
	Intensity operator+ (const Intensity& I) {
		Intensity Ir(IR, IG, IB);
		Ir.IR += I.IR;
		Ir.IG += I.IG;
		Ir.IB += I.IB;
		return Ir;
	}

	void print () {	
		cout << "Intensity: " << endl;
		cout << "R: " << IR << ", ";
		cout << "G: " << IG << ", ";
		cout << "B: " << IB << ", ";
		cout << endl;
	}
};

// For N light sources
Intensity intensityAtP (Intensity Ia, vector<Intensity> Is, vector<point> Ls, SurfaceK Ka, SurfaceK Kd, SurfaceK Ks, point pP, point pN, point pV, double ns);

// Due to single light source (Il,d + Il,s)
Intensity intensityAtP (Intensity Il, SurfaceK Ka, SurfaceK Kd, SurfaceK Ks, point pP, point pL, point pN, point pV, double ns);

#endif
