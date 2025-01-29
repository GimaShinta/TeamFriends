#pragma once

#include "../CharacterBase.h"
#include <vector>

#include "StateBase//PlayerState.h"

// �v���C���[�N���X�i�����o�֐��̃I�[�o�[���C�h�K�{�j
class Player : public CharacterBase
{
public:
	bool flip_flag;    // �摜���]�����邩�ǂ����itrue�͔��]������Afalse�͔��]�����Ȃ��j

public:
	bool stage_end;	//�X�e�[�W�̒[�ɒ�������TRUE

private:
	class PlayerStateBase* state = nullptr;           // ��ԃp�^�[�����̂�ۑ�

public:
	ePlayerState next_state;                          // ���̏�ԃp�^�[����ۑ�
	ePlayerState now_state;                           // ���݂̏�ԃp�^�[����ۑ�

public:
	Player();
	~Player();

public:
	// ����������
	void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delata_second">�P�t���[��������̎���</param>
	void Update(float delata_second) override;

	/// <summary>
	/// �`�揈��
	/// </summary>
	/// <param name="screen_offset"></param>
	void Draw(const Vector2D& screen_offset)const override;

	//�I��������
	void Finalize() override;

public:
	void OnHitCollision(GameObjectBase* hit_object) override;

public:
	//�X�e�[�g�̐؂�ւ�
	void SetNextState(ePlayerState next_state);

public:
	void PlayerControl();
};