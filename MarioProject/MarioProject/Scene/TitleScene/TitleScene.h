#pragma once

#include"../SceneBase.h"

class TitleScene :public SceneBase
{
private:

public:
	TitleScene();
	virtual ~TitleScene();

	//初期化処理
	virtual void Initialize() override;

	//更新処理
	virtual eSceneType Update(float delta_second) override;

	//描画処理
	virtual void Draw(float delta_second) const override;

	//終了時処理
	virtual void Finalize() override;

	//現在のシーンタイプ（オーバーライド必須）
	virtual eSceneType GetNowSceneType() const override;
};