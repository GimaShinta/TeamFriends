#include "Kai.h"

#include "../../../Utility/ResourceManager.h"

Kai::Kai()
{
}

Kai::~Kai()
{
}

// ����������
void Kai::Initialize()
{
	// ����t���O�̃I��
	is_mobility = true;

	//�摜�̐ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Block/kai_block.png", 1, 1, 1, 32, 32)[0];

	//�����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);

	// �����蔻��T�C�Y�̐ݒ�
	box_size = D_OBJECT_SIZE;
}

// �I���������i�g�����C���X�^���X�Ȃǂ̍폜�j
void Kai::Finalize()
{
	ResourceManager::DeleteInstance();
}
