#include "Coin.h"

#include "../../../Utility/ResourceManager.h"

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
	image = rm->GetImages("Resource/Images/Item/coin.png", 1, 1, 1, 32, 32)[0];

	//�����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::eItem;
	collision.hit_object_type.push_back(eObjectType::ePlayer);

	// �����蔻��T�C�Y�̐ݒ�
	box_size = D_OBJECT_SIZE;
}

// �I���������i�g�����C���X�^���X�Ȃǂ̍폜�j
void Coin::Finalize()
{
	ResourceManager::DeleteInstance();
}
