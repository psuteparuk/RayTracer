#include "PointLight.h"

PointLight::PointLight(const STPoint3& src, const STColor3f& pointL)
{
	this->src = src;
	this->pointL = pointL;
}

STVector3 PointLight::LightDirection(const STPoint3& pointOnSurface)
{
	return src - pointOnSurface;
}