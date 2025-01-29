#pragma once

#include "../../../../Utility/Vector2D.h"

#include "../Player.h"
#include "PlayerState.h"

/// <summary>
/// プレイヤー状態管理用のベースクラス
/// </summary>
class PlayerStateBase
{
protected:
	class Player* player;                  // プレイヤー情報
	Vector2D old_location;                 // 前回の位置座標
	int state_image;                       // 状態の画像（ジャンプであればジャンプの画像）
	float animation_time;                  // アニメーションの時間管理
	int animation_count;                   // アニメーションの時間経過によるカウント

public:
	PlayerStateBase(class Player* p)
		: player(p)
		, state_image(NULL)
		, animation_time(0)
		, animation_count(0)
	{
	}

	virtual ~PlayerStateBase() = default;

	// 地面にいるかどうかを確認する
	virtual bool IsOnGround() const
	{
		return player->IsOnGround();
	}

public:
	// 初期化処理
	virtual void Initialize() = 0;
	// 終了時処理
	virtual void Finalize() = 0;
	// 更新処理
	virtual void Update(float delta_second) = 0;
	// 描画処理
	virtual void Draw() const = 0;

public:
	// 現在の見た目の状態を取得
	//virtual ePlayerLooksState GetLooksState() const = 0;
	// 現在の動きの状態を取得
	virtual ePlayerState GetState() const = 0;
};