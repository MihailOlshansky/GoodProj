#pragma once
#include "Dev.h"
#include "engine/Engine.h"

class Lab4 : public UnitBase {
private:
	const float minMetalness = 0.1f;
	const float maxMetalness = 0.9999f;

	const float minRoughness = 0.1f;
	const float maxRoughness = 0.9999f;

	static const char* imguiShadeModels[];
	static const char* imguiIrradianceModes[];

	static const char* textureNames[];
	static const char* textureFilePaths[];

	int selectedShadeModel = SHADE_MODEL_PBR;
	int selectedTexture = 1;
	int selectedIrradianceMode = IRRADIANCE_MAP_DEFAULT;

	std::vector<Mesh*> meshes;
	std::vector<Material*> materials;
	Geometry* sphereGeom;
	Texture* texture;
	SphereLight* light;
	Material* lightMaterial;
public:
	Lab4();
	virtual void init() override;
	virtual void update() override;
	virtual ~Lab4() override;
};