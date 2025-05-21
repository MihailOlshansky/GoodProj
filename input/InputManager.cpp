#include "InputManager.h"

InputManager::InputManager(Engine* eng) {
	engine = eng;
}

void InputManager::preocessInput(HWND hWnd) {
	input->Response(hWnd);

}
InputManager::~InputManager() {
	delete input;
}
