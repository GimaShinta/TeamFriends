#include "Player.h"

#include "../../../Utility/ResourceManager.h"
#include "StateBase/State/PlayerStateFactory.h"

#include "DxLib.h"

#define D_GRAVITY (30.0f)      //�d�͉����x(m/ss)

Player::Player():
	  flip_flag(false)
	, now_state(ePlayerState::NONE)
	, next_state(ePlayerState::NONE)
{
}

Player::~Player()
{
}

// ����������
void Player::Initialize()
{
	// �l�̏�����
	state = PlayerStateFactory::Get((*this), ePlayerState::IDLE);

	// ���\�[�X�}�l�[�W���[�̃C���X�^���X�̎擾�irm�ɂ̓��\�[�X�}�l�[�W���[�N���X�ɃA�N�Z�X�ł���A�h���X������j
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	/* GetImages�͉摜��؂蕪���Ĕz��ɓ���Ă����֐������ǁA�������image�ϐ��͔z��ϐ�����Ȃ�����
	 �摜��1��������Ȃ����߁A�����̌��[0]������*/
	image = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32)[0];

	// �����蔻��̃I�u�W�F�N�g�ݒ�
	collision.is_blocking = true;
	// �����̃I�u�W�F�N�g�^�C�v
	collision.object_type = eObjectType::ePlayer;
	// �����鑊��̃I�u�W�F�N�g�^�C�v
	collision.hit_object_type.push_back(eObjectType::eEnemy);

	is_mobility = true;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delata_second">�P�t���[��������̎���</param>
void Player::Update(float delta_second)
{
	// state�̕ύX����
	if (next_state != ePlayerState::NONE && is_mobility == true)
	{
		//���݂̈ړ���Ԃ�ۊ�
		now_state = next_state;

		state = PlayerStateFactory::Get((*this), next_state);
		next_state = ePlayerState::NONE;
	}
	//��ԕʂ̍X�V�������s��
	state->Update(delta_second);

	//�d�͑��x�̌v�Z
	g_velocity += D_GRAVITY;
	velocity.y += g_velocity * delta_second;

	// �ړ������s����֐��̌Ăяo��
	__super::Movement(delta_second);

	// y500.0f�n�_��n�ʂƉ���
	if (location.y > 600.0f)
	{
		location.y = 600.0f;
		g_velocity = 0.0f;
	}

}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset"></param>
void Player::Draw(const Vector2D& screen_offset) const
{
	// �I�t�Z�b�g�l����ɉ摜�̕`����s��
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.5, 0.0, image, TRUE, flip_flag);

	// �e�N���X�̕`�揈��
	//__super::Draw(screen_offset);
}

// �I���������i�g�����C���X�^���X�Ȃǂ̍폜�j
void Player::Finalize()
{
	ResourceManager::DeleteInstance();
}

void Player::OnHitCollision(GameObjectBase* hit_object)
{
}

void Player::SetNextState(ePlayerState next_state)
{
	this->next_state = next_state;
}
