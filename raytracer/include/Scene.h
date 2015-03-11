#ifndef SCENE_H
#define SCENE_H

#include "st.h"
#include "Camera.h"
#include "Ray.h"
#include "ImagePlane.h"
#include "Shape.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Intersection.h"
#include "Material.h"
#include "Light.h"
#include "AmbientLight.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SceneObject.h"

#include <vector>
#include <stack>

class Scene
{
public:
	Scene(std::string sceneFilename);

	void Render();
	STColor3f TraceRay(const Ray& ray, const STPoint3& origin, int depth);
	bool Intersect(const Ray& ray, Intersection& intersection);

private:

	/** Parsing helpers **/
	void Parse(std::string sceneFilename);
	void BeganParsing();
	void FinishedParsing();
	void ParsedCamera(const STPoint3& eye, const STVector3& up, const STPoint3& lookAt, float fovy, float aspect);
	void ParsedOutput(int imgWidth, int imgHeight, const std::string& outputFilename);
	void ParsedBounceDepth(int depth);
	void ParsedShadowBias(float bias);
	void ParsedPushMatrix();
	void ParsedPopMatrix();
	void ParsedRotate(float rx, float ry, float rz);
	void ParsedScale(float sx, float sy, float sz);
	void ParsedTranslate(float tx, float ty, float tz);
	void ParsedShape(Shape *shape);
	void ParsedSphere(const STPoint3& center, float radius);
	void ParsedTriangle(const STPoint3& v1, const STPoint3& v2, const STPoint3& v3);
	void ParsedAmbientLight(const STColor3f& col);
	void ParsedPointLight(const STPoint3& loc, const STColor3f& col);
	void ParsedDirectionalLight(const STVector3& dir, const STColor3f& col);
	void ParsedMaterial(const STColor3f& amb, const STColor3f& diff, const STColor3f& spec, const STColor3f& mirr, float shine);
	void clean();

	Camera cam;
	ImagePlane imgplane;
	std::string outputfile;
	SceneObject *scene;
	Shape *curshape;
	Material *curmat;
	std::vector<int> matfreq;
	std::vector<Light *> light;
	int depth;
	float bias;
	std::vector<STTransform4> transformList;
	std::stack<STTransform4> matrixStack;
	STTransform4 transform;
};


#endif SCENE_H

