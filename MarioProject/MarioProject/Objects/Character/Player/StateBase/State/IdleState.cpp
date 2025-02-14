#include "IdleState.h"
#include "DxLib.h"

#include "../PlayerState.h"

#include "../../../../../Utility/InputManager.h"

IdleState::IdleState(Player* p) :
	PlayerStateBase(p)
{
}

IdleState::~IdleState()
{
}

// ����������
void IdleState::Initialize()
{
	//���x��0�ɂ���
	player->velocity.x = 0.0f;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
void IdleState::Update(float delta_second)
{
	// �C���X�^���X�̎擾
	InputManager* input = Singleton<InputManager>::GetInstance();

	// �ړ���ԂɑJ��
	if (input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_RIGHT))
	{
		player->SetNextState(ePlayerState::RUN);
	}

	// �W�����v��ԂɑJ��
	if (input->GetKeyDown(KEY_INPUT_UP))
	{
		player->SetNextState(ePlayerState::JUMP);
	}
}

// �`�揈��
void IdleState::Draw() const
{
}

// �I���������i�g�����C���X�^���X�Ȃǂ̍폜�j
void IdleState::Finalize()
{
	InputManager::DeleteInstance();
}

// ���݂̈ړ���Ԃ̎擾
ePlayerState IdleState::GetState() const
{
	return ePlayerState::IDLE;
}
