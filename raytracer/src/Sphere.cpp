#include "Sphere.h"

Sphere::Sphere(const STPoint3& center, float radius)
{
	this->center = center;
	this->radius = radius;
}

bool Sphere::Intersect(const Ray& ray, Intersection& intersection)
{
	STVector3 ec = ray.e - center;
	
	float dot = STVector3::Dot(ray.d, ec);
	float dLenSq = ray.d.LengthSq();
	float ecLenSq = ec.LengthSq();

	float disc = dot*dot - dLenSq*(ecLenSq - radius*radius);

	if (disc < 0.0f)
		return false;

	float t1 = (- dot - sqrt(disc)) / dLenSq;
	float t2 = (- dot + sqrt(disc)) / dLenSq;

	if (t2 < ray.tmin || t1 > ray.tmax)
		return false;

	float t = (t1 < ray.tmin) ? t2 : t1;

	STPoint3 intersect = ray.GetPoint(t);
	STVector3 normal = intersect - center;
	normal.Normalize();

	intersection = Intersection(t, intersect, normal);

	return true;
}