#include "ItemHatena.h"
#include "../../../Objects/GameObjectManager.h"
#include "../../../Objects/Item/Mushroom/Mushroom.h"

ItemHatena::ItemHatena()
{
}

ItemHatena::~ItemHatena()
{
}

void ItemHatena::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たった相手がマリオだったら
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		// マリオの進行方向が上だったら
		if (hit_object->GetVelocity().y < -1.0f)
		{
			// マリオを下降させる
			hit_object->SetVelocity(Vector2D(hit_object->GetVelocity().x, 1.0f));
			// 空じゃなかったら
			if (is_kara == false)
			{
				// 空になる
				is_kara = true;
			}
		}
	}
}
