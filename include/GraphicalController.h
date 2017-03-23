#pragma once

#include <iostream>

#include "scene.h"
#include "Utility.h"

class GraphicalController
{
public:
	GraphicalController();
	void init(int, int);
	void createMap(const aiScene*);
	~GraphicalController();
private:
	int windowWidth_;
	int windowHeight_;

	const aiScene* scene_;

	GL::Camera camera_;

	std::vector<pair<GLuint, GLuint>> meshes_;

	void createCamera();
	std::vector<GLuint>& compileShaders();
	std::pair<GLuint, GLuint> loadMesh(int);
	void createModel();
};
