#pragma once

#include "../PlayerStateBase.h"

// プレイヤーの歩く状態クラス
class RunState : public PlayerStateBase
{
private:
	std::vector<int> mario_aniamtion; // アニメーション画像の保持

private:
	std::vector<int> mario_animation_num = { 0,1,2,3,2,1 };// アニメーションの順番

public:
	// このクラスが生成されるときに、引数にあるpにはプレイヤーのインスタンス（実体）のアドレスが渡される
	RunState(class Player* p);
	~RunState();

public:
	// 初期化処理
	void Initialize() override;
	// 更新処理
	void Update(float delta_second) override;
	// 描画処理
	void Draw() const override;
	// 終了時処理
	void Finalize() override;

public:
	// 現在の動きの状態を取得
	ePlayerState GetState() const override;
};

