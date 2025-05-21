#include "Cubes.h"

Cubes::Cubes() {

}

void Cubes::init()
{
	texture = engine->getRender()->getTextureManager()->loadTexture("bin/textures/GoodTexture.jpg", true, true);

	cubeGeom = engine->getRender()->getGeometryManager()->addCube();
	for (int i = 0; i < 100; i++)
	{
		Material* mat = engine->getRender()->getMaterialManager()->addMaterial();
		mat->getData().color.x = 1.0 * rand() / RAND_MAX;
		mat->getData().color.y = 1.0 * rand() / RAND_MAX;
		mat->getData().color.z = 1.0 * rand() / RAND_MAX;
		mat->setTexture(texture, MaterialTextureType_Color);
		materials.push_back(mat);
	}

	const int W = 10;
	const int H = 10;
	const int D = 10;

	for (int x = -W /2; x < W/2; x++)
		for (int y = -H / 2; y < H / 2; y++)
			for (int z = -D / 2; z < D / 2; z++)
			{
				Mesh* mesh = engine->getRender()->getMeshManager()->addMesh(cubeGeom, materials[rand() % materials.size()]);
				mesh->setPosition({ 3.0f * x, 3.0f * y, 3.0f * z });
				//mesh->setRotation({ 1.0f * rand(), 1.0f * rand(), 1.0f * rand() });
				//mesh->setScale({ 0.01, 0.01, 0.01 });
				meshes.push_back(mesh);
			}
}

void Cubes::update() {

}

Cubes::~Cubes() {
}


