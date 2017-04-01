#include "SceneLoader.h"

SceneLoader::SceneLoader(): scene_(nullptr)
	{}

void SceneLoader::load(const std::string& path)
{
	std::cout << "Reading model file "
			  << path << ". . . " << std::flush;
	scene_ = importer.ReadFile(path, 
		aiProcess_Triangulate |
		aiProcess_GenSmoothNormals
		);
	if (!scene_)
		throw std::invalid_argument("Error: failed to read model file");
	std::cout << "Done." << std::endl;
	#ifdef SCENELOADER_M_DEBUG
	checkScene();
	#endif
}

const aiScene* SceneLoader::scene()
{
	return scene_;
}

void SceneLoader::checkScene()
{
	std::cout << "Checking scene..." << std::endl;
	if (!scene_)
		throw std::invalid_argument("Checking scene error: no scene loaded!");

	std::cout << "Animations? " << std::flush;
	std::cout << boolToStr(scene_->HasAnimations());
	if (scene_->HasAnimations())
		std::cout << ", " << scene_->mNumAnimations;
	std::cout << std::endl;

	std::cout << "Cameras? " << std::flush;
	std::cout << boolToStr(scene_->HasCameras());
	if (scene_->HasCameras())
		std::cout << ", " << scene_->mNumCameras;
	std::cout << std::endl;

	std::cout << "Lights? " << std::flush;
	std::cout << boolToStr(scene_->HasLights());
	if (scene_->HasLights())
		std::cout << ", " << scene_->mNumLights;
	std::cout << std::endl;

	std::cout << "Materials? " << std::flush;
	std::cout << boolToStr(scene_->HasMaterials());
	if (scene_->HasMaterials())
	{
		std::cout << ", " << scene_->mNumMaterials;
		for (uint i = 0; i < scene_->mNumMaterials; i++)
		{
			std::cout << std::endl;
			std::cout << "Material #" << i + 1 << ", Textures: " << std::flush;
			int num;
			if ((num = scene_->mMaterials[i]->GetTextureCount(aiTextureType_NONE)))
				std::cout << 0 << ':' << num << ' ';
			if ((num = scene_->mMaterials[i]->GetTextureCount(aiTextureType_DIFFUSE)))
				std::cout << 1 << ':' << num << ' ';
			if ((num = scene_->mMaterials[i]->GetTextureCount(aiTextureType_SPECULAR)))
				std::cout << 2 << ':' << num << ' ';
			if ((num = scene_->mMaterials[i]->GetTextureCount(aiTextureType_AMBIENT)))
				std::cout << 3 << ':' << num << ' ';
			if ((num = scene_->mMaterials[i]->GetTextureCount(aiTextureType_EMISSIVE)))
				std::cout << 4 << ':' << num << ' ';
			if ((num = scene_->mMaterials[i]->GetTextureCount(aiTextureType_HEIGHT)))
				std::cout << 5 << ':' << num << ' ';
			if ((num = scene_->mMaterials[i]->GetTextureCount(aiTextureType_NORMALS)))
				std::cout << 6 << ':' << num << ' ';
			if ((num = scene_->mMaterials[i]->GetTextureCount(aiTextureType_SHININESS)))
				std::cout << 7 << ':' << num << ' ';
			if ((num = scene_->mMaterials[i]->GetTextureCount(aiTextureType_OPACITY)))
				std::cout << 8 << ':' << num << ' ';
			if ((num = scene_->mMaterials[i]->GetTextureCount(aiTextureType_DISPLACEMENT)))
				std::cout << 9 << ':' << num << ' ';
			if ((num = scene_->mMaterials[i]->GetTextureCount(aiTextureType_LIGHTMAP)))
				std::cout << 10 << ':' << num << ' ';
			if ((num = scene_->mMaterials[i]->GetTextureCount(aiTextureType_REFLECTION)))
				std::cout << 11 << ':' << num << ' ';
			if ((num = scene_->mMaterials[i]->GetTextureCount(aiTextureType_UNKNOWN)))
				std::cout << 12 << ':' << num << ' ';
			if (scene_->mMaterials[i]->mNumProperties)
				std::cout << std::endl << "Properties: "
						  << scene_->mMaterials[i]->mNumProperties;
		}
	}
	std::cout << std::endl;

	std::cout << "Meshes? " << std::flush;
	std::cout << boolToStr(scene_->HasMeshes());
	if (scene_->HasMeshes())
	{
		std::cout << ", " << scene_->mNumMeshes;
		int sumFaces = 0;
		int sumNormals = 0;
		for (uint i = 0; i < scene_->mNumMeshes; i++)
		{
			if (scene_->mMeshes[i]->HasFaces())
				sumFaces++;
			if (scene_->mMeshes[i]->HasNormals())
				sumNormals++;
		}
		std::cout << "\nFaces: "
			<< sumFaces << '/' << scene_->mNumMeshes << "\nVertices: "
			<< sumFaces << '/' << scene_->mNumMeshes << "\nNormals: "
			<< sumNormals << '/' << scene_->mNumMeshes;
	}
	std::cout << std::endl;

	std::cout << "Textures? " << std::flush;
	std::cout << boolToStr(scene_->HasTextures());
	if (scene_->HasTextures())
		std::cout << ", " << scene_->mNumTextures;
	std::cout << std::endl;
}

std::string SceneLoader::boolToStr(bool a)
{
	if (!a)
		return "No";
	else
		return "Yes";
}
