#pragma once

#include "../CharacterBase.h"
#include "StateBase//PlayerState.h"

#include <vector>

// �v���C���[�N���X�i�����o�֐��̃I�[�o�[���C�h�K�{�j
class Player : public CharacterBase
{	
private:
	class PlayerStateBase* state = nullptr;           // ��ԃp�^�[�����̂�ۑ�

public:
	bool flip_flag;    // �摜���]�����邩�ǂ����itrue�͔��]������Afalse�͔��]�����Ȃ��j
	bool stage_end;	   //�X�e�[�W�̒[�ɒ�������TRUE
	bool isOnGround;	//�n�ʂɂ��邩�ǂ���
	bool is_goal;
	bool is_clear;

public:
	ePlayerState next_state;                          // ���̏�ԃp�^�[����ۑ�
	ePlayerState now_state;                           // ���݂̏�ԃp�^�[����ۑ�

private:
	std::vector<int> mario_aniamtion; // �A�j���[�V�����摜�̕ێ�

private:
	std::vector<int> mario_animation_num = { 0,1,2,3,2,1 };// �A�j���[�V�����̏���

public:
	Player();	//�R���X�g���N�^
	~Player();	//�f�X�g���N�^

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

	//�A�j���[�V��������
	void AnimationControl(float delta_second, std::vector<int>& animation_image, std::vector<int>& animation_num, int n_jump, int n_squat, int n_destroy);

	//�X�e�[�g�̐؂�ւ�
	void SetNextState(ePlayerState next_state);

public:
	//�v���C���[�̐���
	void PlayerControl(float delta_second);

	// �n�ʂɂ��邩�ǂ������m�F����
	bool IsOnGround() const;

	// ����ł��邩
	bool GetIsDestroy();

	// clear���Ă��邩
	bool GetIsClear();
};