#pragma once

#include "Dev.h"
#include "win/Win.h"
#include "render/Render.h"
#include "input/Input.h"
#include "units/UnitBase.h"

class Engine {
private:
	Win* win;
	Render* render;
	Input* input;
	std::vector<UnitBase*> units;
public:

	Engine();

	void init(HINSTANCE hInstance);

	void run();

	void addUnit(UnitBase* unit);

	Win* getWin() { return win; }
	Render* getRender() { return render; }
	Input* getInput() { return input; }

	void frame();
	void resize(UINT width, UINT height);

	~Engine();
};