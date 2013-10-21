#include "intensityCalculation.h"

typedef point vector3;
Intensity intensityAtP (Intensity Ia, vector<Intensity> Is, vector<point> Ls, SurfaceK Ka, SurfaceK Kd, SurfaceK Ks, point pP, point pN, point pV, double ns) {
	// Ambient component
	Intensity I = Ia;
	I.intensityMulK (Ka);

	for(int i=0; i<Ls.size(); ++i) 
		I = I + intensityAtP (Is[i], Ka, Kd, Ks, pP, Ls[i], pN, pV, ns);

	return I;
}

Intensity intensityAtP (Intensity Il, SurfaceK Ka, SurfaceK Kd, SurfaceK Ks, point pP, point pL, point pN, point pV, double ns) {
	Intensity I;
	// Diffuse Component
	vector3 N(pN);
	N.normalize();

	pL = pL-pP;
	vector3 L(pL);
	L.normalize();

	double cosT = N.dot(L);
	if (cosT > 0.0) {
		Intensity Id = Il;
		Id.intensityMulK (Kd);

		SurfaceK kCosT (cosT, cosT, cosT);
		Id.intensityMulK (kCosT);
		
		I = I + Id;

		// Specular Diffusion
		pV = pV-pP;
		vector3 V(pV);
		pV.normalize();

		N.scale (2*cosT);
		vector3 R(N);
		R = R-L;

		double cosPhi = V.dot(R);
		if (cosPhi > 0.0) {
			Intensity Is = Il;
			Is.intensityMulK (Kd);

			cosPhi = pow(cosPhi, ns);
			SurfaceK kCosPhi (cosPhi, cosPhi, cosPhi);
			Is.intensityMulK (kCosPhi);

			I = I + Is;
		}
	}

	return I;
}

int main () {
	Intensity Ia(1.0,1.0,0.0), Il(0.0,1.0,1.0);
	SurfaceK Ka(0.01, 0.01, 0.2), Ks=Ka, Kd=Ka;
	double ns = 0.002;
	point p, l(0,0,10), v(4,0,0), n(1,1,1);

	vector<Intensity> Is(1,Il);
	vector<point> Ls(1,l);
	Intensity I = intensityAtP(Ia, Is, Ls, Ka, Kd, Ks, p, n, v, ns);

	I.print();
	return 0;
}
