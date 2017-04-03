#include "GraphicalController.h"
#include "PointerGraphicalController.h"

const unsigned int LightsArray::FRAMES = 16;
const unsigned int LightsArray::SPHERES_COUNT = 10;

const unsigned int Sphere::DIVISION_FIRST = 40;
const unsigned int Sphere::DIVISION_SECOND = 20;

const VM::vec3 LightsArray::waypoint[]=
{
	VM::vec3(-99.9843, 98.5502, -1.02022),
	VM::vec3(-199.953, 97.4004, -3.24024),
	VM::vec3(-299.916, 97.5505, -5.96025),
	VM::vec3(-399.889, 97.5006, -8.28039),
	VM::vec3(-499.864, 97.6508, -10.5006),
	VM::vec3(-599.77, 101.1, -13.119),
	VM::vec3(-699.673, 104.65, -15.7374),
	VM::vec3(-799.573, 108.199, -18.4557),
	VM::vec3(-899.45, 112.348, -21.1734),
	VM::vec3(-999.226, 118.594, -23.5888),
	VM::vec3(-1098.93, 125.638, -26.6012),
	VM::vec3(-1198.64, 132.583, -29.6138),
	VM::vec3(-1202.79, 159.015, 66.7405),
	VM::vec3(-1206.55, 185.737, 163.031),
	VM::vec3(-1209.45, 211.3, 259.665),
	VM::vec3(-1212.06, 236.186, 356.483),
	VM::vec3(-1114.24, 233.936, 377.109),
	VM::vec3(-1015.54, 230.987, 392.915),
	VM::vec3(-916.073, 228.737, 402.975),
	VM::vec3(-816.319, 226.588, 409.648),
	VM::vec3(-716.565, 224.938, 402.834),
	VM::vec3(-617.545, 223.288, 388.96),
	VM::vec3(-518.859, 221.438, 372.913),
	VM::vec3(-420.564, 219.789, 354.599),
	VM::vec3(-321.972, 218.139, 337.958),
	VM::vec3(-222.265, 215.889, 330.647),
	VM::vec3(-122.661, 216.44, 339.514),
	VM::vec3(-23.3894, 216.29, 351.565),
	VM::vec3(75.4996, 218.34, 366.288),
	VM::vec3(173.905, 218.59, 384.072),
	VM::vec3(272.221, 218.44, 402.348),
	VM::vec3(370.462, 218.09, 421.018),
	VM::vec3(468.722, 217.741, 439.589),
	VM::vec3(568.238, 216.691, 449.352),
	VM::vec3(668.219, 218.641, 449.132),
	VM::vec3(767.307, 227.38, 438.87),
	VM::vec3(866.158, 238.308, 428.431),
	VM::vec3(965.39, 247.844, 420.555),
	VM::vec3(1051.62, 241.099, 370.358),
	VM::vec3(1097.92, 243.949, 281.768),
	VM::vec3(1115.88, 243.899, 183.395),
	VM::vec3(1123.03, 241.75, 83.6739),
	VM::vec3(1122.29, 240.7, -16.3178),
	VM::vec3(1120.55, 239.75, -116.298),
	VM::vec3(1117.81, 238.9, -216.257),
	VM::vec3(1114.87, 238.45, -316.213),
	VM::vec3(1072.15, 240.201, -406.614),
	VM::vec3(996.766, 245.249, -472.122),
	VM::vec3(900.086, 245.599, -497.674),
	VM::vec3(801.25, 244.649, -512.854),
	VM::vec3(701.453, 243.299, -519.089),
	VM::vec3(601.485, 241.549, -520.927),
	VM::vec3(501.498, 240, -520.667),
	VM::vec3(401.508, 238.65, -520.206),
	VM::vec3(301.513, 237.7, -519.845),
	VM::vec3(201.518, 236.75, -519.784),
	VM::vec3(101.522, 235.801, -519.723),
	VM::vec3(1.52666, 234.851, -519.663),
	VM::vec3(-98.4688, 233.901, -519.602),
	VM::vec3(-198.463, 232.851, -519.441),
	VM::vec3(-298.456, 231.701, -519.28),
	VM::vec3(-398.45, 230.552, -519.12),
	VM::vec3(-498.443, 229.402, -518.959),
	VM::vec3(-598.436, 228.252, -518.798),
	VM::vec3(-698.429, 227.102, -518.537),
	VM::vec3(-798.424, 226.152, -518.077),
	VM::vec3(-898.288, 230.501, -515.219),
	VM::vec3(-998.12, 234.65, -511.163),
	VM::vec3(-1097.83, 238.899, -504.812),
	VM::vec3(-1174.19, 241.149, -440.284),
	VM::vec3(-1230.56, 244.299, -357.745),
	VM::vec3(-1245.52, 243.649, -258.873),
	VM::vec3(-1230.89, 245.199, -159.961),
	VM::vec3(-1201.26, 246.049, -64.4544),
	VM::vec3(-1134.29, 245.8, 9.80807),
	VM::vec3(-1034.81, 255.733, 11.5976),
	VM::vec3(-936.176, 269.935, 3.19234),
	VM::vec3(-839.676, 292.977, -9.32725),
	VM::vec3(-749.956, 333.707, -26.3976),
	VM::vec3(-673.437, 395.923, -42.9485),
	VM::vec3(-608.032, 470.087, -57.8503),
	VM::vec3(-548.686, 549.252, -72.3743),
	VM::vec3(-494.316, 631.994, -86.4321),
	VM::vec3(-440.768, 715.238, -100.678),
	VM::vec3(-389.867, 800.579, -111.901),
	VM::vec3(-339.195, 886.232, -121.7),
	VM::vec3(-289.959, 972.85, -130.254),
	VM::vec3(-242.046, 1060.45, -135.789),
	VM::vec3(-184.371, 1141.94, -141.576),
	VM::vec3(-104.012, 1201.45, -141.738),
	VM::vec3(-12.4587, 1241.64, -139.909),
	VM::vec3(86.3259, 1256.53, -135.462),
	VM::vec3(181.766, 1226.74, -133.554),
	VM::vec3(272.784, 1185.46, -137.016),
	VM::vec3(354.571, 1127.97, -139.39),
	VM::vec3(430.782, 1063.28, -142.06),
	VM::vec3(503.297, 994.426, -142.786),
	VM::vec3(572.34, 922.101, -141.337),
	VM::vec3(641.383, 849.776, -139.888),
	VM::vec3(712.497, 779.483, -138.538),
	VM::vec3(796.625, 725.562, -134.666),
	VM::vec3(884.706, 678.455, -129.907),
	VM::vec3(978.041, 644.307, -118.843),
	VM::vec3(1064.27, 615.663, -77.0842),
	VM::vec3(1072.28, 595.943, 20.6243),
	VM::vec3(1061.09, 592.894, 119.949),
	VM::vec3(1029.76, 602.33, 214.444),
	VM::vec3(985.843, 617.224, 303.041),
	VM::vec3(934.711, 633.896, 387.347),
	VM::vec3(838.922, 647.206, 412.789),
	VM::vec3(740.077, 658.432, 422.967),
	VM::vec3(640.386, 666.075, 421.133),
	VM::vec3(540.94, 668.525, 410.915),
	VM::vec3(441.747, 665.075, 398.714),
	VM::vec3(342.287, 659.428, 389.999),
	VM::vec3(242.851, 648.997, 388.071),
	VM::vec3(144.43, 631.734, 391.971),
	VM::vec3(46.0798, 614.373, 397.051),
	VM::vec3(-52.4503, 598.194, 402.536),
	VM::vec3(-151.741, 587.664, 408.063),
	VM::vec3(-251.269, 579.921, 413.903),
	VM::vec3(-351.057, 577.072, 419.758),
	VM::vec3(-449.999, 587.503, 429.846),
	VM::vec3(-547.659, 605.651, 441.385),
	VM::vec3(-643.645, 631.214, 452.92),
	VM::vec3(-738.347, 662.813, 458.667),
	VM::vec3(-833.188, 694.507, 459.578),
	VM::vec3(-929.332, 718.132, 445.5),
	VM::vec3(-1027.47, 729.06, 429.724),
	VM::vec3(-1124.58, 710.714, 414.412),
	VM::vec3(-1198.86, 700.283, 348.283),
	VM::vec3(-1265.91, 688.362, 275.056),
	VM::vec3(-1303.98, 678.826, 183.078),
	VM::vec3(-1291.87, 672.78, 83.9981),
	VM::vec3(-1272.07, 667.732, -13.8916),
	VM::vec3(-1257.26, 656.108, -112.104),
	VM::vec3(-1239.61, 645.18, -209.924),
	VM::vec3(-1199.94, 636.342, -301.294),
	VM::vec3(-1147.56, 627.703, -386.039),
	VM::vec3(-1066.64, 620.359, -444.326),
	VM::vec3(-971.652, 615.311, -475.193),
	VM::vec3(-872.207, 609.864, -484.187),
	VM::vec3(-772.57, 604.616, -490.893),
	VM::vec3(-672.893, 599.768, -497.301),
	VM::vec3(-573.008, 602.918, -500.918),
	VM::vec3(-473.095, 606.167, -503.536),
	VM::vec3(-374.992, 600.32, -522.017),
	VM::vec3(-275.124, 596.271, -518.84),
	VM::vec3(-177.393, 592.922, -497.928),
	VM::vec3(-83.6688, 591.272, -463.099),
	VM::vec3(-18.4177, 592.822, -387.337),
	VM::vec3(30.8324, 598.868, -300.516),
	VM::vec3(64.9878, 603.716, -206.655),
	VM::vec3(92.3124, 631.015, -114.415),
	VM::vec3(97.8271, 685.859, -30.9782),
	VM::vec3(93.331, 759.956, 36.026),
	VM::vec3(72.1356, 853.535, 64.1985),
	VM::vec3(56.9156, 951.332, 78.4857),
	VM::vec3(41.1115, 1049.64, 87.7625),
	VM::vec3(20.1498, 1147.24, 93.5818),
	VM::vec3(-5.96819, 1243.72, 96.8053),
	VM::vec3(-70.8262, 1315.77, 121.351),
	VM::vec3(-136.105, 1387.33, 146.205),
	VM::vec3(-224.213, 1412.79, 186.06),
	VM::vec3(-315.333, 1424.22, 225.641),
	VM::vec3(-408.18, 1428.87, 262.488),
	VM::vec3(-502.874, 1432.92, 294.373),
	VM::vec3(-600.636, 1441.55, 313.56),
	VM::vec3(-699.951, 1449.3, 322.302),
	VM::vec3(-798.587, 1460.22, 309.987),
	VM::vec3(-895.569, 1472.44, 288.889),
	VM::vec3(-984.07, 1485.65, 244.245),
	VM::vec3(-1039.74, 1496.68, 161.912),
	VM::vec3(-1084.38, 1502.73, 72.6305),
	VM::vec3(-1098.68, 1506.38, -26.2745),
	VM::vec3(-1088.76, 1508.93, -125.748),
	VM::vec3(-1060.42, 1511.18, -221.622),
	VM::vec3(-980.959, 1512.23, -282.327),
	VM::vec3(-887.089, 1514.27, -316.74),
	VM::vec3(-789.649, 1520.42, -338.365),
	VM::vec3(-691.025, 1528.46, -352.806),
	VM::vec3(-592.195, 1534.11, -366.974),
	VM::vec3(-493.136, 1539.26, -379.661),
	VM::vec3(-393.913, 1544, -391.161),
	VM::vec3(-294.51, 1548.55, -401.073),
	VM::vec3(-194.688, 1550.5, -406.708),
	VM::vec3(-94.8286, 1552.45, -411.644),
	VM::vec3(5.11913, 1553.8, -414.582),
	VM::vec3(105.102, 1555.15, -415.82),
	VM::vec3(205.089, 1556.8, -415.759),
	VM::vec3(305.07, 1558.25, -414.498),
	VM::vec3(404.961, 1559.3, -409.939),
	VM::vec3(504.843, 1560.25, -405.179),
	VM::vec3(604.337, 1560.5, -395.135),
	VM::vec3(702.107, 1558.45, -374.234),
	VM::vec3(784.838, 1555, -318.165),
	VM::vec3(863.632, 1551.65, -256.682),
	VM::vec3(934.552, 1547.6, -186.297),
	VM::vec3(999.987, 1543.15, -110.809),
	VM::vec3(1053.85, 1536.61, -26.8096),
	VM::vec3(1096.63, 1529.66, 63.3114),
	VM::vec3(1121.27, 1526.01, 160.158),
	VM::vec3(1110.47, 1536.54, 259.014),
	VM::vec3(1076.01, 1554.4, 351.176),
	VM::vec3(1019.9, 1579.77, 429.967),
	VM::vec3(938.396, 1608.89, 480.05),
	VM::vec3(843.122, 1637.24, 490.957),
	VM::vec3(749.744, 1664.45, 467.708),
	VM::vec3(660.223, 1689.43, 430.803),
	VM::vec3(570.685, 1713.54, 393.366),
	VM::vec3(482.19, 1733.45, 351.269),
	VM::vec3(395.622, 1749.53, 303.862),
	VM::vec3(309.546, 1762.25, 254.576),
	VM::vec3(224.035, 1762.8, 202.733),
	VM::vec3(140.17, 1750.98, 149.565),
	VM::vec3(58.5015, 1728.52, 96.4056),
	VM::vec3(-22.7725, 1697.97, 46.7971),
	VM::vec3(-97.3444, 1646.25, 4.78838),
	VM::vec3(-151.718, 1566.72, -22.017),
	VM::vec3(-193.422, 1478.04, -41.9068),
	VM::vec3(-228.161, 1385.71, -58.3051),
	VM::vec3(-256.203, 1290.55, -70.862),
	VM::vec3(-256.93, 1190.55, -70.916),
	VM::vec3(-257.757, 1090.55, -70.9774),
	VM::vec3(-272.421, 991.65, -69.1651),
	VM::vec3(-287.183, 892.762, -67.3406),
	VM::vec3(-302.168, 793.905, -65.7313),
	VM::vec3(-317.65, 695.124, -64.1158),
	VM::vec3(-336.482, 596.929, -62.3409),
	VM::vec3(-357.278, 499.132, -60.5276),
	VM::vec3(-382.265, 402.323, -58.6256),
};
const unsigned int LightsArray::wpSize = sizeof(waypoint) / sizeof(aiVector3D);
/*
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
	VM::vec3(1117, 141, -32)*,
	VM::vec3(),
	VM::vec3(),
	VM::vec3(),
	VM::vec3(),
	VM::vec3(),
	VM::vec3(),
	VM::vec3(),
};
*/


