#include "BlockBase.h"

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

/// <summary>
/// ゲームオジェクトのサイズ変更
/// </summary>
/// <param name="x_size">xのサイズ</param>
/// <param name="y_size">yのサイズ</param>
void BlockBase::SetSizeData(int x_size, int y_size)
{
	box_size.x = x_size * D_OBJECT_SIZE;
	box_size.y = y_size * D_OBJECT_SIZE;
}