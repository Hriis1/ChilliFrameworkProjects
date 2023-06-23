#pragma once
#include "MainWindow.h"
#include "Camera.h"
#include "MathKEK.h"

class CameraControler
{
public:
	CameraControler(MainWindow& wnd, Camera& cam);

	void update(float deltaTime);
private:
	static constexpr float _rotationSpeed = PI / 6.0f;
	MainWindow& _wnd;
	Camera& _cam;
};

