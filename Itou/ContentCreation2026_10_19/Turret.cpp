#include "Turret.h"
#include "Ammo.h"
#include "Dxlib.h"
#include "../../Iwasaki/Time/Time.h"

#include <cmath>

using namespace std;
//関数名、クラス名はアッパーキャメルケース、変数名はローワースネークケース、ただし、グローバル変数はアッパースネークケース
//プレイヤーに関するクラス定義

////////////////////////////////////////////////////////////////////
//コンストラクタ
Turret::Turret() :
	position_(0.0, 0.0), center_position_(0.0, 0.0), move_radius_(100.0), move_clockwise_(false),
move_counter_clockwise_(false), degree_(0), speed_(1.0), input_shoot_(false){}

////////////////////////////////////////////////////////////////////
void Turret::InitTurretPosition() {
	center_position_ = Vector2(720 / 2, 720 / 2);
	position_ = Vector2(center_position_.x, center_position_.y - move_radius_); //タレットの初期座標設定

	degree_ = 90;
}

//プレイヤーのインプットを受け取る
void Turret::InputTurretPosition() {
	if (m_input.GetKey(KEY_INPUT_D) == 1) {
		move_clockwise_ = true;
	}
	if (m_input.GetKey(KEY_INPUT_A) == 1) {
		move_counter_clockwise_ = true;
	}
}

void Turret::UpdateTurretPosition() {
	m_input.Update();

	if (move_clockwise_) {
		degree_ -= 72 * Time::delta_time;
		move_clockwise_ = false;
	}
	if (move_counter_clockwise_) {
		degree_ += 72 * Time::delta_time;
		move_counter_clockwise_ = false;
	}

	double radian = cos(degree_ / 180 * 3.141592 * speed_), radian2 = sin(degree_ / 180 * 3.141592 * speed_);

	position_.x = (radian * move_radius_ + center_position_.x);
	position_.y = ( -radian2 * move_radius_ + center_position_.y);
	
	int size = ammoes_.size();
	for (int i = 0; i < ammoes_.size(); i++) {
		ammoes_[i].SetAmmoPosition();
		ammoes_[i].RenderAmmo();
	}
}

//プレイヤーのX座標情報を渡す
double Turret::GiveTurretPositionX() {
	return position_.x;
}

//プレイヤーのY座標情報を渡す
double Turret::GiveTurretPositionY() {
	return position_.y;
}

Vector2 Turret::GiveTurretPosition() {
	return position_;
}

//プレイヤーの偏角を渡す
double Turret::GiveTurretDegree() {
	return degree_;
}

void Turret::InputTurretShoot() {
	//プレイヤーの発射入力を検知する
	if (m_input.GetKeyDown(KEY_INPUT_SPACE) == 1) {
		Ammo ammo(position_, degree_);
		ammoes_.push_back(ammo);
	}
}

//temp
void Turret::RenderTurretAndTurretCenterPoint() {
	//プレイヤーとプレイヤーの移動の中心を描画
	DrawPixel(center_position_.x, center_position_.y, 0xffffff);
	DrawPixel(position_.x, position_.y, 0xffffff);
	DrawCircle(center_position_.x, center_position_.y, 3, 0xffffff, true);
	DrawCircle(position_.x, position_.y, 3, 0xffffff, true);
}
