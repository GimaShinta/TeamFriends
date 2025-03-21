#pragma once
#include "../BlockBase.h"

// ハテナブロッククラス
class Hatena :
    public BlockBase
{
protected:
	int kara_image;
	bool is_kara;                       // 空かどうか（trueなら空、falseなら空じゃない）
	int item_sound;
	int block_sound;

private:
	std::vector<int> hatena_animation;  // ハテナブロックのアニメーション画像を保持

private:
	std::vector<int> hatena_animation_num = { 0,1,2,3,2,1 }; // アニメーションの順番

public:
	Hatena();
	~Hatena();

public:
	// 初期化処理
	void Initialize() override;

	/// <summary>
    /// 更新処理
    /// </summary>
    /// <param name="delata_second">１フレーム当たりの時間</param>
	virtual void Update(float delta_second) override;

	// 終了時処理
	void Finalize() override;

	/// <summary>
    /// ヒット時処理
    /// </summary>
    /// <param name="hit_object">当たった相手</param>
	virtual void OnHitCollision(GameObjectBase* hit_object) override;
};

