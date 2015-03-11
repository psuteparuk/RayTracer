#include "Scene.h"
#include <fstream>
#include <sstream>

#define PI 3.1415926535898f

Scene::Scene(std::string sceneFilename)
{
	Parse(sceneFilename);
}

void Scene::Render()
{
	for (int x = 0; x < imgplane.GetImgWidth(); ++x) {
		for (int y = 0; y < imgplane.GetImgHeight(); ++y) {
			Ray ray = cam.GenerateRay(imgplane.GetLocation(x, y));
			imgplane.SetSample(x, y, Sample(TraceRay(ray, cam.eye, depth)));
		}
	}

	imgplane.Save(outputfile);
	clean();
}

STColor3f Scene::TraceRay(const Ray& ray, const STPoint3& origin, int depth)
{
	Intersection intersection;

	if (!Intersect(ray, intersection))
		return STColor3f(0.0f);

	STVector3 viewDir = origin - intersection.intersect;
	int index = scene->IndexHit(ray);
	STColor3f color = scene->material[index]->Shade(scene->shape, intersection, viewDir, light, bias, transformList);

	if (depth == 0)
		return color;

	if (scene->material[index]->mirr.r == 0.0f && scene->material[index]->mirr.g == 0.0f && scene->material[index]->mirr.b == 0.0f)
		return color;

	Ray reflect = ray.GetReflection(intersection, bias, std::numeric_limits<float>::infinity());
	return color + scene->material[index]->mirr * TraceRay(reflect, intersection.intersect, depth-1);
}

bool Scene::Intersect(const Ray& ray, Intersection& intersection)
{
	return scene->Intersect(ray, intersection);
}

void Scene::Parse(std::string sceneFilename)
{
	BeganParsing();

	std::ifstream sceneFile(sceneFilename.c_str());

	// Die if we couldn't find the file
	if (sceneFile.fail())
	{
		printf("Scene::Parse - Could not find input scene file '%s'\n", sceneFilename.c_str());
		exit(1);
	}

	char line[1024];
	while (!sceneFile.eof())
	{
		sceneFile.getline(line, 1023);
		std::stringstream ss;
		ss.str(line);
		std::string command;
		ss >> command;

		if (command == "Camera")
		{
			float ex, ey, ez, ux, uy, uz, lx, ly, lz, f, a;
			ss >> ex >> ey >> ez >> ux >> uy >> uz >> lx >> ly >> lz >> f >> a;
			STPoint3 eye(ex, ey, ez);
			STVector3 up(ux, uy, uz);
			STPoint3 lookAt(lx, ly, lz);
			ParsedCamera(eye, up, lookAt, f, a);
		}
		else
		if (command == "Output")
		{
			int w, h;
			std::string fname;
			ss >> w >> h >> fname;
			ParsedOutput(w, h, fname);
		}
		else
		if (command == "BounceDepth")
		{
			int depth;
			ss >> depth;
			ParsedBounceDepth(depth);
		}
		else if (command == "ShadowBias")
		{
			float bias;
			ss >> bias;
			ParsedShadowBias(bias);
		}
		else
		if (command == "PushMatrix")
		{
			ParsedPushMatrix();
		}
		else
		if (command == "PopMatrix")
		{
			ParsedPopMatrix();
		}
		else
		if (command == "Rotate")
		{
			float rx, ry, rz;
			ss >> rx >> ry >> rz;
			ParsedRotate(rx, ry, rz);
		}
		else
		if (command == "Scale")
		{
			float sx, sy, sz;
			ss >> sx >> sy >> sz;
			ParsedScale(sx, sy, sz);
		}
		else
		if (command == "Translate")
		{
			float tx, ty, tz;
			ss >> tx >> ty >> tz;
			ParsedTranslate(tx, ty, tz);
		}
		else
		if (command == "Sphere")
		{
			float cx, cy, cz, r;
			ss >> cx >> cy >> cz >> r;
			STPoint3 center(cx, cy, cz);
			ParsedSphere(center, r);
		}
		else
		if (command == "Triangle")
		{
			float x1, y1, z1, x2, y2, z2, x3, y3, z3;
			ss >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
			STPoint3 v[3];
			v[0] = STPoint3(x1, y1, z1);
			v[1] = STPoint3(x2, y2, z2);
			v[2] = STPoint3(x3, y3, z3);
			ParsedTriangle(v[0], v[1], v[2]);
		}
		else
		if (command == "AmbientLight")
		{
			float r, g, b;
			ss >> r >> g >> b;
			STColor3f col(r, g, b);
			ParsedAmbientLight(col);
		}
		else
		if (command == "PointLight")
		{
			float px, py, pz, r, g, b;
			ss >> px >> py >> pz >> r >> g >> b;
			STPoint3 pos(px, py, pz);
			STColor3f col(r, g, b);
			ParsedPointLight(pos, col);
		}
		else
		if (command == "DirectionalLight")
		{
			float dx, dy, dz, r, g, b;
			ss >> dx >> dy >> dz >> r >> g >> b;
			STVector3 dir(dx, dy, dz);
			STColor3f col(r, g, b);
			ParsedDirectionalLight(dir, col);
		}
		else
		if (command == "Material")
		{
			float ra, ga, ba, rd, gd, bd, rs, gs, bs, rr, gr, br, shine;
			ss >> ra >> ga >> ba >> rd >> gd >> bd >> rs >> gs >> bs >> rr >> gr >> br >> shine;
			STColor3f amb(ra, ga, ba);
			STColor3f diff(rd, gd, bd);
			STColor3f spec(rs, gs, bs);
			STColor3f mirr(rr, gr, br);
			ParsedMaterial(amb, diff, spec, mirr, shine);
		}
	}
	sceneFile.close();

	FinishedParsing();
}

