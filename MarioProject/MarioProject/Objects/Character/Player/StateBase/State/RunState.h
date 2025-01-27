#pragma once

#include "../PlayerStateBase.h"

// プレイヤーの歩く状態クラス
class RunState : public PlayerStateBase
{
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

