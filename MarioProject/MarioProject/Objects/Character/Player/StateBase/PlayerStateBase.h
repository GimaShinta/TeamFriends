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
	// �v���C���[���
	class Player* player;
	Vector2D old_location;
	int state_image;
	float animation_time;
	int animation_count;

public:
	PlayerStateBase(class Player* p)
		: player(p)
		, state_image(NULL)
		, animation_time(0)
		, animation_count(0)
	{
	}

	virtual ~PlayerStateBase() = default;

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