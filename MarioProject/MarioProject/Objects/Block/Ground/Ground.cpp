#include "Ground.h"

#include "../../../Utility/ResourceManager.h"

Ground::Ground()
{
}

Ground::~Ground()
{
}

// 初期化処理
void Ground::Initialize()
{
	is_mobility = true;

	//画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Block/floor.png", 1, 1, 1, 32, 32)[0];

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eGround;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eItem);
}


// 終了時処理（使ったインスタンスなどの削除）
void Ground::Finalize()
{
	ResourceManager::DeleteInstance();
}
