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
	// 更新処理
	virtual void Update(float delata_second) override;
	// 描画処理
	virtual void Draw(const Vector2D& screen_offset)const override;
	// 終了時処理
	virtual void Finalize() override;

public:
	// ヒット時処理
	virtual void OnHitCollision(GameObjectBase* hit_object) override;

public:
	// 移動処理
	virtual void Movement(float delta_second);
	// スクロール速さに合わせて加速させる
	void SetVelocity(const Vector2D& velocity);
};

