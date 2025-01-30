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
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset"></param>
void BlockBase::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
	// 当たり判定の可視化
	DrawBox(this->location.x - this->box_size.x, this->location.y - this->box_size.y,
		this->location.x + this->box_size.x, this->location.y + this->box_size.y, GetColor(255, 0, 0), TRUE);
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