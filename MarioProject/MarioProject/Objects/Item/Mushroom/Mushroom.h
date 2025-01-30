#pragma once
#include "../ItemBase.h"

// キノコクラス
class Mushroom : public ItemBase
{
public:
	Mushroom();
	~Mushroom();

public:
	// 初期化処理
	virtual void Initialize() override;

	/// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="delta_second">１フレーム当たりの時間</param>
	virtual void Update(float delata_second);

	// 終了時処理
	virtual void Finalize() override;

	/// <summary>
    /// ヒットしたときの処理
    /// </summary>
    /// <param name="hit_object">プレイヤーだとしたら、ここは敵とかブロックと当たったことになる</param>
	virtual void OnHitCollision(GameObjectBase* hit_object);

};

