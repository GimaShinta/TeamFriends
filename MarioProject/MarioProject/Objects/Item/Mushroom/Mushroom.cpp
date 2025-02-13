#include "Mushroom.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"

Mushroom::Mushroom()
{
}

Mushroom::~Mushroom()
{
}

// ����������
void Mushroom::Initialize()
{
	// ����t���O�̃I��
	is_mobility = true;

	//�摜�̐ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Item/mushroom.png", 1, 1, 1, 32, 32)[0];

	//�����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::eItem;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eBlock);

	// �����蔻��T�C�Y�̐ݒ�
	box_size = D_OBJECT_SIZE;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
void Mushroom::Update(float delta_second)
{
	// �o�����Ă��Ȃ�������
	if (is_appearance == false)
	{
		// ��������ɏグ�ďo�����Ă���悤��
		// �o���ʒu����}�X��܂ŏグ��
		if (location.y < ((D_OBJECT_SIZE * 2) * 9) - D_OBJECT_SIZE)
		{
			location.y = ((D_OBJECT_SIZE * 2) * 9) - D_OBJECT_SIZE;
			// ���B������ړ������̃t���O���I��
			is_appearance = true;
		}
	}
	// �o�����Ă�����
	else
	{
		// ���x�̐ݒ�
		velocity = Vector2D(100, 0);
		//�d�͑��x�̌v�Z
		g_velocity += D_GRAVITY;
		velocity.y += g_velocity * delta_second;
	}

	// �ړ�����
	__super::Movement(delta_second);
}

// �I���������i�g�����C���X�^���X�Ȃǂ̍폜�j
void Mushroom::Finalize()
{
	ResourceManager::DeleteInstance();
	GameObjectManager::DeleteInstance();
}

/// <summary>
/// �q�b�g������
/// </summary>
/// <param name="hit_object">������������</param>
void Mushroom::OnHitCollision(GameObjectBase* hit_object)
{
	// �}���I�ɓ���������
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		// �}���I�̐i�s�������ゾ������
		if (hit_object->GetVelocity().y < 0.0f)
		{
			// �������x�̐ݒ�
			velocity.y -= 100;
		}
	}
}