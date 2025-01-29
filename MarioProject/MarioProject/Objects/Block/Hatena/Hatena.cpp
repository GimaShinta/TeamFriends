#include "Hatena.h"

#include "../../../Utility/ResourceManager.h"

Hatena::Hatena() :
	 is_kara(false)
{
}

Hatena::~Hatena()
{
}

void Hatena::Initialize()
{
	is_mobility = true;

	//‰æ‘œ‚Ìİ’è
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	hatena_animation = rm->GetImages("Resource/Images/Block/hatena.png", 1, 1, 1, 32, 32);
	image = hatena_animation[0];

	//“–‚½‚è”»’è‚Ìİ’è
	collision.is_blocking = true;
	collision.object_type = eObjectType::eGround;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
}

void Hatena::Draw(const Vector2D& screen_offset) const
{
}

void Hatena::Finalize()
{
	ResourceManager::DeleteInstance();
}
