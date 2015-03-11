#include "Camera.h"

#define PI 3.1415926535898f

Camera::Camera(const STPoint3& eye, const STVector3& up, const STPoint3& lookAt, float fovy, float aspect)
{
	this->eye = eye;
	this->up = up;
	this->lookAt = lookAt;
	this->fovy = PI*fovy/180.0f;
	this->aspect = aspect;

	w = lookAt - eye; w.Normalize();
	u = STVector3::Cross(up, w); u.Normalize();
	v = STVector3::Cross(w, u);
}

Ray Camera::GenerateRay(const STPoint3& pointOnImagePlane)
{
	STVector3 dir = pointOnImagePlane - eye;
	return Ray(eye, dir);
}