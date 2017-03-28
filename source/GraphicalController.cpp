#include "GraphicalController.h"
#include "PointerGraphicalController.h"

void GraphicalController::init(int windowWidth, int windowHeight)
{
	windowWidth_ = windowWidth;
	windowHeight_ = windowHeight;
	GraphicalControllerPointer = this;
	int argc = 1;
	char** argv = new char*[2];
	char name[] = PROJECT_NAME;
	argv[1] = 0;
	argv[0] = name;
	std::cout << "Initializing GLUT... " << std::flush;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitContextVersion(3, 3);
	glutInitWindowPosition(-1, -1);
	glutInitWindowSize(windowWidth_, windowHeight);
	glutCreateWindow(PROJECT_NAME);

	glutDisplayFunc(openGLFunctions::display);
	glutIdleFunc(openGLFunctions::idle);
	glutKeyboardFunc(openGLFunctions::keyboard);
	glutSpecialFunc(openGLFunctions::special);
	glutPassiveMotionFunc(openGLFunctions::mouseMove);
	glutReshapeFunc(openGLFunctions::reshape);

	mouseCaptured = false;
	glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
	glClearColor(0.8, 0.8, 1, 1);
	std::cout << "success" << std::endl;

	std::cout << "Initializing GLEW... " << std::flush;
	putenv((char*)"MESA_GL_VERSION_OVERRIDE=3.3COMPAT");
	glewExperimental = true;
	glewInit();
	std::cout << "success" << std::endl;
}

void openGLFunctions::display()
{
	GraphicalControllerPointer->display();
}

void GraphicalController::startLoop()
{
	glutMainLoop();
}

void GraphicalController::toggleMouse()
{
	mouseCaptured = !mouseCaptured;
	if (mouseCaptured)
	{
		glutWarpPointer(windowWidth_ / 2, windowHeight_ / 2);
		glutSetCursor(GLUT_CURSOR_NONE);
	} else
		glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
}

void openGLFunctions::keyboard(unsigned char key, int x, int y)
{
	GraphicalControllerPointer->keyboardFunc(key, x, y);
}

void GraphicalController::keyboardFunc(unsigned char key, int x, int y)
{
	if (key == 'q' || key == 27)
		shutdown();
	else if (key == 'w' || key == 'W')
		camera_.goForward(25.0);
	else if (key == 's' || key == 'S')
		camera_.goBack(25.0);
	else if (key == 'm' || key == 'M')
		toggleMouse();
}

void openGLFunctions::special(int key, int x, int y)
{
	GraphicalControllerPointer->specialFunc(key, x, y);
}

void GraphicalController::specialFunc(int key, int x, int y)
{
	if (key == GLUT_KEY_RIGHT)
		camera_.rotateY(0.02);
	else if (key == GLUT_KEY_LEFT)
		camera_.rotateY(-0.02);
	else if (key == GLUT_KEY_UP)
		camera_.rotateTop(-0.02);
	else if (key == GLUT_KEY_DOWN)
		camera_.rotateTop(0.02);
}

void openGLFunctions::mouseMove(int x, int y)
{
	GraphicalControllerPointer->mouseMove(x, y);
}

void GraphicalController::mouseMove(int x, int y)
{
	if (mouseCaptured)
	{
		int centerX = windowWidth_ / 2;
		int centerY = windowHeight_ / 2;
		if (x != centerX || y != centerY)
		{
			camera_.rotateY((x - centerX) / 1000.0f);
			camera_.rotateTop((y - centerY) / 1000.0f);
			glutWarpPointer(centerX, centerY);
		}
	}
}

void openGLFunctions::reshape(GLint newWidth, GLint newHeight)
{
	GraphicalControllerPointer->reshapeFunc(newWidth, newHeight);
}

void GraphicalController::reshapeFunc(GLint newWidth, GLint newHeight)
{
	glViewport(0, 0, newWidth, newHeight);
	windowWidth_ = newWidth;
	windowHeight_ = newHeight;

	camera_.screenRatio = static_cast<float>(windowWidth_) / windowHeight_;
}

void GraphicalController::display()
{
	glEnable(GL_DEPTH_TEST); CHECK_GL_ERRORS
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); CHECK_GL_ERRORS
	for (uint i = 0; i < scene_->mNumMaterials; i++)
	{
		ShaderInfo shader = shaders_[i];
		glUseProgram(shader.first); CHECK_GL_ERRORS
		GLuint cameraLocation = glGetUniformLocation(shader.first, "camera"); CHECK_GL_ERRORS
		glUniformMatrix4fv(cameraLocation, 1, GL_TRUE,
			camera_.getMatrix().data().data()); CHECK_GL_ERRORS
		for (VAOs::iterator iter = shader.second.begin();
			 iter != shader.second.end();
			 iter++)
		{
			glBindVertexArray(iter->first); CHECK_GL_ERRORS
			glDrawElements(GL_TRIANGLES, iter->second, GL_UNSIGNED_INT, 0); CHECK_GL_ERRORS
			glBindVertexArray(0); CHECK_GL_ERRORS
		}
		glUseProgram(0); CHECK_GL_ERRORS
	}
	glutSwapBuffers(); CHECK_GL_ERRORS
}

