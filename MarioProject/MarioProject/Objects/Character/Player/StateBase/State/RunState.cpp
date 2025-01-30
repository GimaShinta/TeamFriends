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

// 初期化処理
void RunState::Initialize()
{
}

//更新処理
void RunState::Update(float delta_second)
{
    // インスタンスの取得
    InputManager* input = Singleton<InputManager>::GetInstance();

    // 移動処理と反転(加減速処理)
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
    // ジャンプ状態に遷移
    if (input->GetKeyDown(KEY_INPUT_UP) && this->IsOnGround())
    {
        player->SetNextState(ePlayerState::JUMP);
    }
    // 移動入力がない場合、停止状態に遷移
     else if (!input->GetKey(KEY_INPUT_LEFT) && !input->GetKey(KEY_INPUT_RIGHT))
    {
        // 地面にいる場合のみIDLE状態に遷移
        if (this->IsOnGround())
        {
            player->SetNextState(ePlayerState::IDLE);
        }
    }

    // 前回座標の更新
    old_location = player->GetLocation();
}


// 描画処理
void RunState::Draw() const
{
}

// 終了時処理
void RunState::Finalize()
{
	InputManager::DeleteInstance();

	//コメントアウト
	//ResourceManager::DeleteInstance();
}

// 現在の動きの状態を取得
ePlayerState RunState::GetState() const
{
	return ePlayerState::RUN;
}
