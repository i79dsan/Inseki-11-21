#include	"../h/ResultState.h"
#include	"../h/GameState.h"

#include	"../Iwasaki/Time/Time.h"

#include	"../Iwasaki/Collision/Collision.h"

using namespace std;

void GameState::Enter() {
	m_turret.InitTurretPosition(); //砲台の位置の初期化
}

StateBase* GameState::Loop() {
	Time::Update();

	DrawString(0, 0, "Game", 0xffffff);

	m_turret.InputTurretPosition(); //プレイヤーの入力処理による移動
	m_turret.InputTurretShoot(); //プレイヤーの入力処理による弾発射
	m_turret.UpdateTurretPosition(); //砲台と弾の移動更新
	m_turret.RenderTurretAndTurretCenterPoint(); //砲台と弾の描画処理

	m_system.Update(); //システムの更新


	//ここをiwaがかきかえ::::::::::::::::::::::::::::::::
	if (m_system.IsTimeUp()) {
		return new ResultState(true); // 制限時間が0になったら勝利(true)でリザルトへ！
	}
	//:::::::::::::::::::::::::::::::::::::::::::::::::::::

	std::vector<Ammo>& ammos = m_turret.GiveAmmo(); //弾の取得
	std::vector<Meteorite>& meteorites = m_system.GetMeteorite(); //隕石の取得

	for (int i = 0; i < m_turret.GiveAmmo().size(); i++) {
		Vector2 pos = m_turret.GiveAmmo(i).Position();
		double radius = m_turret.GiveAmmo(i).Radius();
		bool flag = m_turret.GiveAmmo(i).Flag();

		if (!flag) continue;

		for (auto ammo = ammos.begin(); ammo != ammos.end(); )
		{
			bool isCollision = false;

			for (auto meteorite = meteorites.begin(); meteorite != meteorites.end(); )
			{
				//弾と隕石の当たり判定
				if (Collision::CircleAndCircle((ammo)->Position(), (ammo)->Radius(), (meteorite)->Position(), (meteorite)->Radius()))
				{
					meteorite = meteorites.erase(meteorite);
					int size = meteorites.size();

					ammo->DestroyAmmo();
					ammo = ammos.erase(ammo);
					int size2 = ammos.size();

					isCollision = true;

					break;
				}
				else
				{
					meteorite++;
				}
			}
			if (!isCollision)
			{
				ammo++;
			}
		}
	}

	if (m_turret.GiveInput().GetKeyDown(KEY_INPUT_RETURN)) return new ResultState(false);

	return this;
}

void GameState::Exit() {

}