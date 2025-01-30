#include "Hatena.h"

#include "../../../Utility/ResourceManager.h"

Hatena::Hatena() :
	 is_kara(false)
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
	hatena_animation = rm->GetImages("Resource/Images/Block/hatena.png", 1, 1, 1, 32, 32);
	image = hatena_animation[0];

	//�����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::eGround;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset"></param>
void Hatena::Draw(const Vector2D& screen_offset) const
{
}

// �I���������i�g�����C���X�^���X�Ȃǂ̍폜�j
void Hatena::Finalize()
{
	ResourceManager::DeleteInstance();
}
