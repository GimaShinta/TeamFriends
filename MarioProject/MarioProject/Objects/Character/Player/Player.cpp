#include "Player.h"
#include "DxLib.h"

// �V���O���g���p���N���X�̃C���N���[�h
#include "../../../Utility/ResourceManager.h"
#include "StateBase/State/PlayerStateFactory.h"
#include"../../../Application/Application.h"

#include <cmath>

#define P_MAX_SPEED 500.0f

Player::Player():
	  flip_flag(false)
	, now_state(ePlayerState::IDLE)
	, next_state(ePlayerState::NONE)
	,stage_end(FALSE)
	, isOnGround(false) //�����l(�n��)
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
	mario_aniamtion = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);
	// ���������摜�̐擪����
	image = mario_aniamtion[0];

	// �����蔻��̃I�u�W�F�N�g�ݒ�
	collision.is_blocking = true;
	// �����̃I�u�W�F�N�g�^�C�v
	collision.object_type = eObjectType::ePlayer;
	// �����鑊��̃I�u�W�F�N�g�^�C�v
	collision.hit_object_type.push_back(eObjectType::eEnemy);

	// �������ǂ����itrue�Ȃ瓮���Afalse�Ȃ�~�܂�j
	is_mobility = true;

	// �v���C���[�̓����蔻��T�C�Y�̐ݒ�
	box_size = D_OBJECT_SIZE;

	velocity = 0;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delata_second">�P�t���[��������̎���</param>
void Player::Update(float delta_second)
{
	// �A�j���[�V����
	AnimationControl(delta_second, mario_aniamtion, mario_animation_num, 5, NULL, 6);

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

	// �ړ������s����֐��̌Ăяo��
	__super::Movement(delta_second);

	//�v���[���[�̍s��������s��
	PlayerControl(delta_second);
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
}

// �I���������i�g�����C���X�^���X�Ȃǂ̍폜�j
void Player::Finalize()
{
	ResourceManager::DeleteInstance();
	PlayerStateFactory::DeleteInstance();
}

/// <summary>
/// �q�b�g���菈��
/// </summary>
/// <param name="hit_object"></param>
void Player::OnHitCollision(GameObjectBase* hit_object)
{
	if (hit_object->GetCollision().object_type == eObjectType::eEnemy)
	{
		now_state = ePlayerState::DESTROY;
	}
	else if (hit_object->GetCollision().object_type == eObjectType::eBlock)
	{
		Vector2D diff = location - hit_object->GetLocation();
		//if (velocity.y > 0)
		//{
		//	location.y = hit_object->GetLocation().y - (D_OBJECT_SIZE * 2);
		//	isOnGround = true;
		//}
	}
}

/// <summary>
/// �A�j���[�V�����̐���
/// </summary>
/// <param name="delta_second">1�t���[��������̎���</param>
/// <param name="animation_image">�A�j���[�V�������摜</param>
/// <param name="animation_num">�A�j���[�V��������</param>
/// <param name="n_jump">�W�����v�摜�̈ʒu</param>
/// <param name="n_squat">���Ⴊ�݉摜�̈ʒu</param>
void Player::AnimationControl(float delta_second, std::vector<int>& animation_image, std::vector<int>& animation_num, int n_jump, int n_squat, int n_destroy)
{
	switch (now_state)
	{
	case ePlayerState::RUN:
		// �A�j���[�V�������摜�ƃA�j���[�V���������������Ƃ���
		GameObjectBase::AnimationControl(delta_second, animation_image, animation_num, 16.0f);
		break;
	case ePlayerState::IDLE:
		// ��~���Ă���摜����
		image = animation_image[0];
		break;
	case ePlayerState::JUMP:
		// n_jump�Ԗڂɂ���W�����v�摜����
		image = animation_image[n_jump];
		break;
	case ePlayerState::SQUAT:
		// n_squat�Ԗڂɂ��邵�Ⴊ�݉摜����
		image = animation_image[n_squat];
		break;
	case ePlayerState::DESTROY:
		image = animation_image[n_destroy];
		break;
	case ePlayerState::NONE:
		break;
	}
}

/// <summary>
/// �X�e�[�g�̐ݒ�
/// </summary>
/// <param name="next_state"></param>
void Player::SetNextState(ePlayerState next_state)
{
	this->next_state = next_state;
}

