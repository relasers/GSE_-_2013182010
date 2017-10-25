#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <iostream>
#include <cmath>

#include <vector>

#include "Dependencies\glew.h"
#include "Dependencies\freeglut.h"

#include "Renderer.h"


#define CLIENT_WIDTH 500
#define CLIENT_HEIGHT 500

#define MAXOBJECT 10
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