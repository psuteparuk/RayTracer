#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "st.h"

struct Intersection
{
	inline Intersection();
	inline Intersection(float t, const STPoint3& intersect, const STVector3& normal);

	float t;
	STPoint3 intersect;
	STVector3 normal;
};

#include "Intersection.inl"

#endif INTERSECTION_H