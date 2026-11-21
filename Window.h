#pragma once
#include "Matsunaga/Vector/Vector.h"

class Window {
public:
	Window() = default;

	void Init(Vector2 size); // 画面のサイズの初期化（仮引数: Vector2）

	Vector2 GetSize() const; // 画面サイズの取得
	int GetColorBitDepth() const; // 画面のカラービット数の取得

private:
	Vector2 size_{}; // 画面のサイズ管理
	int colorBitDepth_ = 32; // 画面のカラービット数管理
};