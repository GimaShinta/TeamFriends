#include "Coin.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"

Coin::Coin()
{
}

Coin::~Coin()
{
}

// ����������
void Coin::Initialize()
{
	// ����t���O�̃I��
	is_mobility = true;

	//�摜�̐ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Item/coin.png", 4, 4, 1, 32, 32)[0];

	//�����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::eItem;
	collision.hit_object_type.push_back(eObjectType::ePlayer);

	// �����蔻��T�C�Y�̐ݒ�
	box_size = D_OBJECT_SIZE;

	//// ��ɔ�΂�
	//velocity.y -= 700.0f;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
void Coin::Update(float delta_second)
{
	// �o��������
	if (is_appearance == true)
	{
		// �d�͑��x�̌v�Z
		g_velocity += D_GRAVITY;
		velocity.y += g_velocity * delta_second;
	}

	// ���ɗ����Ă���Ƃ�
	if (velocity.y > 1000.0f)
	{
		// �C���X�^���X�̎擾
		GameObjectManager* gm = Singleton<GameObjectManager>::GetInstance();
		// ���g���폜
		gm->DestroyGameObject(this);
	}

	// �e�N���X�̈ړ�����
	__super::Movement(delta_second);
}

// �I���������i�g�����C���X�^���X�Ȃǂ̍폜�j
void Coin::Finalize()
{
	ResourceManager::DeleteInstance();
	GameObjectManager::DeleteInstance();
}

/// <summary>
/// �q�b�g������
/// </summary>
/// <param name="hit_object">������������</param>
void Coin::OnHitCollision(GameObjectBase* hit_object)
{
	// �}���I�ɓ���������
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		// �}���I�̐i�s�������ゾ������
		if (hit_object->GetVelocity().y < 0.0f)
		{
			// �������x�̐ݒ�
			velocity.y -= 1000;
			is_appearance = true;
		}
	}
}