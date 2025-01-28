#pragma once

#include "../GameObjectBase.h"

// キャラクターベースクラス（メンバ関数のオーバーライド必須）
class CharacterBase : public GameObjectBase
{
protected:
	float g_velocity;       // 重力

public:
	Vector2D velocity;      // 速度

public:
	CharacterBase();
	~CharacterBase();

public:
	// 初期化処理
	virtual void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delata_second">１フレーム当たりの時間</param>
	virtual void Update(float delata_second) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="screen_offset"></param>
	virtual void Draw(const Vector2D& screen_offset)const override;

	// 終了時処理
	virtual void Finalize() override;

public:
	/// <summary>
	/// ヒット時処理
	/// </summary>
	/// <param name="hit_object">当たった相手</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	/// <summary>
	/// 移動処理
	/// </summary>
	/// <param name="delta_second">１フレーム当たりの時間</param>
	virtual void Movement(float delta_second);
	// スクロール速さに合わせて加速させる
	void SetVelocity(const Vector2D& velocity);
};