void openGLFunctions::idle()
{
	GraphicalControllerPointer->idle();
}

void GraphicalController::idle()
{
	glutPostRedisplay();
}

GraphicalController::GraphicalController()
{
}

GraphicalController::~GraphicalController()
{
}

void GraphicalController::createMap(const aiScene* scene)
{
	scene_ = scene;
	
	std::cout << "Setting camera... " << std::flush;
	createCamera();
	std::cout << "success" << std::endl;

	std::cout << "Loading model... " << std::flush;
	createModel();
	std::cout << "success" << std::endl;
}

void GraphicalController::createCamera()
{
	camera_.angle = 45.0f / 180.0f * M_PI;
	camera_.direction = VM::vec3(0, 0.3, -1);
	camera_.position = VM::vec3(0, 0.5, -0.5);
	camera_.screenRatio = static_cast<float>(windowWidth_) / windowHeight_;
	camera_.up = VM::vec3(0, 1, 0);
	camera_.zfar = 10000.0f;
	camera_.znear = 0.05f;
}

void GraphicalController::compileShaders()
{
	
/*
	for (uint i = 0; i < scene_->mNumMaterials; i++)
	{
		GLuint shader =
			GL::CompileShaderProgram(("mat" + std::to_string(i)).data());
		CHECK_GL_ERRORS
		VAOs listVAO;
		ShaderInfo info(shader, listVAO);
		shaders_.push_back(info);
	}
*/
}

std::vector<unsigned int> GraphicalController::concatFaces(aiMesh* mesh)
{
	std::vector<unsigned int> result;
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		if (mesh->mFaces[i].mNumIndices == 3)
		{
			for (unsigned int j = 0; j < mesh->mFaces[i].mNumIndices; j++)
				result.push_back(mesh->mFaces[i].mIndices[j]);
		} else if (mesh->mFaces[i].mNumIndices == 4)
		{
			unsigned int* indices = mesh->mFaces[i].mIndices;
			for (unsigned int j = 0; j < 3; j++)
				result.push_back(indices[j]);
			for (unsigned int j = 0; j < 3; j++)
				result.push_back(indices[j+1]);
		} else
			throw std::invalid_argument(
				std::to_string(mesh->mFaces[i].mNumIndices) +
				" vertices in a single face! Cant deal with it, aborting");
	}
	return result;
}

MeshInfo GraphicalController::loadMesh(int i, uint& length)
{
	std::pair<GLuint, int> result;
	uint shader = scene_->mMeshes[i]->mMaterialIndex;
	glGenVertexArrays(1, &result.first);
	glBindVertexArray(result.first);

	GLuint vertBuffer;
	aiVector3D* vertices = scene_->mMeshes[i]->mVertices;
	int vertLength = scene_->mMeshes[i]->mNumVertices;

	glGenBuffers(1, &vertBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * vertLength,
				 vertices, GL_STATIC_DRAW); CHECK_GL_ERRORS
	GLuint vertLocation = glGetAttribLocation(shaders_[shader].first, "point"); CHECK_GL_ERRORS
	glEnableVertexAttribArray(vertLocation); CHECK_GL_ERRORS
	glVertexAttribPointer(vertLocation, 3, GL_FLOAT, GL_FALSE, 0, 0); CHECK_GL_ERRORS

	GLuint facesBuffer;
	std::vector<unsigned int> faces = concatFaces(scene_->mMeshes[i]);
	length = faces.size();

	glGenBuffers(1, &facesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, facesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * faces.size(),
				 faces.data(), GL_STATIC_DRAW); CHECK_GL_ERRORS

	glBindVertexArray(0);
	
	result.second = shader;
	return result;
}

void GraphicalController::shutdown()
{
	glutDestroyWindow(glutGetWindow());
}

void GraphicalController::checkInfo()
{
	std::cout << "Checking what's loaded:" << std::endl;
	for (uint i = 0; i < scene_->mNumMaterials; i++)
	{
		std::cout << shaders_[i].first << ": ";
		for (VAOs::iterator iter = shaders_[i].second.begin();
			 iter != shaders_[i].second.end();
			 iter++)
		{
			std::cout << iter->first << ' ';
		}
		std::cout << std::endl;
	}
}

void GraphicalController::createModel()
{
	compileShaders();
	for (uint i = 0; i < scene_->mNumMeshes; i++)
	{
		uint length;
		MeshInfo meshInfo = loadMesh(i, length);
		uint index = meshInfo.second;
		meshInfo.second = length;
		shaders_[index].second.push_back(meshInfo);
	}
	#ifdef GRAPHICALCONTROLLER_M_DEBUG
	checkInfo();
	#endif
}
