#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <string>
#include <cmath>

#include <vector>

#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"


#define CLIENT_WIDTH 500
#define CLIENT_HEIGHT 800

#define MAXOBJECT 200

using namespace std;

class BoundingBox{
public:
	int left;
	int	top;
	int	right;
	int	bottom;
public:
	bool isCollision(BoundingBox boundingbox){
	
		if (left > boundingbox.right) return false;
		if	(right < boundingbox.left) return false;
		if	(bottom > boundingbox.top) return false;
		if	(top < boundingbox.bottom) return false;
		return true;
	}
};

enum class OBJECT_TYPE {
	OBJECT_BUILDING, OBJECT_CHARACTER,
	OBJECT_BULLET, OBJECT_ARROW
};

enum class TEAM_TYPE {
	TEAM_RED, TEAM_BLUE
};