LightsArray::LightsArray(): VAO(0), positionBuffer(0), radiusBuffer(0),
							colorBuffer(0), quantity(0), counter(0),
							stepNumber(0)
{

}

void LightsArray::create()
{
	unsigned int _quantity = SPHERES_COUNT;
	if (_quantity > sizeof(waypoint) / sizeof(VM::vec3))
		throw std::invalid_argument("Error: can't create that many"
									" spheres unless you provide more"
									" positions");
	quantity = _quantity;
	for (multiplier = wpSize / 2; quantity > wpSize / multiplier; multiplier--)
		{}
	srand(time(NULL));
	for (unsigned int i = 0; i < quantity; i++)
	{
		position.push_back(waypoint[multiplier * i]);
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
		VM::vec3 src = waypoint[(multiplier * i + stepNumber) % wpSize];
		VM::vec3 dest = waypoint[(multiplier * i + 1 + stepNumber) % wpSize];
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
//		std::cout << "VM::vec3(" << camera_.position.x << ", "
//				  << camera_.position.y << ", "
//				  << camera_.position.z << ")," << std::endl;
//		std::cout << "\rCurrent camera position: " << camera_.position.x << ' '
//				  << camera_.position.y << ' '
//				  << camera_.position.z << std::endl;
	}
	else if (key == 's' || key == 'S')
	{
		camera_.goBack(25.0);
//		std::cout << "\rCurrent camera position: " << camera_.position.x << ' '
//				  << camera_.position.y << ' '
//				  << camera_.position.z << std::endl;
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

void GraphicalController::passLights(GLuint shader)
{
	GLint lightsPositions =
		glGetUniformLocation(shader, "lightsPositions"); CHECK_GL_ERRORS
	glUniform3fv(lightsPositions, lights_.quantity,
				 static_cast<GLfloat*>(&lights_.position[0].x));
	GLint lightsPowers =
		glGetUniformLocation(shader, "lightsPowers"); CHECK_GL_ERRORS
	glUniform1fv(lightsPowers, lights_.quantity, lights_.radius.data());
	GLint lightsColors =
		glGetUniformLocation(shader, "lightsColors"); CHECK_GL_ERRORS
	glUniform3fv(lightsColors, lights_.quantity,
				 static_cast<GLfloat*>(&lights_.color[0].x));
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
	passLights(sponzaShaderOne_);

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
			passLights(sponzaShaderTwo_);
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
	lights_.create();
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
