#pragma once

#include <iostream>

#include "scene.h"
#include "Utility.h"

class GraphicalController
{
public:
	void init(int, int);
	void createMap(const aiScene*);
private:
	int windowWidth_;
	int windowHeight_;

	GL::Camera camera;

	void createCamera();
	void createModel(const aiScene*);
};
