#ifndef IMAGEPLANE_H
#define IMAGEPLANE_H

#include "st.h"
#include "Camera.h"

typedef STColor4ub Sample;

class ImagePlane
{
public:
	ImagePlane() {};
	ImagePlane(const Camera &cam, int width, int height);

	STPoint3 GetLocation(int x, int y);
	int GetImgWidth() const { return mWidth; }
	int GetImgHeight() const { return mHeight; }
	STStatus Save(const std::string& filename) const;
	void SetSample(int x, int y, Sample value);

	STPoint3 LL, LR, UL, UR;

private:
	STPoint3 center;
	float halfPlaneWidth, halfPlaneHeight;
	int mWidth, mHeight;
	Sample *planeSamples;
	STImage *img;

};

#endif IMAGEPLANE_H