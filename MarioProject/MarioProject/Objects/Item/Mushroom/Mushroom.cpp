#include "Mushroom.h"

#include "../../../Utility/ResourceManager.h"

Mushroom::Mushroom()
{
}

Mushroom::~Mushroom()
{
}

// 初期化処理
void Mushroom::Initialize()
{
	// 動作フラグのオン
	is_mobility = true;

	//画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Item/mushroom.png", 1, 1, 1, 32, 32)[0];

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eItem;
	collision.hit_object_type.push_back(eObjectType::ePlayer);

	// 当たり判定サイズの設定
	box_size = D_OBJECT_SIZE;
}

// 終了時処理（使ったインスタンスなどの削除）
void Mushroom::Finalize()
{
	ResourceManager::DeleteInstance();
}