void Scene::BeganParsing()
{
	scene = new SceneObject();
	curshape = NULL;
	curmat = NULL;
	matrixStack.push(STTransform4::Identity());
}

void Scene::FinishedParsing()
{
	curshape = NULL;
	curmat = NULL;
	scene->transform = transformList;
}


void Scene::ParsedCamera(const STPoint3& eye, const STVector3& up, const STPoint3& lookAt, float fovy, float aspect)
{
	cam = Camera(eye, up, lookAt, fovy, aspect);
}

void Scene::ParsedOutput(int imgWidth, int imgHeight, const std::string& outputFilename)
{
	imgplane = ImagePlane(cam, imgWidth, imgHeight);
	outputfile = outputFilename;
}

void Scene::ParsedBounceDepth(int depth)
{
	this->depth = depth;
}

void Scene::ParsedShadowBias(float bias)
{
	this->bias = bias;
}

void Scene::ParsedPushMatrix()
{
	transform = matrixStack.top();
	matrixStack.push(transform);
}

void Scene::ParsedPopMatrix()
{
	matrixStack.pop();
}

void Scene::ParsedRotate(float rx, float ry, float rz)
{
	transform = matrixStack.top();
	transform *= STTransform4::Rotation(PI*rx/180.0f, PI*ry/180.0f, PI*rz/180.0f);
	matrixStack.pop();
	matrixStack.push(transform);
}

void Scene::ParsedScale(float sx, float sy, float sz)
{
	transform = matrixStack.top();
	transform *= STTransform4::Scaling(sx, sy, sz);
	matrixStack.pop();
	matrixStack.push(transform);
}

void Scene::ParsedTranslate(float tx, float ty, float tz)
{
	transform = matrixStack.top();
	transform *= STTransform4::Translation(tx, ty, tz);
	matrixStack.pop();
	matrixStack.push(transform);
}

void Scene::ParsedShape(Shape *shape)
{
	scene->shape.push_back(shape);
	curshape = shape;
	if (scene->shape.size() > scene->material.size()) {
		scene->material.push_back(curmat);
		matfreq[matfreq.size()-1]++;
	}
	transformList.push_back(matrixStack.top());
}

void Scene::ParsedSphere(const STPoint3& center, float radius)
{
	Shape *sphere = new Sphere(center, radius);
	ParsedShape(sphere);
}

void Scene::ParsedTriangle(const STPoint3& v1, const STPoint3& v2, const STPoint3& v3)
{
	Shape *triangle = new Triangle(v1, v2, v3);
	ParsedShape(triangle);
}

void Scene::ParsedAmbientLight(const STColor3f& col)
{
	Light *ambL = new AmbientLight(col);
	light.push_back(ambL);
}

void Scene::ParsedPointLight(const STPoint3& loc, const STColor3f& col)
{
	STPoint3 newloc = matrixStack.top() * loc;
	Light *pointL = new PointLight(newloc, col);
	light.push_back(pointL);
}

void Scene::ParsedDirectionalLight(const STVector3& dir, const STColor3f& col)
{
	STVector3 newdir = matrixStack.top() * dir;
	Light *dirL = new DirectionalLight(newdir, col);
	light.push_back(dirL);
}

void Scene::ParsedMaterial(const STColor3f& amb, const STColor3f& diff, const STColor3f& spec, const STColor3f& mirr, float shine)
{
	Material *mat = new Material(amb, diff, spec, mirr, shine);
	scene->material.push_back(mat);
	curmat = mat;
	if (matfreq.size() == 0)
		matfreq.push_back(1);
	else
		matfreq.push_back(matfreq[matfreq.size()-1]+1);
}

void Scene::clean()
{
	for (unsigned int i = 0; i < scene->shape.size(); ++i)
		delete scene->shape[i];

	for (unsigned int i = 0; i < matfreq.size(); ++i)
		delete scene->material[matfreq[i]-1];

	delete scene;

	for (unsigned int i = 0; i < light.size(); ++i)
		delete light[i];

	while (!matrixStack.empty())
		matrixStack.pop();
}