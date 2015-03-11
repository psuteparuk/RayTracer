#include "Triangle.h"

Triangle::Triangle(const STPoint3& v1, const STPoint3& v2, const STPoint3& v3)
{
	this->v1 = v1;
	this->v2 = v2;
	this->v3 = v3;
}

bool Triangle::Intersect(const Ray& ray, Intersection& intersection)
{
	STVector3 ae = v1 - ray.e;
	STVector3 ab = v1 - v2;
	STVector3 ac = v1 - v3;

	float param = STVector3::Dot(ab, STVector3::Cross(ac, ray.d));
	float beta = STVector3::Dot(ae, STVector3::Cross(ac, ray.d)) / param;
	float gamma = STVector3::Dot(ab, STVector3::Cross(ae, ray.d)) / param;
	float t = STVector3::Dot(ab, STVector3::Cross(ac, ae)) / param;

	if (beta < 0.0f || gamma < 0.0f || (beta+gamma) > 1.0f)
		return false;

	if (t < ray.tmin || t > ray.tmax)
		return false;

	STPoint3 intersect = ray.GetPoint(t);
	STVector3 normal = STVector3::Cross(ab, ac);
	normal.Normalize();
	if (STVector3::Dot(ray.d, normal) > 0.0f)
		normal = -normal;

	intersection = Intersection(t, intersect, normal);

	return true;
}