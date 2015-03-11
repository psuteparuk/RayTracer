#ifndef CAMERA_H
#define CAMERA_H

#include "st.h"
#include "Ray.h"

class Camera
{
public:
	Camera() {};
	Camera(const STPoint3& eye, const STVector3& up, const STPoint3& lookAt, float fovy, float aspect);
	
	Ray GenerateRay(const STPoint3& pointOnImagePlane);

	STPoint3 eye;
	STVector3 up;
	STPoint3 lookAt;
	float fovy, aspect;

	STVector3 u, v, w;

private:

};

#endif CAMERA_H