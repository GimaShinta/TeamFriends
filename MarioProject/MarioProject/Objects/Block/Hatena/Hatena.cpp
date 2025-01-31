#include "Hatena.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"
#include "../../../Objects/Item/Mushroom/Mushroom.h"

Hatena::Hatena() :
	 is_kara(false)
	, kara_image(NULL)
{
}

Hatena::~Hatena()
{
}
 
// ����������
void Hatena::Initialize()
{
	// ����t���O�̃I��
	is_mobility = true;

	//�摜�̐ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	hatena_animation = rm->GetImages("Resource/Images/Block/hatena.png", 4, 4, 1, 32, 32);
	kara_image = rm->GetImages("Resource/Images/Block/kara_block.png")[0];
	image = hatena_animation[0];

	//�����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);

	// �����蔻��T�C�Y�̐ݒ�
	box_size = D_OBJECT_SIZE;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delata_second">�P�t���[��������̎���</param>
void Hatena::Update(float delata_second)
{
	// ��ɂȂ�����
	if (is_kara == true)
	{
		// ��u���b�N�̉摜�ɂ���
		image = kara_image;
	}
	else
	{
		image = hatena_animation[0];
	}
}

// �I���������i�g�����C���X�^���X�Ȃǂ̍폜�j
void Hatena::Finalize()
{
	ResourceManager::DeleteInstance();
}

/// <summary>
/// �q�b�g������
/// </summary>
/// <param name="hit_object">������������</param>
void Hatena::OnHitCollision(GameObjectBase* hit_object)
{
	// �����������肪�}���I�������炩�A�}���I�̐i�s�������ゾ������
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		if (hit_object->GetVelocity().y < -1.0f)
		{
			// �}���I�����~������
			hit_object->SetVelocity(Vector2D(hit_object->GetVelocity().x, 1.0f));
			// �󂶂�Ȃ�������
			if (is_kara == false)
			{
				// �C���X�^���X�̎擾
				GameObjectManager* gm = Singleton<GameObjectManager>::GetInstance();
				// �L�m�R�̐���
				gm->CreateObject<Mushroom>(location);
				// ��ɂȂ�
				is_kara = true;
			}
		}
		//else if(hit_object->GetVelocity().x > 1.0f)
		//{
		//	// �}���I�����~������
		//	hit_object->SetVelocity(Vector2D(0.0f, hit_object->GetVelocity().y));
		//}
		//else if(hit_object->GetVelocity().x < -1.0f)
		//{
		//	// �}���I�����~������
		//	hit_object->SetVelocity(Vector2D(0.0f, hit_object->GetVelocity().y));
		//}
	}
}