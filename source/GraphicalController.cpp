#include "GraphicalController.h"
#include "PointerGraphicalController.h"


const VM::vec3 LightsArray::waypoint[]=
{
	VM::vec3(1120, 250, -450),
	VM::vec3(-1200, 250, -450),
	VM::vec3(-1200, 250, 400),
	VM::vec3(1120, 250, 400),
	VM::vec3(832, 110, -220),
	VM::vec3(115, 484, 104),
	VM::vec3(-12, 617, -466),
	VM::vec3(-1246, 615, -431),
	VM::vec3(-1196, 627, -139),
	VM::vec3(-112, 1241, -42),
	VM::vec3(1117, 141, -32)/*,
	VM::vec3(),
	VM::vec3(),
	VM::vec3(),
	VM::vec3(),
	VM::vec3(),
	VM::vec3(),
	VM::vec3(),*/
};

const int LightsArray::wpSize = sizeof(waypoint) / sizeof(aiVector3D);

const unsigned int LightsArray::FRAMES = 60;

LightsArray::LightsArray(): VAO(0), positionBuffer(0), radiusBuffer(0),
							colorBuffer(0), quantity(0), counter(0),
							stepNumber(0)
{

}

void LightsArray::create(unsigned int _quantity)
{
	if (_quantity > sizeof(waypoint) / sizeof(VM::vec3))
		throw std::invalid_argument("Error: can't create that many"
									" spheres unless you provide more"
									" positions");
	quantity = _quantity;
	srand(time(NULL));
	for (unsigned int i = 0; i < quantity; i++)
	{
		position.push_back(waypoint[i]);
		radius.push_back(10 + 50 * static_cast<GLfloat>(rand()) / RAND_MAX);
		color.push_back(VM::vec3(static_cast<GLfloat>(rand()) / RAND_MAX,
						static_cast<GLfloat>(rand()) / RAND_MAX,
						static_cast<GLfloat>(rand()) / RAND_MAX));	
	}
}

void LightsArray::step()
{
	for (unsigned int i = 0; i < quantity; i++)
	{
		VM::vec3 src = waypoint[(i + stepNumber) % wpSize];
		VM::vec3 dest = waypoint[(i + 1 + stepNumber) % wpSize];
		VM::vec3 newPos = (dest - src) * counter / FRAMES + src;
		position[i] = newPos;
	}
	counter++;
	if (counter == FRAMES)
	{
		counter = 0;
		stepNumber = (stepNumber + 1) % wpSize;
	}
	#ifdef GRAPHICALCONTROLLER_M_DEBUG_SUPER
	std::cout << "Lights positions:" << std::endl;
	for (unsigned int i = 0; i < quantity; i++)
	{
		std::cout << '{' << position[i].x << ' ' << position[i].y
				  << ' ' << position[i].z << '}';
	}
	std::cout << std::endl;
	#endif
}

const unsigned int Sphere::DIVISION_FIRST = 20;
const unsigned int Sphere::DIVISION_SECOND = 10;

void Sphere::createLine(double first, double second, double offset)
{
	double halfStep = M_PI / DIVISION_SECOND;
	for (unsigned int i = 0; i <= DIVISION_SECOND; i++)
	{
		double angle = i * M_PI * 2 / DIVISION_SECOND + offset;
		aiVector3D vertexOne(cos(angle) * cos(first),
							 sin(first),
							 sin(angle) * cos(first));
		angle += halfStep;
		aiVector3D vertexTwo(cos(angle) * cos(second),
							 sin(second),
							 sin(angle) * cos(second));
		vertices_.push_back(vertexOne);
		vertices_.push_back(vertexTwo);
	}
}

void Sphere::postprocess()
{

}

