#include "SceneObject.h"

bool SceneObject::Intersect(const Ray& ray, Intersection& intersection)
{
	int index = IndexHit(ray);

	if (index < 0)
		return false;

	Ray transformRay = ray.Transform(transform[index].Inverse());
	bool ret = shape[index]->Intersect(transformRay, intersection);
	intersection.intersect = transform[index] * intersection.intersect;
	intersection.normal = transform[index].Inverse().Transpose() * intersection.normal;

	return ret;
}

int SceneObject::IndexHit(const Ray& ray)
{
	Intersection intersection;
	float tmin = std::numeric_limits<float>::infinity();
	Shape *min_shape = NULL;
	int index = -1;

	for (unsigned int i = 0; i < shape.size(); ++i) {
		Ray transformRay = ray.Transform(transform[i].Inverse());
		if (shape[i]->Intersect(transformRay, intersection)) {
			if (intersection.t >= transformRay.tmin && intersection.t <= transformRay.tmax && intersection.t < tmin) {
				min_shape = shape[i];
				tmin = intersection.t;
				index = i;
			}
		}
	}

	return index;
}