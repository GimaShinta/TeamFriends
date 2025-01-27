#include "CharacterBase.h"

#define D_GRAVITY (30.0f)      //�d�͉����x(m/ss)

CharacterBase::CharacterBase():
	  velocity(0.0f)
	, g_velocity(0.0f)
{
}

CharacterBase::~CharacterBase()
{
}

// ����������
void CharacterBase::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delata_second">1�t���[��������̎���</param>
void CharacterBase::Update(float delata_second)
{
	// �e�N���X�̍X�V�������Ăяo��
	__super::Update(delata_second);
}

// �`�揈��
void CharacterBase::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

// �I��������
void CharacterBase::Finalize()
{
}

// �q�b�g������
void CharacterBase::OnHitCollision(GameObjectBase* hit_object)
{
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
void CharacterBase::Movement(float delta_second)
{
	location += velocity * delta_second;
}

/// <summary>
/// �X�N���[���ɍ��킹�ĉ���������
/// </summary>
/// <param name="velocity">this�I�u�W�F�N�g�̑��x</param>
void CharacterBase::SetVelocity(const Vector2D& velocity)
{
	this->velocity = velocity;
}
