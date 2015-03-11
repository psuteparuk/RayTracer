#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

class PointLight : public Light
{
public:
	PointLight(const STPoint3& src, const STColor3f& pointL);

	STVector3 LightDirection(const STPoint3& pointOnSurface);
	int Type() { return Light::Point; }
	STColor3f Intensity() { return pointL; }

private:
	STPoint3 src;
	STColor3f pointL;

};

#endif POINTLIGHT_H