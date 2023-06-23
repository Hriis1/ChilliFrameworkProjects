#include "CameraControler.h"

CameraControler::CameraControler(MainWindow& wnd, Camera& cam)
	:_wnd(wnd), _cam(cam)
{
}

void CameraControler::update(float deltaTime)
{
	while (!_wnd.mouse.IsEmpty())
	{
		const auto e = _wnd.mouse.Read();

		if (e.GetType() == Mouse::Event::Type::WheelUp)
			_cam.setScale(_cam.getScale() * 1.1f);
		else if (e.GetType() == Mouse::Event::Type::WheelDown)
			_cam.setScale(_cam.getScale() * 0.9f);
	}

	if (_wnd.kbd.KeyIsPressed('Q'))
	{
		_cam.setAngle(_cam.getAngle() + _rotationSpeed * deltaTime);
	}
	if (_wnd.kbd.KeyIsPressed('E'))
	{
		_cam.setAngle(_cam.getAngle() - _rotationSpeed * deltaTime);
	}

	const float cameraSpeed = 3.0f;
	if (_wnd.kbd.KeyIsPressed('S'))
	{
		_cam.moveBy(Vec2<float>(0.0f, -cameraSpeed));
	}
	if (_wnd.kbd.KeyIsPressed('W'))
	{
		_cam.moveBy(Vec2<float>(0.0f, cameraSpeed));
	}
	if (_wnd.kbd.KeyIsPressed('A'))
	{
		_cam.moveBy(Vec2<float>(-cameraSpeed, 0.0f));
	}
	if (_wnd.kbd.KeyIsPressed('D'))
	{
		_cam.moveBy(Vec2<float>(cameraSpeed, 0.0f));
	}
}
