#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "st.h"
#include "Shape.h"
#include "Material.h"

class SceneObject
{
public:
	bool Intersect(const Ray& ray, Intersection& intersection);
	int IndexHit(const Ray& ray);

	std::vector<Shape *> shape;
	std::vector<Material *> material;
	std::vector<STTransform4> transform;

private:


};

#endif SCENEOBJECT_H