#include "JumpState.h"
#include "DxLib.h"

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
	// インスタンスの取得
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	//BGMの読み込み
	jump_sound = rm->GetSounds("Resource/Sounds/SE_MiniJump.wav");
	// 再生
	PlaySoundMem(jump_sound, DX_PLAYTYPE_BACK);

	//移動処理
	this->player->velocity.y -= 1700.0f;         //ジャンプ力
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
