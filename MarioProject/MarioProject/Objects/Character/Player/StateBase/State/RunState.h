#pragma once

#include "../PlayerStateBase.h"

// �v���C���[�̕�����ԃN���X
class RunState : public PlayerStateBase
{
public:
	// ���̃N���X�����������Ƃ��ɁA�����ɂ���p�ɂ̓v���C���[�̃C���X�^���X�i���́j�̃A�h���X���n�����
	RunState(class Player* p);
	~RunState();

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
	// ���݂̓����̏�Ԃ��擾
	ePlayerState GetState() const override;
};