/// <summary>
/// �v���C���[�̐��䏈��
/// </summary>
void Player::PlayerControl(float delta_second)
{
	//�ő呬�x�̐ݒ�
	if (velocity.x >= P_MAX_SPEED)
	{
		velocity.x = P_MAX_SPEED;
	}
	else if (velocity.x <= -P_MAX_SPEED)
	{
		velocity.x = -P_MAX_SPEED;
	}

	//Vector2D P = Vector2D(location.x + velocity.x, location.y);
	//Vector2D P_upper = Vector2D(P + (0, -24.0f));
	//Vector2D P_upper_div_chip = P_upper / (D_OBJECT_SIZE * 2);
	//if (map_data[P_upper_div_chip.y][P_upper_div_chip.x] == '2')
	//{
	//	if (velocity.x > 0)
	//	{
	//		location.x -= velocity.x;
	//	}
	//	else
	//	{
	//		location.x += velocity.x;
	//	}
	//}

	//Vector2D P_bottom = Vector2D(P + (0, 24.0f));
	//Vector2D P_bottom_div_chip = P_bottom / (D_OBJECT_SIZE * 2);
	//if (map_data[P_bottom_div_chip.y][P_bottom_div_chip.x] == '2')
	//{
	//	if (velocity.x > 0)
	//	{
	//		location.x -= velocity.x;
	//	}
	//	else
	//	{
	//		location.x += velocity.x;
	//	}
	//}

	//P = Vector2D(location.x, location.y + D_OBJECT_SIZE);
	//Vector2D P_left = Vector2D(P + (-24.0f, 0));
	//Vector2D P_left_div_chip = P_left / (D_OBJECT_SIZE * 2);
	//if (map_data[P_left_div_chip.y][P_left_div_chip.x] == '2')
	//{
	//	if (velocity.y > 0)
	//	{
	//		location.y -= velocity.y;
	//	}
	//	else
	//	{
	//		location.y += velocity.y;
	//	}
	//}

	//Vector2D P_right = Vector2D(P + (24.0f, 0));
	//Vector2D P_right_div_chip = P_right / (D_OBJECT_SIZE * 2);
	//if (map_data[P_right_div_chip.y][P_right_div_chip.x] == '2')
	//{
	//	if (velocity.y > 0)
	//	{
	//		location.y -= velocity.y;
	//	}
	//	else
	//	{
	//		location.y += velocity.y;
	//	}
	//}

	// �������Ă���ꏊ���n�ʂ������炻�̍��W�ɐݒ�
	if (__super::MapCollision() == true)
	{
		// �ϊ��p�ϐ��ɕۑ�
		float y_map = location.y;

		// �`�b�v�T�C�Y�Ŋ����Č��݂̃}�b�v�ʒu�����
		y_map /= (D_OBJECT_SIZE * 2);

		// �؂�グ�����ɕϊ�
		int y_id = std::ceil(y_map);

		// �}�b�v�T�C�Y�������č��W�����
		y_id *= (D_OBJECT_SIZE * 2);

		// ���W��ݒ�
		location.y = y_id - D_OBJECT_SIZE;
		velocity.y = 0.0f;
		g_velocity = 0.0f;
		isOnGround = true; // �n�ʂɂ���
	}
	else
	{
		//�d�͑��x�̌v�Z
		g_velocity += D_GRAVITY;
		velocity.y += g_velocity * delta_second;
		isOnGround = false; // �󒆂ɂ���
	}

	//��ʊO�ɍs���Ȃ��悤�ɂ���
	if (location.x < 0 + D_OBJECT_SIZE)
	{ //��
		location.x = 0 + D_OBJECT_SIZE;
	}

	//�X�N���[������
	if (stage_end == FALSE)
	{
		//Player->�^�񒆂ɒ�������
		if (location.x >= D_WIN_MAX_X / 2)
		{
			location.x = D_WIN_MAX_X / 2;
		}
	}
	else
	{
		//�X�e�[�W�̒[�ɒ�������
		if (location.x > D_WIN_MAX_X - D_OBJECT_SIZE * 1.2)
		{ //��
			location.x = D_WIN_MAX_X - D_OBJECT_SIZE * 1.2;
		}
	}
}

// �n�ʂɂ��邩�ǂ������m�F����
bool Player::IsOnGround() const
{
	return isOnGround;
}