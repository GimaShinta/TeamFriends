#include "Ground.h"

#include "../../../Utility/ResourceManager.h"

Ground::Ground()
{
}

Ground::~Ground()
{
}

// ‰Šú‰»ˆ—
void Ground::Initialize()
{
	is_mobility = true;

	//‰æ‘œ‚Ìİ’è
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Block/floor.png", 1, 1, 1, 32, 32)[0];

	//“–‚½‚è”»’è‚Ìİ’è
	collision.is_blocking = true;
	collision.object_type = eObjectType::eGround;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
}

void Ground::Finalize()
{
	ResourceManager::DeleteInstance();
}
