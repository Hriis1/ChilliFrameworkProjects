#pragma once
#include "MainWindow.h"
#include "Camera.h"

class CameraControler
{
public:
	CameraControler(MainWindow& wnd, Camera& cam);

	void update(float deltaTime);
private:
	MainWindow& _wnd;
	Camera& _cam;
};

