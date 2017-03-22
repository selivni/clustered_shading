#include "GraphicalController.h"

void GraphicalController::init(int windowWidth, int windowHeight)
{
	windowWidth_ = windowWidth;
	windowHeight_ = windowHeight;
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
	glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
	glClearColor(0.8, 0.8, 1, 1);
	std::cout << "success" << std::endl;

	std::cout << "Initializing GLEW... " << std::flush;
	putenv((char*)"MESA_GL_VERSION_OVERRIDE=3.3COMPAT");
	glewExperimental = true;
	glewInit();
	std::cout << "success" << std::endl;
}

void GraphicalController::createMap(const aiScene* scene)
{
	std::cout << "Setting camera... " << std::flush;
	createCamera();
	std::cout << "success" << std::endl;

	std::cout << "Loading model... " << std::flush;
	createModel(scene);
	std::cout << "success" << std::endl;
}

void GraphicalController::createCamera()
{
	camera.angle = 45.0f / 180.0f * M_PI;
	camera.direction = VM::vec3(0, 0.3, -1);
	camera.position = VM::vec3(0, 0, 0);
	camera.screenRatio = static_cast<float>(windowWidth_) / windowHeight_;
	camera.up = VM::vec3(0, 1, 0);
	camera.zfar = 50.0f;
	camera.znear = 0.05f;
}

void GraphicalController::createModel(const aiScene* scene)
{
	
}
