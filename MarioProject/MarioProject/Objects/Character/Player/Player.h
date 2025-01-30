#pragma once

#include "../CharacterBase.h"
#include "StateBase//PlayerState.h"

#include <vector>

// プレイヤークラス（メンバ関数のオーバーライド必須）
class Player : public CharacterBase
{	
private:
	class PlayerStateBase* state = nullptr;           // 状態パターン自体を保存

public:
	bool flip_flag;    // 画像反転させるかどうか（trueは反転させる、falseは反転させない）
	bool stage_end;	   //ステージの端に着いたらTRUE
	bool isOnGround;	//地面にいるかどうか


public:
	ePlayerState next_state;                          // 次の状態パターンを保存
	ePlayerState now_state;                           // 現在の状態パターンを保存

public:
	Player();	//コンストラクタ
	~Player();	//デストラクタ

public:
	// 初期化処理
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delata_second">１フレーム当たりの時間</param>
	void Update(float delata_second) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="screen_offset"></param>
	void Draw(const Vector2D& screen_offset)const override;

	//終了時処理
	void Finalize() override;

public:
	void OnHitCollision(GameObjectBase* hit_object) override;

	//ステートの切り替え
	void SetNextState(ePlayerState next_state);

public:
	//プレイヤーの制御
	void PlayerControl();

	// 地面にいるかどうかを確認する
	bool IsOnGround() const;
};