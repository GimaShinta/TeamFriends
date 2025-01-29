#pragma once

#include "../../../../Utility/Vector2D.h"

#include "../Player.h"
#include "PlayerState.h"

/// <summary>
/// �v���C���[��ԊǗ��p�̃x�[�X�N���X
/// </summary>
class PlayerStateBase
{
protected:
	class Player* player;                  // �v���C���[���
	Vector2D old_location;                 // �O��̈ʒu���W
	int state_image;                       // ��Ԃ̉摜�i�W�����v�ł���΃W�����v�̉摜�j
	float animation_time;                  // �A�j���[�V�����̎��ԊǗ�
	int animation_count;                   // �A�j���[�V�����̎��Ԍo�߂ɂ��J�E���g

public:
	PlayerStateBase(class Player* p)
		: player(p)
		, state_image(NULL)
		, animation_time(0)
		, animation_count(0)
	{
	}

	virtual ~PlayerStateBase() = default;

	// �n�ʂɂ��邩�ǂ������m�F����
	virtual bool IsOnGround() const
	{
		return player->IsOnGround();
	}

public:
	// ����������
	virtual void Initialize() = 0;
	// �I��������
	virtual void Finalize() = 0;
	// �X�V����
	virtual void Update(float delta_second) = 0;
	// �`�揈��
	virtual void Draw() const = 0;

public:
	// ���݂̌����ڂ̏�Ԃ��擾
	//virtual ePlayerLooksState GetLooksState() const = 0;
	// ���݂̓����̏�Ԃ��擾
	virtual ePlayerState GetState() const = 0;
};