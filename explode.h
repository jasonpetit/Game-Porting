//Created and designed by: Jason Petit
//All rights reserved
//Any duplication or use of this is prohibited unless authorized by: Jason Petit

//explode.h

#ifndef EXPLODE_H
#define EXPLODE_H

#include "MyDirectX.h"

using namespace std;

class Explode
{
public:
	bool Load();
	bool explode(float x, float y);
	void end();
};

#endif