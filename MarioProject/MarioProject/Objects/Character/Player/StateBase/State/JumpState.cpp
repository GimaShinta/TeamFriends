#include "JumpState.h"
#include "DxLib.h"

#include "../../Player.h"
#include "../PlayerState.h"

#include "../../../../../Utility/InputManager.h"
#include "../../../../../Utility/ResourceManager.h"

JumpState::JumpState(Player* p) :
	PlayerStateBase(p)
{
}

JumpState::~JumpState()
{
}

// ����������
void JumpState::Initialize()
{
	//�ړ�����
	this->player->velocity.y -= 1100.0f;         //�W�����v��
	old_location = 0.0f;
}

// �X�V����
void JumpState::Update(float delta_second)
{
	//�C���X�^���X�̎擾
	InputManager* input = Singleton<InputManager>::GetInstance();

	// �W�����v��Ԃ̂܂܈ړ�
	if (input->GetKey(KEY_INPUT_LEFT))
	{
		player->SetNextState(ePlayerState::RUN);
	}
	else if (input->GetKey(KEY_INPUT_RIGHT))
	{
		player->SetNextState(ePlayerState::RUN);
	}

	// �n�ʂɐG�ꂽ��
	if (old_location.y == player->GetLocation().y)
	{
		// ��~��ԂɑJ��
		player->SetNextState(ePlayerState::IDLE);
	}

	//// ���Ⴊ�ݏ�ԂɑJ��
	//if (input->GetKey(KEY_INPUT_DOWN))
	//{
	//	player->SetNextState(ePlayerState::SQUAT);
	//}

	//if (player->is_destroy == true)
	//{
	//	player->SetNextState(ePlayerState::DESTROY);
	//}

	// �O����W�̍X�V
	old_location = player->GetLocation();
}

// �`�揈��
void JumpState::Draw() const
{
}

// �I��������
void JumpState::Finalize()
{
	InputManager::DeleteInstance();
	ResourceManager::DeleteInstance();
}

// ���݂̈ړ���Ԃ̎擾
ePlayerState JumpState::GetState() const
{
	return ePlayerState::JUMP;
}
