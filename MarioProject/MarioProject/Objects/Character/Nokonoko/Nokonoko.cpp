#include "Nokonoko.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"

Nokonoko::Nokonoko() :
	noko_state(eNokonokoState::NORMAL)
	, revival_size(0.0f)
{
}

Nokonoko::~Nokonoko()
{
}

// ����������
void Nokonoko::Initialize()
{
	// ����T�C�Y�̐ݒ�
	box_size = Vector2D(D_OBJECT_SIZE, D_OBJECT_SIZE);
	// �������ǂ����itrue�Ȃ瓮���Afalse�Ȃ�~�܂�j
	is_mobility = true;
	// ���x�̐ݒ�
	velocity.x = -100.0f;

	// �摜�̐ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	nokonoko_animation = rm->GetImages("Resource/Images/Enemy/nokonoko.png", 2, 2, 1, 32, 64);
	revival_animation = rm->GetImages("Resource/Images/Enemy/nokonoko_revival.png", 2, 2, 1, 32, 32);

	// �����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
void Nokonoko::Update(float delta_second)
{
	switch (noko_state)
	{
	case Nokonoko::NORMAL:
		// �ړ��̎��s
		__super::Movement(delta_second);
		image = nokonoko_animation[0];
		break;
	case Nokonoko::REVIVAL:
		image = revival_animation[0];
		break;
	case Nokonoko::DEAD:
		break;
	default:
		break;
	}


	// �e�N���X�̍X�V�������Ăяo��
	__super::Update(delta_second);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset"></param>
void Nokonoko::Draw(const Vector2D& screen_offset) const
{
	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

// �I���������i�g�����C���X�^���X�Ȃǂ̍폜�j
void Nokonoko::Finalize()
{
	ResourceManager::DeleteInstance();
}

/// <summary>
/// �q�b�g�������̏���
/// </summary>
/// <param name="hit_object">������������</param>
void Nokonoko::OnHitCollision(GameObjectBase* hit_object)
{
	// �C���X�^���X�̎擾
	GameObjectManager* rm = Singleton<GameObjectManager>::GetInstance();
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		// �m�R�m�R�̏�ɐG�ꂽ��
		if (hit_object->GetVelocity().y > 1000.0f)
		{
			noko_state = eNokonokoState::REVIVAL;
			// �}���I���W�����v������
			hit_object->SetVelocity(Vector2D(hit_object->GetVelocity().x, -1500));
		}
		// �m�R�m�R�̏�ȊO�ɐG�ꂽ��
		else
		{
			// �}���I���폜����
			rm->DestroyGameObject(hit_object);
		}
	}
}