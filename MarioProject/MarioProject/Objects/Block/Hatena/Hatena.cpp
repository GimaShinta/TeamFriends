#include "Hatena.h"

#include "../../../Utility/ResourceManager.h"

Hatena::Hatena()
{
}

Hatena::~Hatena()
{
}

void Hatena::Initialize()
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
}

void Hatena::Draw(const Vector2D& screen_offset) const
{
}
