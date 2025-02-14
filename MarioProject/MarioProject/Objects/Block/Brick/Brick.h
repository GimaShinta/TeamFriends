#pragma once
#include "../BlockBase.h"

// 破壊可能ブロック
class Brick : public BlockBase
{
private:
	bool is_destruction;   // 壊したかどうか
	int block_sound;

public:
	Brick();
	~Brick();

public:
	// 初期化処理
	void Initialize() override;

	/// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="delata_second">１フレーム当たりの時間</param>
	virtual void Update(float delta_second) override;

	/// <summary>
    /// 描画処理
    /// </summary>
    /// <param name="screen_offset"></param>
	virtual void Draw(const Vector2D& screen_offset)const override;

	// 終了時処理
	void Finalize() override;

	/// <summary>
    /// ヒット時処理
    /// </summary>
    /// <param name="hit_object">当たった相手</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;
};