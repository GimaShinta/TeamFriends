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
	// �����������肪�}���I��������
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		// �}���I�̐i�s�������ゾ������
		if (hit_object->GetVelocity().y < -1.0f)
		{
			// �}���I�����~������
			hit_object->SetVelocity(Vector2D(hit_object->GetVelocity().x, 1.0f));
			// �󂶂�Ȃ�������
			if (is_kara == false)
			{
				// ��ɂȂ�
				is_kara = true;
			}
		}
	}
}
