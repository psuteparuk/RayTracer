#ifndef RAY_H
#define RAY_H

#include "st.h"
#include "Intersection.h"

class Ray
{
public:
	Ray(const STPoint3& origin, const STVector3& direction);
	Ray(const STPoint3& origin, const STVector3& direction, float min, float max);

	STPoint3 GetPoint(float t) const;
	Ray GetReflection(const Intersection& intersection, float min, float max) const;
	Ray Transform(const STTransform4& transform) const;

	STPoint3 e;
	STVector3 d;
	float tmin, tmax;

private:

};

#endif RAY_H