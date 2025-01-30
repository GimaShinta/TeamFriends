#pragma once

#include "../CharacterBase.h"

// ノコノコクラス
class Nokonoko :public CharacterBase
{
private:
	// ノコノコの状態
	enum eNokonokoState
	{
		NORMAL,
		REVIVAL,   // 甲羅状態
		DEAD
	};

private:
	bool revival_move;         // 甲羅状態で走るか（trueは走っている、falseは走っていない）

private:
	eNokonokoState noko_state;          // ノコノコの状態の管理

private:
	std::vector<int> nokonoko_animation;     // ノコノコのアニメーション画像を保持
	std::vector<int> revival_animation;      // 甲羅状態のノコノコのアニメーション画像を保持

public:
	Nokonoko();
	~Nokonoko();

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

