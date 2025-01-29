#pragma once

#include "../CharacterBase.h"
#include <vector>

#include "StateBase//PlayerState.h"

// プレイヤークラス（メンバ関数のオーバーライド必須）
class Player : public CharacterBase
{
public:
	bool flip_flag;    // 画像反転させるかどうか（trueは反転させる、falseは反転させない）

public:
	bool stage_end;	//ステージの端に着いたらTRUE

private:
	class PlayerStateBase* state = nullptr;           // 状態パターン自体を保存

public:
	ePlayerState next_state;                          // 次の状態パターンを保存
	ePlayerState now_state;                           // 現在の状態パターンを保存

public:
	Player();
	~Player();

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

public:
	//ステートの切り替え
	void SetNextState(ePlayerState next_state);

public:
	void PlayerControl();
};