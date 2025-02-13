#include "BlockBase.h"
#include "DxLib.h"

BlockBase::BlockBase()
{
}

BlockBase::~BlockBase()
{
}

// 初期化処理
void BlockBase::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delata_second">１フレーム当たりの時間</param>
void BlockBase::Update(float delata_second)
{
	// 親クラスの更新処理
	__super::Update(delata_second);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset"></param>
void BlockBase::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

// 終了時処理
void BlockBase::Finalize()
{
}

/// <summary>
/// ヒット時処理
/// </summary>
/// <param name="hit_object">当たった相手</param>
void BlockBase::OnHitCollision(GameObjectBase* hit_object)
{
}