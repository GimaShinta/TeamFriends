#pragma once

#include"../SceneBase.h"
#include <vector>

// インゲームシーンクラス
class InGameScene : public SceneBase//,  public ObjectManager
{
private:
	// csvの値を格納する構造体
	struct MapObjectData
	{
		char mode;
		int x_size;
		int y_size;
		int spos_x;
		int spos_y;
	};
	
	// ステージマップの情報を保持する構造体
	struct StageMapData 
	{
		std::vector<std::vector<char>> mapData;  // マップデータ ('.', 'P', ' ')
		int width;
		int height;
	};


private:
	// クラスポインタ変数
	class Player* player;
	class Kuribo* kuribo;
	class Nokonoko* nokonoko;

	// オブジェクト配列
	std::vector<MapObjectData> map_object;

public:
	InGameScene();
	virtual ~InGameScene();

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
	virtual void Draw(float delta_second) const override;

	// 終了時処理
	virtual void Finalize() override;

	// 現在のシーンタイプ（オーバーライド必須）
	virtual eSceneType GetNowSceneType() const override;

private:
	// 画像の読み込み
	void LoadImages();

	// csvを読み込んでステージの情報配列を作成
	void LoadStageMapCSV();

	// 作成したステージの情報配列を使って背景を生成
	void DrawStageMap();

	// csvを読み込んでオブジェクトの情報配列を作成
	void LoadStageObjectCSV();

	// 作成したオブジェクトの情報配列を使ってオブジェクトを生成
	void CreateMapObject();
};