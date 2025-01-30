#include "IdleState.h"
#include "DxLib.h"

//#include "../../Player.h"
#include "../PlayerState.h"

#include "../../../../../Utility/InputManager.h"
#include "../../../../../Utility/ResourceManager.h"

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
	player->velocity = 0.0f;

	//�摜�̐ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	state_image = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32)[0];
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


	//// ���Ⴊ�ݏ�ԂɑJ��
	//if (input->GetKey(KEY_INPUT_DOWN))
	//{
	//	player->SetNextState(ePlayerState::SQUAT);
	//}

	//if (player->is_destroy == true)
	//{
	//	player->SetNextState(ePlayerState::DESTROY);
	//}
}

// �`�揈��
void IdleState::Draw() const
{
}

// �I���������i�g�����C���X�^���X�Ȃǂ̍폜�j
void IdleState::Finalize()
{
	InputManager::DeleteInstance();
	ResourceManager::DeleteInstance();
}

// ���݂̈ړ���Ԃ̎擾
ePlayerState IdleState::GetState() const
{
	return ePlayerState::IDLE;
}
