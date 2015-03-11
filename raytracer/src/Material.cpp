#include "Material.h"
#include <assert.h>

Material::Material(const STColor3f& ambi, const STColor3f& diff, const STColor3f& spec, const STColor3f& mirr, float shine)
{
	this->ambi = ambi;
	this->diff = diff;
	this->spec = spec;
	this->mirr = mirr;
	this->shine = shine;
}

bool Shadow(const std::vector<Shape *>& shape, const Intersection& intersection, Light *l, float bias, const std::vector<STTransform4>& transform)
{
	float tmax = (l->Type() == Light::Point) ? 1.0f : std::numeric_limits<float>::infinity();
	Ray shadowRay = Ray(intersection.intersect, l->LightDirection(intersection.intersect), bias, tmax);
	Intersection block;

	for (unsigned int j = 0; j < shape.size(); ++j) {
		if (shape[j]->Intersect(shadowRay.Transform(transform[j].Inverse()), block))
			return true;
	}

	return false;
}

STColor3f Material::Shade(const std::vector<Shape *>& shape, const Intersection& intersection, const STVector3& viewdir, const std::vector<Light *>& light, float bias, const std::vector<STTransform4>& transform)
{
	STColor3f finalColor = STColor3f();

	for (unsigned int i = 0; i < light.size(); ++i) {
		assert(light[i]->Type() > 0);

		STColor3f ambientColor = STColor3f();
		STColor3f diffuseColor = STColor3f();
		STColor3f specularColor = STColor3f();

		if (light[i]->Type() == Light::Ambient) {
			ambientColor = ambi * light[i]->Intensity();
			finalColor += ambientColor;
		} else {
			STVector3 N = intersection.normal;
			N.Normalize();
			STVector3 L = light[i]->LightDirection(intersection.intersect);
			L.Normalize();
			float dot = STVector3::Dot(L, N);
			STVector3 R = 2.0f * dot * N - L;
			R.Normalize();
			STVector3 V = viewdir;
			V.Normalize();

			bool shadow = Shadow(shape, intersection, light[i], bias, transform);

			if (!shadow) {
				float diffCoef = max(dot, 0.0f);
				float specCoef = max(STVector3::Dot(R, V), 0.0f);

				diffuseColor = (diff * light[i]->Intensity()) * diffCoef;
				specularColor = (spec * light[i]->Intensity()) * powf(specCoef, shine) * specCoef;

				finalColor += diffuseColor + specularColor;
			}
		}
	}

	return finalColor;
}