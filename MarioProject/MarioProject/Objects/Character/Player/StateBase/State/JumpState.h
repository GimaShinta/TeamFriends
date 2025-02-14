#pragma once

#include "../PlayerStateBase.h"

// �v���C���[�̃W�����v��ԃN���X
class JumpState : public PlayerStateBase
{
private:
	int jump_sound;

public:
	// ���̃N���X�����������Ƃ��ɁA�����ɂ���p�ɂ̓v���C���[�̃C���X�^���X�i���́j�̃A�h���X���n�����
	JumpState(class Player* p);
	~JumpState();

public:
	// ����������
	void Initialize() override;
	// �X�V����
	void Update(float delta_second) override;
	// �`�揈��
	void Draw() const override;
	// �I��������
	void Finalize() override;

public:
	// ���݂̈ړ���Ԃ��擾
	ePlayerState GetState() const override;
};