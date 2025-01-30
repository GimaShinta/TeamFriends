#pragma once
#include "../GameObjectBase.h"

#define D_GRAVITY (30.0f)    //重力加速度(m/ss)

// アイテム基底クラス
class ItemBase : public GameObjectBase
{
protected:
	float g_velocity;       // 重力

public:
	ItemBase();
	~ItemBase();

public:
	// 初期化処理
	virtual void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">１フレーム当たりの時間</param>
	/// <returns></returns>
	virtual void Update(float delata_second);

	// 終了時処理
	virtual void Finalize() override;

	/// <summary>
	/// ヒットしたときの処理
	/// </summary>
	/// <param name="hit_object">プレイヤーだとしたら、ここは敵とかブロックと当たったことになる</param>
	virtual void OnHitCollision(GameObjectBase* hit_object);

	/// <summary>
    /// 移動処理
    /// </summary>
    /// <param name="delta_second">１フレーム当たりの時間</param>
	virtual void Movement(float delta_second);
};

