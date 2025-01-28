#include "Kuribo.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"

Kuribo::Kuribo()
{
}

Kuribo::~Kuribo()
{
}

// ����������
void Kuribo::Initialize()
{
	// ����T�C�Y�̐ݒ�
	box_size = Vector2D(24.0f);
	is_mobility = true;
	velocity.x = 100.0f;

	// �摜�̐ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32)[0];

	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
}

// �X�V����
void Kuribo::Update(float delta_second)
{
	// �ړ��̎��s
	location.x -= velocity.x * delta_second;

	// �e�N���X�̍X�V�������Ăяo��
	__super::Update(delta_second);
}

// �`�揈��
void Kuribo::Draw(const Vector2D& screen_offset) const
{
	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

// �I���������i�g�����C���X�^���X�Ȃǂ̍폜�j
void Kuribo::Finalize()
{
	ResourceManager::DeleteInstance();
}

//�q�b�g������
void Kuribo::OnHitCollision(GameObjectBase* hit_object)
{
}