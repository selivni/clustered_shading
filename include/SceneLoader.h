#pragma once

#define SCENELOADER_M_DEBUG
#undef SCENELOADER_M_DEBUG

#include <stdexcept>
#include <iostream>

#include "cimport.h"
#include "Importer.hpp"
#include "scene.h"
#include "postprocess.h"



class SceneLoader
{
public:
	void load(const std::string&);
	const aiScene* scene();
	SceneLoader();
private:
	const aiScene* scene_;
	Assimp::Importer importer;

	void checkScene();
	std::string boolToStr(bool);
};