Sphere::Sphere()
{
	const double halfStep = M_PI / DIVISION_SECOND;
	double offset = halfStep;
	for (unsigned int i = 0; i <  DIVISION_FIRST; i++)
	{
		if (offset != 0)
			offset = 0;
		else
			offset = halfStep;
			
		createLine(-M_PI / 2 + (M_PI / DIVISION_FIRST) * i,
				   -M_PI / 2 + (M_PI / DIVISION_FIRST) * (i + 1), offset);
	}
	/*
	for (unsigned int i = DIVISION_FIRST / 2; i < DIVISION_FIRST; i++)
	{
		if (offset != 0)
			offset = 0;
		else
			offset = halfStep;
			
		createLine(-M_PI / 2 + (M_PI / DIVISION_FIRST) * (i + 1),
				   -M_PI / 2 + (M_PI / DIVISION_FIRST) * i, offset);
	}
	postprocess();*/
}

const std::vector<aiVector3D>* Sphere::getMesh()
{
	return &vertices_;
}

void GraphicalController::init(int windowWidth, int windowHeight)
{
	windowWidth_ = windowWidth;
	windowHeight_ = windowHeight;
	GraphicalControllerPointer = this;

	int argc = 1;
	char** argv = new char*[2];
	char name[] = PROJECT_NAME;
	texturesCount_ = 0;
	opacityTexCount_ = 0;
	argv[1] = 0;
	argv[0] = name;
	std::cout << "Initializing GLUT... " << std::flush;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE |
						GLUT_DEPTH | GLUT_MULTISAMPLE);
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
	mouseCaptured_ = false;
	glutSetCursor(GLUT_CURSOR_RIGHT_ARROW);
	glClearColor(0.0, 0.0, 0.005, 0);
	std::cout << "success" << std::endl;

	std::cout << "Initializing GLEW... " << std::flush;
	putenv((char*)"MESA_GL_VERSION_OVERRIDE=3.3COMPAT");
	glewExperimental = true;
	glewInit();
	GLint maximum = 0;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maximum); CHECK_GL_ERRORS
	std::cout << "Maximum textures in fragment shader: "
			  << static_cast<int>(maximum) << std::endl;

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
	mouseCaptured_ = !mouseCaptured_;
	if (mouseCaptured_)
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
	{
		camera_.goForward(25.0);
		std::cout << "\rCurrent camera position: " << camera_.position.x << ' '
				  << camera_.position.y << ' '
				  << camera_.position.z << std::endl;
	}
	else if (key == 's' || key == 'S')
	{
		camera_.goBack(25.0);
		std::cout << "\rCurrent camera position: " << camera_.position.x << ' '
				  << camera_.position.y << ' '
				  << camera_.position.z << std::endl;
	}
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
	if (mouseCaptured_)
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

void GraphicalController::prepareTextures(GLuint shader)
{
	if (shader == sponzaShaderOne_)
	{
		for (unsigned int i = 0; i <= scene_->mNumMaterials / 2; i++)
		{
			GLuint location = glGetUniformLocation(shader,
				(std::string("Tex") + std::to_string(i)).data());
				CHECK_GL_ERRORS
			glUniform1i(location, materials_[i].first[0]); CHECK_GL_ERRORS
		}
		opTexPointer_ = 0;
		for (unsigned int i = 0; i <= scene_->mNumMaterials / 2; i++)
		{
			if (materials_[i].first[1] != 0)
			{
				GLuint location = glGetUniformLocation(shader,
					(std::string("Opac") +
					 std::to_string(opTexPointer_)).data());
				CHECK_GL_ERRORS
				opTexPointer_++;
				glUniform1i(location, materials_[i].first[1]); CHECK_GL_ERRORS
			}
		}
	}
	else
	{
		for (unsigned int i = scene_->mNumMaterials / 2 + 1;
			 i < scene_->mNumMaterials; i++)
		{
			GLuint location = glGetUniformLocation(shader,
				(std::string("Tex") + std::to_string(i)).data());
				CHECK_GL_ERRORS
			glUniform1i(location, materials_[i].first[0]); CHECK_GL_ERRORS
		}

		for (unsigned int i = scene_->mNumMaterials / 2 + 1;
			 i <= scene_->mNumMaterials; i++)
		{
			if (materials_[i].first[1] != 0)
			{
				GLuint location = glGetUniformLocation(shader,
					(std::string("Opac") +
					 std::to_string(opTexPointer_)).data());
				CHECK_GL_ERRORS
				opTexPointer_++;
				if (opTexPointer_ == opacityTexCount_)
				glUniform1i(location, materials_[i].first[1]); CHECK_GL_ERRORS
			}
		}
	}

	for (GLuint i = 0; i < texturesCount_ + opacityTexCount_; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures_[i]); CHECK_GL_ERRORS
	}
}

