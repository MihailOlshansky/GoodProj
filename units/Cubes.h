#pragma once
#include "Dev.h"
#include "engine/Engine.h"

class Cubes : public UnitBase {
	std::vector<Mesh*> meshes;
	std::vector<Material*> materials;
	Geometry* cubeGeom;
	Texture* texture;
public:
	Cubes();
	virtual void init() override;
	virtual void update() override;
	virtual ~Cubes() override;
};
