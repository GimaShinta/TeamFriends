#pragma once

#include "../../../../../Singleton.h"

#include "../PlayerStateBase.h"
#include "../PlayerState.h"

// �v���C���[�̈ړ���ԊǗ��N���X
class PlayerStateFactory : public Singleton<class T>
{
private:
	// �N���X�^�ϐ�
	class IdleState* idle;
	class RunState* run;
	class JumpState* jump;
	//class SquatState* squat;
	//class DestroyState* destroy;

public:
	// �C���X�^���X�̍폜
	static void DeleteInstance();

private:
	// ����������
	void Initialize(class Player& player);

public:
	// ��ԃN���X�Ǘ�����
	static PlayerStateBase* Get(class Player& player, ePlayerState state);

	// �I������
	void Finalize();
};

