#pragma once
#include "../../Matsunaga/Vector/Vector.h"
//クラス名、関数名はアッパーキャメルケース、変数名はローワースネークケース、ただし、グローバル変数はアッパースネークケース

//弾に関するクラス宣言
class Ammo {
private:
	Vector2 position_;
	double degree_;
	bool flag_;
	double speed_;
	double summon_span_;
	double radius_;
	int last_summon_ammo_id_;
public:
	Ammo();
	Ammo(Vector2 position, double degree);

	////弾をスポーンさせる
	//void SetAmmoSummon();
	//弾の座標を更新する
	void SetAmmoPosition();
	//弾の描画
	void RenderAmmo();
	//弾の諸元情報を渡す
	void GiveAmmoInfo(double* x, double* y, double* radius,bool* flag);
	void GiveAmmoInfo(Vector2* position, double* radius, bool* flag);

	//ここから追加・変更部分
	//弾の消滅
	void DestroyAmmo() { flag_ = false; }

	double Radius() const { return radius_; } //半径の取得
	bool Flag() const { return flag_; } //オブジェクトアクティブフラグの取得
	Vector2 Position() const { return position_; } //位置の取得
};

class DynamicAmmo {
private:
	Vector2 ammo_position;
	bool ammo_flag;
public:
};