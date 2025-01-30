#include "Kai.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"

Kai::Kai()
{
}

Kai::~Kai()
{
}

// 初期化処理
void Kai::Initialize()
{
	// 動作フラグのオン
	is_mobility = true;

	//画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Block/kai_block.png", 1, 1, 1, 32, 32)[0];

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eGround;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset"></param>
void Kai::Draw(const Vector2D& screen_offset) const
{
	// 当たり判定の可視化
	DrawBox(location.x - box_size.x, location.y - box_size.y,
		location.x + box_size.x, location.y + box_size.y, GetColor(255, 0, 0), TRUE);
}

// 終了時処理（使ったインスタンスなどの削除）
void Kai::Finalize()
{
	ResourceManager::DeleteInstance();
}
