#pragma once

#include "../CharacterBase.h"

// クリボークラス
class Kuribo :public CharacterBase
{
private:
	// クリボーの状態
	enum eKuriboState
	{
		NORMAL,
		HUMARERU,
		DEAD
	};

private:
	eKuriboState kuribo_state;       // クリボーの状態の管理

private:
	std::vector<int> kuribo_animation;     // クリボーのアニメーション画像を保持

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

