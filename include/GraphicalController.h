#pragma once

#define GRAPHICALCONTROLLER_M_DEBUG
#define GRAPHICALCONTROLLER_M_DEBUG_SUPER
#undef GRAPHICALCONTROLLER_M_DEBUG_SUPER

#include <stdio.h>

#include <iostream>
#include <vector>
#include <list>

#include "scene.h"
#include "vector3.h"
#include "Utility.h"
#include "SOIL.h"

//GLuint - VAO, uint - mesh vertices count
typedef std::pair<GLuint, uint> MeshInfo;

typedef std::list<MeshInfo> VAOs;
//GLuint - texture index; VAOs - meshes VAO's
typedef std::pair<GLuint[2], VAOs> MaterialInfo;

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

	bool mouseCaptured_;
	void toggleMouse();

	const aiScene* scene_;

	GL::Camera camera_;

	std::vector<GLuint> textures_;
	GLuint texturesCount_;
	GLuint opacityTexCount_;
	GLuint opTexPointer_;
	std::vector<MaterialInfo> materials_;

	GLuint sponzaShaderOne_;
	GLuint sponzaShaderTwo_;

	int lastTime_;
	unsigned int frameCounter_;

	void createCamera();
	void updateFPS();
	void prepareTextures(GLuint);
	void unprepareTextures();
	void prepareProgram(GLuint);
	void loadTextures();
	bool loadTexture(const char*, GLuint&);
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
