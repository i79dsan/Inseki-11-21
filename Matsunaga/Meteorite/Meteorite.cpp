#include "DxLib.h"
#include "Meteorite.h"
#include "../../Iwasaki/Time/Time.h"

#include <vector>

Meteorite::Meteorite(Vector2 pos, double speed, int radius, Vector2 earthPosition)
{
	position = pos;
	this->speed = speed;
	this->radius = radius;
	Vector2 distance = earthPosition - position;
	direction = distance.Normalized();
}

void Meteorite::Update()
{
	// ˆÚ“®ˆ—
	position += direction * speed * Time::delta_time;
}

void Meteorite::Draw()
{
	DrawCircle(position.x, position.y, radius, 0xff0000, true);
}

