#include "Ammo.h"
#include "Turret.h"
#include	"../../Iwasaki/Time/Time.h"
#include <cmath>
#include "Dxlib.h"
//クラス名、関数名はアッパーキャメルケース、変数名はローワースネークケース、ただし、グローバル変数はアッパースネークケース
//弾に関するクラス定義

/////////////////////////////////////////////////////////////////////
//コンストラクタ
Ammo::Ammo() : position_(0.0, 0.0),degree_(0.0),flag_(true),
last_summon_ammo_id_(0),speed_(1.0), summon_span_(14.0), radius_(10.0){}

Ammo::Ammo(Vector2 position, double degree) : position_(position),degree_(degree), flag_(true),
last_summon_ammo_id_(0), speed_(50.0), summon_span_(14.0), radius_(10.0){}
/////////////////////////////////////////////////////////////////////

//弾の座標を更新する
void Ammo::SetAmmoPosition() {
	if (flag_) {
		double v1 = cos(degree_ / 180 * 3.141592) * speed_ * Time::delta_time;
		double v2 = sin(degree_ / 180 * 3.141592) * speed_ * Time::delta_time;
		position_.x += v1;
		position_.y -= v2;
	}
}

void Ammo::RenderAmmo() {
	//弾の描画
	if (flag_) DrawCircle(position_.x, position_.y, radius_, 0x0000ff, true);
}

void Ammo::GiveAmmoInfo(double* x, double *y, double* radius,bool* flag) {
	*x = position_.x;
	*y = position_.y;
	*radius = radius_;
	*flag = flag_;
}

void Ammo::GiveAmmoInfo(Vector2* position, double* radius, bool* flag) {
	*position = position_;
	*radius = radius_;
	*flag = flag_;

}