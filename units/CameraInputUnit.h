#pragma once
#include "Dev.h"
#include "engine/Engine.h"

class CameraInputUnit : public UnitBase {
private:
	float Speed = 0.03f;
	float Sencitivity = 1.0f;

	Camera* camera = nullptr;
	Input* input = nullptr;
public:
	CameraInputUnit();
	virtual void init() override;
	virtual void update() override;
	virtual ~CameraInputUnit() override;
};
