#ifndef LIGHT_H
#define LIGHT_H

#include "st.h"

class Light
{
public:
	virtual STVector3 LightDirection(const STPoint3& pointOnSurface) { return STVector3(); }
	virtual int Type() { return 0; }
	virtual STColor3f Intensity() { return STColor3f(); }

	enum {
		Ambient = 1,
		Point,
		Directional
	};

private:


};

#endif LIGHT_H