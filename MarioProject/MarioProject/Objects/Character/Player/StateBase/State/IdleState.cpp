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

// 初期化処理
void IdleState::Initialize()
{
	//速度を0にする
	player->velocity.x = 0.0f;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
void IdleState::Update(float delta_second)
{
	// インスタンスの取得
	InputManager* input = Singleton<InputManager>::GetInstance();

	// 移動状態に遷移
	if (input->GetKey(KEY_INPUT_LEFT) || input->GetKey(KEY_INPUT_RIGHT))
	{
		player->SetNextState(ePlayerState::RUN);
	}

	// ジャンプ状態に遷移
	if (input->GetKeyDown(KEY_INPUT_UP))
	{
		player->SetNextState(ePlayerState::JUMP);
	}
}

// 描画処理
void IdleState::Draw() const
{
}

// 終了時処理（使ったインスタンスなどの削除）
void IdleState::Finalize()
{
	InputManager::DeleteInstance();
}

// 現在の移動状態の取得
ePlayerState IdleState::GetState() const
{
	return ePlayerState::IDLE;
}
