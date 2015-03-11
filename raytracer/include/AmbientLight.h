#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "Light.h"

class AmbientLight : public Light
{
public:
	AmbientLight(const STColor3f& ambL);

	int Type() { return Light::Ambient; }
	STColor3f Intensity() { return ambL; }

private:
	STColor3f ambL;

};

#endif AMBIENTLIGHT_H