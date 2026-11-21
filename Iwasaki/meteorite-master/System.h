#pragma once
#include "../../Matsunaga/Vector/Vector.h"
#include "../../Matsunaga/Meteorite/Meteorite.h"
#include "../Time/Time.h"
#include <vector>

class Turret; // 前方宣言

class System {
private:
    std::vector<Meteorite> meteors;  // 隕石の保管
    Turret* turret;                  // 砲台のポインタ
    double limitTime = 60.0;         // 制限時間（初期値60）
    bool isTimeUp = false;           // タイムアップしたかどうかのフラグ
    bool hasInitialized = false;     // 初期化済みフラグ

    void CreateStageMeteors();       // ステージ開始時の固定隕石生成

public:
    System(); // コンストラクタ

    void Init(Vector2 pos, double size, int health); // 初期化
    void Update();                                   // アップデート
    void LoadStage();                                // ステージ読み込み

    // 隕石全体を取得するゲッター
    std::vector<Meteorite>& GetMeteorite() { return meteors; }

    // 砲台をセットするセッター
    void SetTurret(Turret* t) { turret = t; }

    // 制限時間が0になったかどうかを外に教えるゲッター
    bool IsTimeUp() const { return isTimeUp; }
};