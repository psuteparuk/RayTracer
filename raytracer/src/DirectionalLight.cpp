#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(const STVector3& dir, const STColor3f& dirL)
{
	this->dir = dir;
	this->dirL = dirL;
}

STVector3 DirectionalLight::LightDirection(const STPoint3& pointOnSurface)
{
	return -dir;
}