#pragma once

#include "../BlockBase.h"

// 地面クラス
class Ground : public BlockBase
{
public:
	Ground();
	~Ground();

public:
	// 初期化処理
	void Initialize() override;

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="screen_offset"></param>
	void Draw(const Vector2D& screen_offset)const override;

	// 終了時処理
	void Finalize() override;
};

