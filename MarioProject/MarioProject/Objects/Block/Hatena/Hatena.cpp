#include "Hatena.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"

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
void Hatena::Update(float delta_second)
{
	// ��ɂȂ�����
	if (is_kara == true)
	{
		// ��u���b�N�̉摜�ɂ���
		image = kara_image;
	}
	else
	{
		// �A�j���[�V����
		GameObjectBase::AnimationControl(delta_second, hatena_animation, hatena_animation_num, 6.0f);
	}

	// ��}�X��ɓ��B������ړ����]
	if (location.y < old_location.y - D_OBJECT_SIZE)
	{
		velocity.y *= -1;
	}

	// �����ʒu�ɖ߂�
	if (location.y > old_location.y)
	{
		location.y = old_location.y;
		velocity = 0;
	}

	// �ړ�����
	location += velocity * delta_second;
}

// �I���������i�g�����C���X�^���X�Ȃǂ̍폜�j
void Hatena::Finalize()
{
	ResourceManager::DeleteInstance();
	GameObjectManager::DeleteInstance();
}

/// <summary>
/// �q�b�g������
/// </summary>
/// <param name="hit_object">������������</param>
void Hatena::OnHitCollision(GameObjectBase* hit_object)
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
				// ��ɏ㏸������
				velocity.y -= 500;
				// ��ɂȂ�
				is_kara = true;
			}
		}
	}
}