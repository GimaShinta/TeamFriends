#pragma once

#include"../SceneBase.h"

// タイトルシーンクラス
class TitleScene :public SceneBase
{
private:
	int title_image;    // タイトルの画像
public:
	TitleScene();
	virtual ~TitleScene();

	// 初期化処理
	virtual void Initialize() override;

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">１フレーム当たりの時間</param>
	/// <returns></returns>
	virtual eSceneType Update(float delta_second) override;

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="delta_second">１フレーム当たりの時間</param>
	/// <returns></returns>
	virtual void Draw(float delta_second) override;

	// 終了時処理（使ったインスタンスの削除とか）
	virtual void Finalize() override;

	// 現在のシーンタイプ（オーバーライド必須）
	virtual eSceneType GetNowSceneType() const override;
};