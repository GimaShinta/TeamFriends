#pragma once

// シーンの種類
enum class eSceneType
{
	eTitle,
	eInGame,
	eResult,
	eXit
};

// シーン基底クラス
class SceneBase
{
public:
	// 初期化処理
	virtual void Initialize() {}

	/// <summary>
	/// 更新処理
	/// </summary>
	/// <param name="delta_second">1フレーム当たりの時間</param>
	/// <returns></returns>
	virtual eSceneType Update(float delta_second)
	{
		//現在のシーン情報を取得する
		return GetNowSceneType();
	}

	/// <summary>
	/// 描画処理
	/// </summary>
	/// <param name="delta_second">1フレーム当たりの時間</param>
	/// <returns></returns>
	virtual void Draw(float delta_second) const
	{
		//インスタンスの取得
		//GameObjectManager* obj_manager = Singleton<GameObjectManager>::GetInstance();
		//obj_manager->Draw();
	}

	// 終了時処理
	virtual void Finalize() {}

public:
	// 現在のシーン情報を取得する
	virtual eSceneType GetNowSceneType()const = 0;
};