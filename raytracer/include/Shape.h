#ifndef SHAPE_H
#define SHAPE_H

#include "st.h"
#include "Ray.h"
#include "Intersection.h"

class Shape
{
public:
	virtual bool Intersect(const Ray& ray, Intersection& intersection) { return false; }

private:


};

#endif SHAPE_H