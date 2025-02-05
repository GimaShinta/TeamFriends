#include "Kuribo.h"
#include "DxLib.h"

// �V���O���g���p���N���X�̃C���N���[�h
#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"

Kuribo::Kuribo() :
	kuribo_state(eKuriboState::NORMAL)
{
}

Kuribo::~Kuribo()
{
}

// ����������
void Kuribo::Initialize()
{
	// ����T�C�Y�̐ݒ�
	box_size = D_OBJECT_SIZE;
	// �������ǂ����itrue�Ȃ瓮���Afalse�Ȃ�~�܂�j
	is_mobility = true;
	// ���x�̐ݒ�
	velocity.x = -100.0f;

	// �摜�̐ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	kuribo_animation = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32);
	image = kuribo_animation[0];

	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eBlock);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
void Kuribo::Update(float delta_second)
{
	// �N���{�[�̏�ԊǗ�
	switch (kuribo_state)
	{
	case Kuribo::NORMAL:
		// �ړ��̎��s
		__super::Movement(delta_second);
		break;
	case Kuribo::HUMARERU:
		// �Ԃ�Ă���摜�ɐݒ�
		image = kuribo_animation[2];
		// ���S���̃A�j���[�V����
		animation_time += delta_second;
		if (animation_time >= 0.07f)
		{
			animation_time = 0.0f;
			animation_count++;

			// ���S��Ԃɂ���
			if (animation_count >= kuribo_animation.size())
			{
				kuribo_state = eKuriboState::DEAD;
				animation_count = 0;
			}
		}
		break;
	case Kuribo::DEAD:
		// �C���X�^���X�̎擾
		GameObjectManager* rm = Singleton<GameObjectManager>::GetInstance();
		// �N���{�[�̍폜
		rm->DestroyGameObject(this);
		break;
	}

	// �e�N���X�̍X�V�������Ăяo��
	__super::Update(delta_second);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset"></param>
void Kuribo::Draw(const Vector2D& screen_offset) const
{
	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
	//// �����蔻��̉���
	//DrawBox(this->location.x - this->box_size.x, this->location.y - this->box_size.y,
	//	this->location.x + this->box_size.x, this->location.y + this->box_size.y, GetColor(255, 0, 0), TRUE);
}

// �I���������i�g�����C���X�^���X�Ȃǂ̍폜�j
void Kuribo::Finalize()
{
	ResourceManager::DeleteInstance();
	GameObjectManager::DeleteInstance();
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="hit_object">������������</param>
void Kuribo::OnHitCollision(GameObjectBase* hit_object)
{
	// �C���X�^���X�̎擾
	GameObjectManager* rm = Singleton<GameObjectManager>::GetInstance();
	// �}���I�ɓ���������
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		// �������~�߂�
		is_mobility = false;
		// �N���{�[�̏�ɐG�ꂽ��
		if (hit_object->GetVelocity().y > 0.0f)
		{
			// enum���Ȃɂ��Ŏ��񂾏�Ԃɂ���̂���������

			// �}���I���W�����v������
			hit_object->SetVelocity(Vector2D(hit_object->GetVelocity().x, -1500));

			// �N���{�[�𓥂܂ꂽ��Ԃɂ���
			kuribo_state = eKuriboState::HUMARERU;
		}
		// �N���{�[�̏�ȊO�ɐG�ꂽ��
		else
		{
			rm->DestroyGameObject(hit_object);
		}
	}
}