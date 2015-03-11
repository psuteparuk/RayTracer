#include "Ray.h"
#include <assert.h>

Ray::Ray(const STPoint3& origin, const STVector3& direction)
{
	e = origin;
	d = direction;
	tmin = 1.0f;
	tmax = std::numeric_limits<float>::infinity();
}

Ray::Ray(const STPoint3& origin, const STVector3& direction, float min, float max)
{
	e = origin;
	d = direction;
	tmin = min;
	tmax = max;
}

STPoint3 Ray::GetPoint(float t) const
{
	assert(t >= tmin && t <= tmax);
	return e + t*d;
}

Ray Ray::GetReflection(const Intersection& intersection, float min, float max) const
{
	STVector3 r = d - 2.0f * STVector3::Dot(d, intersection.normal) * intersection.normal;

	return Ray(intersection.intersect, r, min, max);
}

Ray Ray::Transform(const STTransform4& transform) const
{
	STPoint3 newe = transform * e;
	STVector3 newd = transform * d;

	return Ray(newe, newd, tmin, tmax);
}