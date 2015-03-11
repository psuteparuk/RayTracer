#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Light.h"

class DirectionalLight : public Light
{
public:
	DirectionalLight(const STVector3& dir, const STColor3f& dirL);

	STVector3 LightDirection(const STPoint3& pointOnSurface);
	int Type() { return Light::Directional; }
	STColor3f Intensity() { return dirL; }

private:
	STVector3 dir;
	STColor3f dirL;

};

#endif DIRECTIONALLIGHT_H