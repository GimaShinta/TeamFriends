#include "Kai.h"

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
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);

	// 当たり判定サイズの設定
	box_size = D_OBJECT_SIZE;
}

// 終了時処理（使ったインスタンスなどの削除）
void Kai::Finalize()
{
	ResourceManager::DeleteInstance();
}
