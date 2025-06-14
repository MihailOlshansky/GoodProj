#include "Lab4.h"

const char* Lab4::imguiShadeModels[] = {
	"Color",
	"Phong",
	"Normal Distribution Function",
	"Geometry Function",
	"Fresnel Function",
	"PBR"
};

const char* Lab4::imguiIrradianceModes[] = {
	"Default",
	"Diffusion",
	"Specular",
	"Diffusion + Specular"
};

const char* Lab4::textureFilePaths[] = {
	"bin/textures/GoodTexture.jpg",
	"bin/textures/BlackTexture.png",
	"bin/textures/OrangeTexture.jpg",
	"bin/textures/DoomTexture.jpg"
};

const char* Lab4::textureNames[] = {
	"GoodTexture",
	"BlackTexture",
	"OrangeTexture",
	"DoomTexture"
};

Lab4::Lab4() {

}

void Lab4::init()
{
	selectedShadeModel = 5;
	selectedTexture = 2;

	texture = engine->getRender()->getTextureManager()->loadTexture(textureFilePaths[selectedTexture], true, true);

	sphereGeom = engine->getRender()->getGeometryManager()->addSphere(20, 20);
	const int W = 5;
	const int H = 5;
	const float3 scale = { 3.0f, 3.0f, 3.0f };
	float HW = 1.0f *  H* W;

	for (int i = 0; i < H * W; i++)
	{
		Material* mat = engine->getRender()->getMaterialManager()->addMaterial();
		mat->getData().shadeModel = selectedShadeModel;
		mat->getData().diffuse.x = 1.0 * rand() / RAND_MAX;
		mat->getData().diffuse.y = 1.0 * rand() / RAND_MAX;
		mat->getData().diffuse.z = 1.0 * rand() / RAND_MAX;

		mat->getData().specular.x = 1.0 * rand() / RAND_MAX;
		mat->getData().specular.y = 1.0 * rand() / RAND_MAX;
		mat->getData().specular.z = 1.0 * rand() / RAND_MAX;

		mat->getData().ph = 30;
		
		mat->getData().metalness = min(1.0 * (i / H) * (maxMetalness - minMetalness) / (W - 1) + minMetalness, maxMetalness);
		mat->getData().roughness = min(1.0 * (i % W) * (maxRoughness - minRoughness) / (H - 1) + minRoughness, maxRoughness);;
	
		mat->setTexture(texture, MaterialTextureType_Color);
		materials.push_back(mat);
	}

	for (int x = 0; x < W; x++)
		for (int y = 0; y < H; y++)
		{
			Mesh* mesh = engine->getRender()->getMeshManager()->addMesh(sphereGeom, materials[y * W + x]);
			mesh->setPosition({ -HW / 2 + x * HW / (W - 1), -HW / 2 + y * HW / (H - 1), HW / 1.5f });
			mesh->setScale(scale);
			meshes.push_back(mesh);
		}

	light = engine->getRender()->getLightManager()->addSphereLight({ 10, 10, 10 }, { -5, 5, 5 }, 100);

	Material* mat = engine->getRender()->getMaterialManager()->addMaterial();
	mat->getData().shadeModel = SHADE_MODEL_COLOR;
	mat->getData().color.x = 10;
	mat->getData().color.y = 10;
	mat->getData().color.z = 10;
	lightMaterial = mat;

	Mesh* mesh = engine->getRender()->getMeshManager()->addMesh(sphereGeom, mat);
	mesh->setPosition({-5, 5, 5});
	meshes.push_back(mesh);
}

void Lab4::update() {
	ImGui::Begin("Lab3");

	ImGui::Text(
		"Controls:\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", 
		"W - forward",
		"S - backward",
		"A - left",
		"D - right",
		"E - up",
		"Q - down",
		"R - reset",
		"Hold RMB to rotate");

	float3 lightColor = light->getColor();
	if (ImGui::ColorPicker3("LightColor", &lightColor.x))
	{
		light->setColor(lightColor);
		lightMaterial->getData().color.x = lightColor.x;
		lightMaterial->getData().color.y = lightColor.y;
		lightMaterial->getData().color.z = lightColor.z;
	}

	bool check = ImGui::Combo("Texture", &selectedTexture, textureNames, IM_ARRAYSIZE(textureNames));
	if (check)
	{
		texture = engine->getRender()->getTextureManager()->loadTexture(textureFilePaths[selectedTexture], true, true);
		for (auto& material : materials) {
			material->setTexture(texture, MaterialTextureType_Color);
		}
	}

	check = ImGui::Combo("Shade Model", &selectedShadeModel, imguiShadeModels, IM_ARRAYSIZE(imguiShadeModels));
	if (check)
	{
		for (auto& material : materials) {
			material->getData().shadeModel = selectedShadeModel;
		}
	}

	check = ImGui::Combo("Irradiance Map Mode", &selectedIrradianceMode, imguiIrradianceModes, IM_ARRAYSIZE(imguiIrradianceModes));
	if (check)
	{
		for (auto& material : materials) {
			material->getData().irradianceMapMode = selectedIrradianceMode;
		}
	}

	ImGui::End();
}

Lab4::~Lab4() {
}


