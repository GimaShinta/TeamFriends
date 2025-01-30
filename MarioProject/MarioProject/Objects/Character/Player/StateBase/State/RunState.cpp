#include "RunState.h"
#include "DxLib.h"

#include "../../Player.h"
#include "../PlayerState.h"

#include "../../../../../Utility/InputManager.h"

RunState::RunState(Player* p) :
	PlayerStateBase(p)
{
}

RunState::~RunState()
{
}

// ����������
void RunState::Initialize()
{
}

//�X�V����
void RunState::Update(float delta_second)
{
    // �C���X�^���X�̎擾
    InputManager* input = Singleton<InputManager>::GetInstance();

    // �ړ������Ɣ��](����������)
    if (input->GetKey(KEY_INPUT_LEFT))
    {
        this->player->velocity.x -= 1.0f;
        this->player->flip_flag = TRUE;
        old_location = 0.0f;
    }
    else if (input->GetKey(KEY_INPUT_RIGHT))
    {
        this->player->velocity.x += 1.0f;
        this->player->flip_flag = FALSE;
        old_location = 0.0f;
    }
    // �W�����v��ԂɑJ��
    if (input->GetKeyDown(KEY_INPUT_UP) && this->IsOnGround())
    {
        player->SetNextState(ePlayerState::JUMP);
    }
    // �ړ����͂��Ȃ��ꍇ�A��~��ԂɑJ��
     else if (!input->GetKey(KEY_INPUT_LEFT) && !input->GetKey(KEY_INPUT_RIGHT))
    {
        // �n�ʂɂ���ꍇ�̂�IDLE��ԂɑJ��
        if (this->IsOnGround())
        {
            player->SetNextState(ePlayerState::IDLE);
        }
    }

    // �O����W�̍X�V
    old_location = player->GetLocation();
}


// �`�揈��
void RunState::Draw() const
{
}

// �I��������
void RunState::Finalize()
{
	InputManager::DeleteInstance();

	//�R�����g�A�E�g
	//ResourceManager::DeleteInstance();
}

// ���݂̓����̏�Ԃ��擾
ePlayerState RunState::GetState() const
{
	return ePlayerState::RUN;
}
