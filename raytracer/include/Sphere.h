#ifndef SPHERE_H
#define SPHERE_H

#include "Shape.h"

class Sphere : public Shape
{
public:
	Sphere(const STPoint3& center, float radius);

	bool Intersect(const Ray& ray, Intersection& intersection);

	STPoint3 center;
	float radius;

private:


};

#endif SPHERE_H