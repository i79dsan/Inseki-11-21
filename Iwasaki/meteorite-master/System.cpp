#include "DxLib.h"
#include "System.h"
#include "../../Itou/ContentCreation2026_10_19/Ammo.h"
#include "../../Itou/ContentCreation2026_10_19/Turret.h"
#include <cmath>

namespace {
	// 画面の中心座標（砲台・中心位置）
	constexpr double CENTER_X = 360.0;
	constexpr double CENTER_Y = 360.0;
	constexpr double PI = 3.14159265358979323846;

	// 固定の隕石データ：{ 角度(度), 砲台(中心)からの距離 }
	constexpr double METEOR_SPAWN_TABLE[][2] = {
		{   0.0, 180.0 },
		{  45.0, 200.0 },
		{  90.0, 220.0 },
		{ 135.0, 240.0 },
		{ 180.0, 180.0 },
		{ 225.0, 200.0 },
		{ 270.0, 220.0 },
		{ 315.0, 240.0 },
	};

	// デバッグ確認用：先頭隕石の生成時座標
	Vector2 debugInitPos0(0.0, 0.0);
}

// コンストラクタ
System::System() {
	turret = nullptr;
	limitTime = 60.0;
	isTimeUp = false;
	hasInitialized = false;
}

void System::CreateStageMeteors() {
	meteors.clear();

	const int meteorCount = static_cast<int>(sizeof(METEOR_SPAWN_TABLE) / sizeof(METEOR_SPAWN_TABLE[0]));
	meteors.reserve(meteorCount);

	const double fixedSpeed = 55.0;
	const int meteorRadius = 30;
	const Vector2 centerPos(CENTER_X, CENTER_Y);

	for (int i = 0; i < meteorCount; ++i) {
		const double degree = METEOR_SPAWN_TABLE[i][0];
		const double distance = METEOR_SPAWN_TABLE[i][1];
		const double radian = degree * PI / 180.0;

		Vector2 spawnPos;
		spawnPos.x = CENTER_X + std::cos(radian) * distance;
		spawnPos.y = CENTER_Y + std::sin(radian) * distance;

		if (i == 0) {
			debugInitPos0 = spawnPos;
		}

		Meteorite meteor(spawnPos, fixedSpeed, meteorRadius, centerPos);
		meteors.push_back(meteor);
	}
}

void System::Init(Vector2 pos, double size, int health) {
	Time::Update();
	limitTime = 60.0;
	isTimeUp = false;
	hasInitialized = true;
	CreateStageMeteors();
}
//
void System::LoadStage() {
	Time::Update();
	limitTime = 60.0;
	isTimeUp = false;
	hasInitialized = true;
	CreateStageMeteors();
}

void System::Update() {
	if (!hasInitialized) {
		Time::Update();
		limitTime = 60.0;
		isTimeUp = false;
		hasInitialized = true;
		CreateStageMeteors();
	}

	// --- 1. 時間管理の処理 ---
	double deltaTime = Time::delta_time;
	if (!isTimeUp) {
		double clampedDelta = deltaTime;
		if (clampedDelta < 0.0) {
			clampedDelta = 0.0;
		}
		if (clampedDelta > 0.1) {
			clampedDelta = 0.1;
		}

		limitTime -= clampedDelta;

		if (limitTime <= 0.0) {
			limitTime = 0.0;
			isTimeUp = true;
		}
	}

	// --- 2. 隕石の更新と描画 ---
	// 異常な delta_time で隕石がワープしないよう、更新時のみ上限を設ける
	const double savedDeltaTime = Time::delta_time;
	double safeMeteorDelta = savedDeltaTime;
	if (safeMeteorDelta < 0.0) {
		safeMeteorDelta = 0.0;
	}
	if (safeMeteorDelta > 0.1) {
		safeMeteorDelta = 0.1;
	}
	Time::delta_time = safeMeteorDelta;

	for (auto meteoriteIt = meteors.begin(); meteoriteIt != meteors.end(); ++meteoriteIt) {
		meteoriteIt->Update();
		meteoriteIt->Draw();
	}

	Time::delta_time = savedDeltaTime;

	// デバッグ表示：生成時座標と現在座標を比較
	//DrawFormatString(50, 110, GetColor(0, 255, 255),
	//	"init0: (%.1f, %.1f)", debugInitPos0.x, debugInitPos0.y);

	//if (!meteors.empty()) {
	//	Vector2 p0 = meteors[0].Position();
	//	DrawFormatString(50, 80, GetColor(255, 255, 0),
	//		"m0: (%.1f, %.1f) dt: %.5f", p0.x, p0.y, deltaTime);
	//}

	// --- 3. 弾のゲッター取得 ---
	if (turret != nullptr) {
		std::vector<Ammo>& ammoList = turret->GiveAmmo();
		(void)ammoList;
	}

	// --- 4. 残り時間の画面表示 ---
	int displayTime = (int)limitTime;
	DrawFormatString(50, 50, GetColor(255, 255, 255), "残り時間: %d秒", displayTime);
}