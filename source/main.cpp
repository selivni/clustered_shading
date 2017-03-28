#include <iostream>

#include "SceneLoader.h"
#include "GraphicalController.h"

int main()
{
	try {
		SceneLoader loader;
		GraphicalController graphics;
		loader.load(SPONZA_OBJ);
		graphics.init(WINDOWWIDTH_DEFAULT, WINDOWHEIGHT_DEFAULT);
		graphics.createMap(loader.scene());
		graphics.startLoop();
		return EXIT_SUCCESS;
	}
	catch (std::invalid_argument error)
	{
		std::cout << "Exception caught by main module!" << std::endl;
		std::cout << error.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown exception caught in main module, aborting"
				  << std::endl;
	}
	return EXIT_FAILURE;
}
