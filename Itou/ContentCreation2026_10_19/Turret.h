#pragma once
#include	<vector>
#include	"../../Matsunaga/Input/Input.h"
#include	"Ammo.h"
#include	"../../Matsunaga/Vector/Vector.h"

//クラス名、関数名はアッパーキャメルケース、変数名はローワースネークケース、ただし、グローバル変数はアッパースネークケース
//プレイヤーに関するクラス宣言

class Turret {
private:
	Vector2 position_;
	Vector2 center_position_;
	double move_radius_;
	bool move_clockwise_;
	bool move_counter_clockwise_;
	//turret_degreeは度数法であって弧度法ではない
	double degree_;
	double speed_;
	bool input_shoot_;

	Input m_input;

	std::vector<Ammo> ammoes_;
public:
	//コンストラクタ
	Turret();
	//砲台の初期座標設定
	void InitTurretPosition();
	//プレイヤーのインプットを受け取る
	void InputTurretPosition();
	//プレイヤーの位置更新
	void UpdateTurretPosition();
	//プレイヤーのX座標情報を渡す
	double GiveTurretPositionX();
	//プレイヤーののY座標情報を渡す
	double GiveTurretPositionY();
	//プレイヤーの座標情報を渡す
	Vector2 GiveTurretPosition();
	//プレイヤーの偏角を渡す
	double GiveTurretDegree();

	//ここから追加・変更部分
	const Ammo& GiveAmmo(int ID) { return ammoes_[ID]; } /*弾を取得する*/
	std::vector<Ammo>& GiveAmmo() { return ammoes_; } /*弾全体を取得する*/

	Input GiveInput() { return m_input; } /*入力処理を取得する*/
	//ここまで

	//プレイヤーの発射入力を検知する
	void InputTurretShoot();
	//プレイヤーとプレイヤーの移動の中心を表示する
	void RenderTurretAndTurretCenterPoint();
};