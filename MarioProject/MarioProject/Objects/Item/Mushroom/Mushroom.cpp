#include "Mushroom.h"

#include "../../../Utility/ResourceManager.h"

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

	// �����蔻��T�C�Y�̐ݒ�
	box_size = D_OBJECT_SIZE;

	velocity.x = 100;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
void Mushroom::Update(float delta_second)
{
	__super::Movement(delta_second);
}

// �I���������i�g�����C���X�^���X�Ȃǂ̍폜�j
void Mushroom::Finalize()
{
	ResourceManager::DeleteInstance();
}

/// <summary>
/// �q�b�g������
/// </summary>
/// <param name="hit_object">������������</param>
void Mushroom::OnHitCollision(GameObjectBase* hit_object)
{
}