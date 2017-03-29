#pragma once

#define GRAPHICALCONTROLLER_M_DEBUG

#include <iostream>
#include <vector>
#include <list>

#include "scene.h"
#include "vector3.h"
#include "Utility.h"
//GLuint - VAO, int - index in shaders_
typedef std::pair<GLuint, uint> MeshInfo;
//GLuint - VAO, int - index in mMeshes
typedef std::list<MeshInfo> VAOs;
//GLuint - shader index; list<GLuint> - meshes VAO's
typedef std::pair<GLuint, VAOs> MaterialInfo;

class GraphicalController
{
public:
	GraphicalController();
	void init(int, int);
	void createMap(const aiScene*);
	void shutdown();
	void specialFunc(int, int, int);
	void keyboardFunc(unsigned char, int, int);
	void mouseMove(int, int);
	void reshapeFunc(GLint, GLint);
	void display();
	void idle();
	void startLoop();
	~GraphicalController();
private:
	int windowWidth_;
	int windowHeight_;

	bool mouseCaptured;
	void toggleMouse();

	const aiScene* scene_;

	GL::Camera camera_;

	std::vector<MaterialInfo> materials_;

	GLuint sponzaShader_;

	void createCamera();
	void compileShaders();
	std::vector<unsigned int> concatFaces(aiMesh*);
	MeshInfo loadMesh(int, uint&);
	void checkInfo();
	void createModel();
};
//openGL forbids passing pointers to functions that are class members
namespace openGLFunctions
{
	void display();
	void idle();
	void keyboard(unsigned char, int, int);
	void special(int, int, int);
	void mouseMove(int, int);
	void reshape(GLint, GLint);
}
