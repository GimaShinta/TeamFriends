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

// 初期化処理
void JumpState::Initialize()
{
	//移動処理
	this->player->velocity.y -= 1100.0f;         //ジャンプ力
	old_location = 0.0f;
}

// 更新処理
void JumpState::Update(float delta_second)
{
	//インスタンスの取得
	InputManager* input = Singleton<InputManager>::GetInstance();

	// ジャンプ状態のまま移動
	if (input->GetKey(KEY_INPUT_LEFT))
	{
		player->SetNextState(ePlayerState::RUN);
	}
	else if (input->GetKey(KEY_INPUT_RIGHT))
	{
		player->SetNextState(ePlayerState::RUN);
	}

	// 地面に触れたら
	if (old_location.y == player->GetLocation().y)
	{
		// 停止状態に遷移
		player->SetNextState(ePlayerState::IDLE);
	}

	//// しゃがみ状態に遷移
	//if (input->GetKey(KEY_INPUT_DOWN))
	//{
	//	player->SetNextState(ePlayerState::SQUAT);
	//}

	//if (player->is_destroy == true)
	//{
	//	player->SetNextState(ePlayerState::DESTROY);
	//}

	// 前回座標の更新
	old_location = player->GetLocation();
}

// 描画処理
void JumpState::Draw() const
{
}

// 終了時処理
void JumpState::Finalize()
{
	InputManager::DeleteInstance();
	ResourceManager::DeleteInstance();
}

// 現在の移動状態の取得
ePlayerState JumpState::GetState() const
{
	return ePlayerState::JUMP;
}
