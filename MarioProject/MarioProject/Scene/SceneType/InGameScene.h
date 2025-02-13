#pragma once

#include"../SceneBase.h"
#include <vector>

// インゲームシーンクラス 
class InGameScene : public SceneBase//,  public ObjectManager
{
public:

	int image;	//画像用
	float scroll;	//スクロール量
	int bgm;     // bgm用
	int score;   // スコア

private:
	std::vector<int> ui_string;	//文字画像　
	std::vector<int> ui_num;	//数字画像 
	int ui_image[4];	//UI画像


private:
	// csvの値を格納する構造体
	struct ObjectMapData
	{
		char mode;
		int x_size;
		int y_size;
		int spos_x;
		int spos_y;
	};

private:
	// クラスポインタ変数
	class Player* player;                   // プレイヤー情報を保持
	class GameObjectBase* game_object;      // プレイヤー以外のゲームオブジェクト情報を保持する

	// オブジェクトの情報配列
	std::vector<ObjectMapData> map_object;

	// 生成したオブジェクトを格納する配列
	std::vector<GameObjectBase*> object_array;

	// ステージの情報配列
	std::vector<std::vector<char>> map_array;

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
	virtual void Draw(float delta_second) override;

	// 終了時処理
	virtual void Finalize() override;

	// 現在のシーンタイプ（オーバーライド必須）
	virtual eSceneType GetNowSceneType() const override;

	// スクロール処理
	void Scroll(float delta_second);

private:
	// csvを読み込んでステージの情報配列を作成
	std::vector<std::vector<char>> LoadStageMapCSV();

	// 作成したステージの情報配列を使って背景を描画
	void DrawStageMap();

	// csvを読み込んでオブジェクトの情報配列を作成
	void LoadStageObjectCSV();

	// 作成したオブジェクトの情報配列を使ってオブジェクトを生成
	void CreateMapObject();
};