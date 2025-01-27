#pragma once

#include"../SceneBase.h"

//コメントアウト
//#include"../../Object/ObjectManager.h"

class InGameScene : public SceneBase//,  public ObjectManager
{

public:
	InGameScene();
	virtual ~InGameScene();

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