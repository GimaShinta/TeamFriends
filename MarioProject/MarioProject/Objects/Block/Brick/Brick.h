#pragma once
#include "../BlockBase.h"

// 破壊可能ブロック
class Brick :
    public BlockBase
{
public:
	Brick();
	~Brick();

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

