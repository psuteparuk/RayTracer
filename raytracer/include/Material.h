#ifndef MATERIAL_H
#define MATERIAL_H

#include "st.h"
#include "Shape.h"
#include "Intersection.h"
#include "Light.h"

class Material
{
public:
	Material(const STColor3f& ambi, const STColor3f& diff, const STColor3f& spec, const STColor3f& mirr, float shine);

	STColor3f Shade(const std::vector<Shape *>& shape, const Intersection& intersection, const STVector3& viewdir, const std::vector<Light *>& light, float bias, const std::vector<STTransform4>& transform);

	STColor3f ambi, diff, spec, mirr;
	float shine;

private:


};

#endif MATERIAL_H