#ifndef INTERSECTION_INL
#define INTERSECTION_INL

#include "Intersection.h"

inline Intersection::Intersection()
{
	t = 0.0f;
	intersect = STPoint3();
	normal = STVector3();
}

inline Intersection::Intersection(float t, const STPoint3& intersect, const STVector3& normal)
{
	this->t = t;
	this->intersect = intersect;
	this->normal = normal;
}

#endif INTERSECTION_INL