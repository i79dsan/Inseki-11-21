#pragma once
#include "../Vector/Vector.h"

class Meteorite
{
public:
	Meteorite(Vector2 pos, double speed, int radius, Vector2 earthPosition);
	//~Meteorite();
	void Update();
	void Draw();
	//void Destroy();

	//追加・変更部分
	int Radius() const { return radius; } /*半径の取得*/
	Vector2 Position() const { return position; } /*位置の取得*/
private:
	Vector2 position;
	Vector2 direction;
	double speed;
	int radius;
};