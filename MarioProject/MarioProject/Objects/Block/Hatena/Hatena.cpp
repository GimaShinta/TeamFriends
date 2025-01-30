#include "Hatena.h"

#include "../../../Utility/ResourceManager.h"

Hatena::Hatena() :
	 is_kara(false)
{
}

Hatena::~Hatena()
{
}

// 初期化処理
void Hatena::Initialize()
{
	// 動作フラグのオン
	is_mobility = true;

	//画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	hatena_animation = rm->GetImages("Resource/Images/Block/hatena.png", 4, 4, 1, 32, 32);
	image = hatena_animation[0];

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eGround;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);

	// 当たり判定サイズの設定
	box_size = D_OBJECT_SIZE;
}

// 終了時処理（使ったインスタンスなどの削除）
void Hatena::Finalize()
{
	ResourceManager::DeleteInstance();
}
