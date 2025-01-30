#pragma once

#include "../CharacterBase.h"

// クリボークラス
class Kuribo :public CharacterBase
{
public:
	// クリボーの状態
	enum eKUriboState
	{
		NORMAL,
		HUMARERU,
		DEAD
	};

public:
	Kuribo();
	~Kuribo();

public:
	// 初期化処理
	void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second"></param>
	void Update(float delta_second) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="screen_offset"></param>
	void Draw(const Vector2D& screen_offset)const override;

	// 終了時処理
	void Finalize() override;

public:
	/// <summary>
	/// ヒットしたときの処理
	/// </summary>
	/// <param name="hit_object">当たった相手</param>
	void OnHitCollision(GameObjectBase* hit_object) override;
};