void GraphicalController::unprepareTextures()
{
	for (GLuint i = 0; i < texturesCount_ + opacityTexCount_; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void GraphicalController::prepareProgram(GLuint program)
{
	unprepareTextures();
	glUseProgram(0);
	glUseProgram(program);
	prepareTextures(program);
}


void GraphicalController::updateFPS()
{
	int currentTime = glutGet(GLUT_ELAPSED_TIME);
	std::cout << '\r'
		<< "FPS: " << 1000 / (currentTime - lastTime_) << "      ";
	lastTime_ = currentTime;
}

void GraphicalController::drawLights()
{
	glUseProgram(sphereShader_); CHECK_GL_ERRORS
	glBindVertexArray(lights_.VAO); CHECK_GL_ERRORS
	GLint cameraLocation =
		glGetUniformLocation(sphereShader_, "camera"); CHECK_GL_ERRORS
	GLint cameraPosLocation = 
		glGetUniformLocation(sphereShader_, "cameraPosition"); CHECK_GL_ERRORS
	glUniformMatrix4fv(cameraLocation, 1, GL_TRUE,
		camera_.getMatrix().data().data()); CHECK_GL_ERRORS
	GLfloat camPos[3] = {camera_.position.x, camera_.position.y,
						 camera_.position.z};
	glUniform3fv(cameraPosLocation, 1, camPos);
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, sphereMeshSize_,
						  lights_.quantity); CHECK_GL_ERRORS
	glBindVertexArray(0);
	glUseProgram(0);
}

void GraphicalController::drawSponza()
{
	updateFPS();
	GLint cameraLocationOne =
		glGetUniformLocation(sponzaShaderOne_, "camera"); CHECK_GL_ERRORS
	GLint materialIndexLocationOne =
		glGetUniformLocation(sponzaShaderOne_, "material"); CHECK_GL_ERRORS
	GLint cameraPosLocOne =
		glGetUniformLocation(sponzaShaderOne_, "cameraPosition");
			CHECK_GL_ERRORS

	GLint cameraLocationTwo =
		glGetUniformLocation(sponzaShaderTwo_, "camera"); CHECK_GL_ERRORS
	GLint materialIndexLocationTwo =
		glGetUniformLocation(sponzaShaderTwo_, "material"); CHECK_GL_ERRORS
	GLint cameraPosLocTwo =
		glGetUniformLocation(sponzaShaderTwo_, "cameraPosition");
			CHECK_GL_ERRORS

	glUseProgram(sponzaShaderOne_); CHECK_GL_ERRORS
	prepareProgram(sponzaShaderOne_);
	glUniformMatrix4fv(cameraLocationOne, 1, GL_TRUE,
		camera_.getMatrix().data().data()); CHECK_GL_ERRORS
	GLfloat camPos[3];
	camPos[0] = camera_.position.x;
	camPos[1] = camera_.position.y;
	camPos[2] = camera_.position.z;
	glUniform3fv(cameraPosLocOne, 1, camPos);

	for (uint i = 0; i < scene_->mNumMaterials; i++)
	{
		MaterialInfo material = materials_[i];
		GLuint materialIndex = i;
		GLuint materialIndexLocation;
		if (i > scene_->mNumMaterials / 2)
			materialIndexLocation = materialIndexLocationTwo;
		else
			materialIndexLocation = materialIndexLocationOne;
		if (i == scene_->mNumMaterials / 2 + 1)
		{
			prepareProgram(sponzaShaderTwo_);
			glUniformMatrix4fv(cameraLocationTwo, 1, GL_TRUE,
				camera_.getMatrix().data().data()); CHECK_GL_ERRORS
			camPos[0] = camera_.position.x;
			camPos[1] = camera_.position.y;
			camPos[2] = camera_.position.z;
			glUniform3fv(cameraPosLocTwo, 1, camPos);
		}
		glUniform1ui(materialIndexLocation, materialIndex);
		for (VAOs::iterator iter = material.second.begin();
			 iter != material.second.end();
			 iter++)
		{
			glBindVertexArray(iter->first); CHECK_GL_ERRORS
			glDrawElements(GL_TRIANGLES, iter->second, GL_UNSIGNED_INT, 0);
				CHECK_GL_ERRORS
			glBindVertexArray(0); CHECK_GL_ERRORS
		}
	}
	unprepareTextures();
}

void GraphicalController::updateLights()
{
	lights_.step();
	glBindVertexArray(lights_.VAO);
	glBindBuffer(GL_ARRAY_BUFFER, lights_.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER,
				 sizeof(VM::vec3) * lights_.position.size(),
				 lights_.position.data(), GL_DYNAMIC_DRAW);
		CHECK_GL_ERRORS
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void GraphicalController::display()
{
	glEnable(GL_DEPTH_TEST); CHECK_GL_ERRORS
	//glEnable(GL_CULL_FACE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); CHECK_GL_ERRORS

	drawLights();
	drawSponza();
	updateLights();

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

	std::cout << "Creating lights... " << std::flush;
	createLights();
	std::cout << "success" << std::endl;

	frameCounter_ = 0;
	lastTime_ = glutGet(GLUT_ELAPSED_TIME);
}

void GraphicalController::createCamera()
{
	camera_.angle = 45.0f / 180.0f * M_PI;
	camera_.direction = VM::vec3(0, 0.3, -1);
	camera_.position = VM::vec3(0, 100, 0);
	camera_.screenRatio = static_cast<float>(windowWidth_) / windowHeight_;
	camera_.up = VM::vec3(0, 1, 0);
	camera_.zfar = 10000.0f;
	camera_.znear = 5.0f;
}

bool GraphicalController::loadTexture(const char* path, GLuint& texture)
{
	int width, height;
	int channels;
	unsigned char* image = SOIL_load_image(path,
		&width, &height, &channels, SOIL_LOAD_RGBA);
	if (image == NULL)
	{
		std::cerr << "Failed to load texture " << path << std::endl;
		return false;
	}
//		throw std::invalid_argument((std::string(
//			"Error: failed to load texture file") + path).data());
	glGenTextures(1, &texture);
	glActiveTexture(GL_TEXTURE0 + texturesCount_);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0,
		GL_RGBA, GL_UNSIGNED_BYTE, image); CHECK_GL_ERRORS
	glGenerateMipmap(GL_TEXTURE_2D); CHECK_GL_ERRORS
	SOIL_free_image_data(image);
	textures_.push_back(texture);
	texture = texturesCount_;
	glBindTexture(GL_TEXTURE_2D, 0);
	return true;
}

void GraphicalController::loadTextures()
{
	aiString path;
	aiReturn error;
	GLuint texture;
	GLuint noTexture;
	if (!loadTexture((std::string(MODEL_PATH) +
		"/textures/sponza_no_tex.tga").data(), noTexture))
			throw std::invalid_argument("Error: failed to load no_texture texture");
	texturesCount_++;
	for (unsigned int i = 0; i < scene_->mNumMaterials; i++)
	{
		if ((error = scene_->mMaterials[i]->GetTexture(
			 aiTextureType_AMBIENT, 0, &path)) == aiReturn_SUCCESS)
		{
			char* data = path.data;
			for (unsigned int j = 0; data[j] != '\0'; j++)
				if (data[j] == '\\')
					data[j] = '/';
			if (!loadTexture((std::string(MODEL_PATH) +
				"/" + path.C_Str()).data(), texture))
				texture = noTexture;
			else
				texturesCount_++;
		} else
			texture = noTexture;
		materials_[i].first[0] = texture;

	}
	for (unsigned int i = 0; i < scene_->mNumMaterials; i++)
	{
		if ((error = scene_->mMaterials[i]->GetTexture(
			 aiTextureType_OPACITY, 0, &path)) == aiReturn_SUCCESS)
		{
			char* data = path.data;
			for (unsigned int j = 0; data[j] != '\0'; j++)
				if (data[j] == '\\')
					data[j] = '/';
			if (!loadTexture((std::string(MODEL_PATH) +
				"/" + path.C_Str()).data(), texture))
				texture = 0;
			else
				opacityTexCount_++;
		} else
			texture = 0;
		materials_[i].first[1] = texture;
	}
	std::cout << "Loaded " << texturesCount_ << '/'
			  << scene_->mNumMaterials << " possible textures" << std::endl;
	if (opacityTexCount_ != 0)
		std::cout << "Also loaded " << opacityTexCount_
				  << " opacity textures" << std::endl;
}

void GraphicalController::compileShaders()
{
	sponzaShaderOne_ = GL::CompileShaderProgram("sponzaOne");
		CHECK_GL_ERRORS
	sponzaShaderTwo_ = GL::CompileShaderProgram("sponzaTwo");
		CHECK_GL_ERRORS
	for (uint i = 0; i < scene_->mNumMaterials; i++)
	{
		VAOs listVAO;
		MaterialInfo info;
		info.first[0] = i;
		info.first[1] = 0;
		info.second = listVAO;
		materials_.push_back(info);
	}
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
	GLuint shader;
	uint material = scene_->mMeshes[i]->mMaterialIndex;
	if (material >= 14)
		shader = sponzaShaderTwo_;
	else
		shader = sponzaShaderOne_;
	glGenVertexArrays(1, &result.first);
	glBindVertexArray(result.first);

	GLuint vertBuffer;
	aiVector3D* vertices = scene_->mMeshes[i]->mVertices;
	int vertLength = scene_->mMeshes[i]->mNumVertices;

	glGenBuffers(1, &vertBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * vertLength,
				 vertices, GL_STATIC_DRAW); CHECK_GL_ERRORS
	GLuint vertLocation = glGetAttribLocation(shader, "point"); CHECK_GL_ERRORS
	glEnableVertexAttribArray(vertLocation); CHECK_GL_ERRORS
	glVertexAttribPointer(vertLocation, 3, GL_FLOAT, GL_FALSE, 0, 0); CHECK_GL_ERRORS

	GLuint uvBuffer;
	aiVector3D* uv = scene_->mMeshes[i]->mTextureCoords[0];

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * vertLength,
				 uv, GL_STATIC_DRAW); CHECK_GL_ERRORS
	GLuint uvLocation = glGetAttribLocation(shader, "uvCoord"); CHECK_GL_ERRORS
	glEnableVertexAttribArray(uvLocation); CHECK_GL_ERRORS
	glVertexAttribPointer(uvLocation, 3, GL_FLOAT, GL_FALSE, 0, 0); CHECK_GL_ERRORS

	GLuint normBuffer;
	aiVector3D* norm = scene_->mMeshes[i]->mNormals;

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glGenBuffers(1, &normBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * vertLength,
				 norm, GL_STATIC_DRAW); CHECK_GL_ERRORS
	GLuint normLocation = glGetAttribLocation(shader, "normal");
		CHECK_GL_ERRORS
	glEnableVertexAttribArray(normLocation); CHECK_GL_ERRORS
	glVertexAttribPointer(normLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
		CHECK_GL_ERRORS

	GLuint facesBuffer;
	std::vector<unsigned int> faces = concatFaces(scene_->mMeshes[i]);
	length = faces.size();

	glGenBuffers(1, &facesBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, facesBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * faces.size(),
				 faces.data(), GL_STATIC_DRAW); CHECK_GL_ERRORS

	glBindVertexArray(0);
	
	result.second = material;
	return result;
}

void GraphicalController::shutdown()
{
	glutDestroyWindow(glutGetWindow());
	std::cout << std::endl;
}

void GraphicalController::checkInfo()
{
	std::cout << "Checking what's loaded:" << std::endl;
	for (uint i = 0; i < scene_->mNumMaterials; i++)
	{
		std::cout << i + 1 << ": ";
		for (VAOs::iterator iter = materials_[i].second.begin();
			 iter != materials_[i].second.end();
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
	loadTextures();
	for (uint i = 0; i < scene_->mNumMeshes; i++)
	{
		uint length;
		MeshInfo meshInfo = loadMesh(i, length);
		uint index = meshInfo.second;
		meshInfo.second = length;
		materials_[index].second.push_back(meshInfo);
	}
	#ifdef GRAPHICALCONTROLLER_M_DEBUG_SUPER
	checkInfo();
	#endif
}

void GraphicalController::createLights()
{
	Sphere sphere;
	const std::vector<aiVector3D>* mesh = sphere.getMesh();
	sphereMeshSize_ = mesh->size();
	lights_.create(10);
	sphereShader_ = GL::CompileShaderProgram("sphere");
	glGenVertexArrays(1, &lights_.VAO);
	glBindVertexArray(lights_.VAO);

	GLuint meshBuffer;
	glGenBuffers(1, &meshBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, meshBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(aiVector3D) * mesh->size(),
				 mesh->data(), GL_STATIC_DRAW); CHECK_GL_ERRORS
	GLuint meshLocation = glGetAttribLocation(sphereShader_, "point");
		CHECK_GL_ERRORS
	glEnableVertexAttribArray(meshLocation);
		CHECK_GL_ERRORS
	glVertexAttribPointer(meshLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
		CHECK_GL_ERRORS

	glGenBuffers(1, &lights_.positionBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, lights_.positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VM::vec3) * lights_.position.size(),
				 lights_.position.data(), GL_DYNAMIC_DRAW); CHECK_GL_ERRORS
	GLuint positionsLocation = glGetAttribLocation(sphereShader_, "position");
		CHECK_GL_ERRORS
	glEnableVertexAttribArray(positionsLocation); CHECK_GL_ERRORS
	glVertexAttribPointer(positionsLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
		CHECK_GL_ERRORS
	glVertexAttribDivisor(positionsLocation, 1);

	glGenBuffers(1, &lights_.radiusBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, lights_.radiusBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * lights_.radius.size(),
				 lights_.radius.data(), GL_STATIC_DRAW);
		CHECK_GL_ERRORS
	GLuint radiusLocation = glGetAttribLocation(sphereShader_, "radius");
		CHECK_GL_ERRORS
	glEnableVertexAttribArray(radiusLocation); CHECK_GL_ERRORS
	glVertexAttribPointer(radiusLocation, 1, GL_FLOAT, GL_FALSE, 0, 0);
		CHECK_GL_ERRORS
	glVertexAttribDivisor(radiusLocation, 1);

	glGenBuffers(1, &lights_.colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, lights_.colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VM::vec3) * lights_.color.size(),
				 lights_.color.data(), GL_STATIC_DRAW);
		CHECK_GL_ERRORS
	GLuint colorLocation = glGetAttribLocation(sphereShader_, "color");
		CHECK_GL_ERRORS
	glEnableVertexAttribArray(colorLocation); CHECK_GL_ERRORS
	glVertexAttribPointer(colorLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
		CHECK_GL_ERRORS
	glVertexAttribDivisor(colorLocation, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
