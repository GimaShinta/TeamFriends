#pragma once

#include "../GameObjectBase.h"

#define D_GRAVITY (30.0f)    //重力加速度(m/ss)

// キャラクターベースクラス（メンバ関数のオーバーライド必須）
class CharacterBase : public GameObjectBase
{
protected:
	float g_velocity;                          // 重力
	std::vector<std::vector<char>> map_data;   // マップの情報保持
	float scroll_value;                        // スクロール量を保存

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

	/// <summary>
	/// スクロール量の設定
	/// </summary>
	/// <param name="scroll">スクロール量</param>
	void SetScrollValue(float& scroll);

	/// <summary>
    /// ステージの情報を設定
    /// </summary>
    /// <param name="map">インゲームで作ったステージ情報を参照で受け取る</param>
	void SetMapData(const std::vector<std::vector<char>>& map);

	// マップとの当たり判定
	bool MapCollision();
};

