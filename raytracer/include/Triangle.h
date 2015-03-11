#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape
{
public:
	Triangle(const STPoint3& v1, const STPoint3& v2, const STPoint3& v3);

	bool Intersect(const Ray& ray, Intersection& intersection);

	STPoint3 v1, v2, v3;

private:


};

#endif TRIANGLE_H