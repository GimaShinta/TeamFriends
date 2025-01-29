#include "Brick.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"

Brick::Brick()
{
}

Brick::~Brick()
{
}

void Brick::Initialize()
{
	is_mobility = true;

	//âÊëúÇÃê›íË
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Block/floor.png", 1, 1, 1, 32, 32)[0];

	//ìñÇΩÇËîªíËÇÃê›íË
	collision.is_blocking = true;
	collision.object_type = eObjectType::eGround;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
}

void Brick::Draw(const Vector2D& screen_offset) const
{
	DrawBox(location.x - box_size.x, location.y - box_size.y,
		location.x + box_size.x, location.y + box_size.y, GetColor(255, 0, 0), TRUE);
}
