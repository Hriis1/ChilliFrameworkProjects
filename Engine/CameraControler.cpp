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
	else if (_wnd.kbd.KeyIsPressed('E'))
	{
		_cam.setAngle(_cam.getAngle() - _rotationSpeed * deltaTime);
	}

	const float cameraSpeed = 3.0f;
	if (_wnd.kbd.KeyIsPressed('S'))
	{
		Vec2<float> moveVec = {0.0f, -cameraSpeed};

		//rotate the moveVec with -_angle to counteract the camera rotation
		moveVec.Rotate(-_cam.getAngle());

		_cam.moveBy(moveVec);
	}
	if (_wnd.kbd.KeyIsPressed('W'))
	{
		Vec2<float> moveVec = { 0.0f, cameraSpeed };

		//rotate the moveVec with -_angle to counteract the camera rotation
		moveVec.Rotate(-_cam.getAngle());

		_cam.moveBy(moveVec);
	}
	if (_wnd.kbd.KeyIsPressed('A'))
	{
		Vec2<float> moveVec = { -cameraSpeed, 0.0f };

		//rotate the moveVec with -_angle to counteract the camera rotation
		moveVec.Rotate(-_cam.getAngle());

		_cam.moveBy(moveVec);
	}
	if (_wnd.kbd.KeyIsPressed('D'))
	{
		Vec2<float> moveVec = { cameraSpeed, 0.0f };

		//rotate the moveVec with -_angle to counteract the camera rotation
		moveVec.Rotate(-_cam.getAngle());

		_cam.moveBy(moveVec);
	}
}
