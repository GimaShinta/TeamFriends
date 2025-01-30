#pragma once
#include "Brick.h"
// 破壊可能ブロックの破片クラス
class BlickDebris : public BlockBase
{
private:
	float g_velocity;
	float kaiten;

public:
	BlickDebris();
	~BlickDebris();

public:
	// 初期化処理
	void Initialize() override;

	/// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="delata_second">１フレーム当たりの時間</param>
	virtual void Update(float delta_second) override;
};