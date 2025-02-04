#include "ItemBase.h"

ItemBase::ItemBase() :
	g_velocity(0.0f)
{
}

ItemBase::~ItemBase()
{
}

// 初期化処理
void ItemBase::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
/// <returns></returns>
void ItemBase::Update(float delata_second)
{
}

// 終了時処理
void ItemBase::Finalize()
{
}

/// <summary>
/// ヒット時処理
/// </summary>
/// <param name="hit_object">当たった相手</param>
void ItemBase::OnHitCollision(GameObjectBase* hit_object)
{
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
void ItemBase::Movement(float delta_second)
{
	this->location += velocity * delta_second;
}
