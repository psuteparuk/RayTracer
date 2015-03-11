#include "ImagePlane.h"
#include <assert.h>

ImagePlane::ImagePlane(const Camera& cam, int width, int height)
{
	center = cam.eye + cam.w;

	halfPlaneHeight = tanf(cam.fovy/2.0f);
	halfPlaneWidth = tanf(cam.aspect*cam.fovy/2.0f);

	STVector3 halfU = halfPlaneWidth*cam.u;
	STVector3 halfV = halfPlaneHeight*cam.v;
	LL = center + halfU - halfV;
	LR = center - halfU - halfV;
	UL = center + halfU + halfV;
	UR = center - halfU + halfV;

	mWidth = width;
	mHeight = height;

	planeSamples = new Sample[mWidth*mHeight];
	img = new STImage(mWidth, mHeight);
}

STPoint3 ImagePlane::GetLocation(int x, int y)
{
	assert(x >= 0 && x < mWidth);
	assert(y >= 0 && y < mHeight);

	float wRatio = (1.0f*x + 0.5f) / (1.0f*mWidth);
	float hRatio = (1.0f*y + 0.5f) / (1.0f*mHeight);

	return STPoint3((1.0f-wRatio) * ((1.0f-hRatio)*STVector3(LL) + hRatio*STVector3(UL)) + wRatio * ((1.0f-hRatio)*STVector3(LR) + hRatio*STVector3(UR)));
}

STStatus ImagePlane::Save(const std::string& filename) const
{
	for (int x = 0; x < mWidth; ++x) {
		for (int y = 0; y < mHeight; ++y) {
			img->SetPixel(x, y, planeSamples[y*mWidth+x]);
		}
	}

	return img->Save(filename);
}

void ImagePlane::SetSample(int x, int y, Sample value)
{
	assert(x >= 0 && x < mWidth);
	assert(y >= 0 && y < mHeight);

	planeSamples[y*mWidth+x] = value;
}