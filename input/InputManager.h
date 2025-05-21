#pragma once
#include "Dev.h"
#include "Input.h"

class InputManager {
private:
	Engine* engine = nullptr;
	Input* input = new Input();
public:
	InputManager(Engine* eng);
	void preocessInput(HWND hWnd);
	~InputManager();
};
