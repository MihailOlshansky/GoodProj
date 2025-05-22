#include "CameraInputUnit.h"

CameraInputUnit::CameraInputUnit() {}

void CameraInputUnit::init() {
	camera = &(engine->getRender()->playerCamera);
	input = engine->getInput();
}

void CameraInputUnit::update() {
	if (input->keys['r'] || input->keys['R']) {
		camera->reset();
	}
	DirectX::XMFLOAT3 cameraTranslate = { 0, 0, 0 };
	float angleUpInDegrees = 0;
	float angleRightInDegrees = 0;
	cameraTranslate.z += (input->keys['w'] || input->keys['W']) * Speed;
	cameraTranslate.z -= (input->keys['s'] || input->keys['S']) * Speed;
	cameraTranslate.x += (input->keys['d'] || input->keys['D']) * Speed;
	cameraTranslate.x -= (input->keys['a'] || input->keys['A']) * Speed;
	cameraTranslate.y += (input->keys['e'] || input->keys['E']) * Speed;
	cameraTranslate.y -= (input->keys['q'] || input->keys['Q']) * Speed;

//	cameraTranslate.z += input->Mdz;
	if (input->keys[VK_RBUTTON]) {
		angleUpInDegrees = input->Mdx * Sencitivity;
		angleRightInDegrees = input->Mdy * Sencitivity;
	}

	DirectX::XMFLOAT3 dirf = camera->getDirection();
	DirectX::XMFLOAT3 upf = { 0, 1, 0 };


	DirectX::XMVECTOR dir = DirectX::XMLoadFloat3(&dirf);
	DirectX::XMVECTOR up = DirectX::XMLoadFloat3(&upf);
	DirectX::XMVECTOR right = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(up, dir));
	up = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(dir, right));
	DirectX::XMVECTOR total = DirectX::XMVectorScale(dir, cameraTranslate.z);
	total = DirectX::XMVectorAdd(total, DirectX::XMVectorScale(up, cameraTranslate.y));
	total = DirectX::XMVectorAdd(total, DirectX::XMVectorScale(right, cameraTranslate.x));

	DirectX::XMStoreFloat3(&cameraTranslate, total);
	camera->translate(cameraTranslate);
	camera->rotateAroundUp(angleUpInDegrees);
	camera->rotateAroundRight(angleRightInDegrees);
}


CameraInputUnit::~CameraInputUnit() {}
