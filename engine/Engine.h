#pragma once

#include "Dev.h"
#include "win/Win.h"
#include "render/Render.h"
#include "units/UnitBase.h"

class Engine {
private:
	Win* win;
	Render* render;
	std::vector<UnitBase*> units;
public:

	Engine();

	void init(HINSTANCE hInstance);

	void run();

	void addUnit(UnitBase* unit);

	Win* getWin() { return win; }
	Render* getRender() { return render; }

	void frame();
	void resize(UINT width, UINT height);

	~Engine();
};