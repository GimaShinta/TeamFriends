#include"InGameScene.h"
#include"../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"

#include "../../Objects/GameObjectManager.h"
#include "../../Objects/Character/Player/Player.h"
#include "../../Objects/Character/Kuribo/Kuribo.h"

#include"DxLib.h"

#include <fstream>
#include <iostream>


InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

// 初期化処理
void InGameScene::Initialize()
{
	// インスタンスの取得
	GameObjectManager* object_manager = Singleton<GameObjectManager>::GetInstance();
	object_manager->CreateObject<Player>(Vector2D(100, 600));
	object_manager->CreateObject<Kuribo>(Vector2D(700, 600));
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
/// <returns></returns>
eSceneType InGameScene::Update(float delta_second)
{
	// インスタンスの取得
	GameObjectManager* obj_manager = Singleton<GameObjectManager>::GetInstance();
	InputManager* input = Singleton<InputManager>::GetInstance();

	// GameObjectManagerクラスのUpdate関数にアクセス
	obj_manager->Update(delta_second);

	//【デバッグ用】Yキーでリザルト画面に遷移する
	if (input->GetKeyDown(KEY_INPUT_Y))
	{
		return eSceneType::eResult;
	}

	// 現在のシーンタイプはインゲームですということを呼び出し元へreturnで送る
	return GetNowSceneType();
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
/// <returns></returns>
void InGameScene::Draw(float delta_second) const
{
	// 親クラスの描画処理
	__super::Draw(delta_second);

	// コメントアウティ
	//GameObjectManager* obj_manager = Singleton<GameObjectManager>::GetInstance();
	//obj_manager->Draw();

	DrawFormatString(10, 10, GetColor(0, 255, 255), "インゲーム画面です");
}

// 終了時処理（使ったインスタンスの削除とか）
void InGameScene::Finalize()
{
	InputManager::DeleteInstance();
}

/// <summary>
/// 現在のシーン情報
/// </summary>
/// <returns>現在はインゲームシーンです</returns>
eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}

// 画像の読み込み
void InGameScene::LoadImages()
{
}

// csvを読み込んでステージの情報配列を作成
void InGameScene::LoadStageMapCSV()
{
	FILE* fp = NULL;
	std::string file_name = "Resource/Map/StageMapFoods.csv";

	// 指定されたファイルを開く
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// エラーチェック
	if (result != 0)
	{
		throw (file_name + "が開けません");
	}

	int x = 0;
	int y = 0;

	// ファイル内の文字を確認していく
	while (true)
	{
		// ファイルから1文字抽出する
		int c = fgetc(fp);

		// 抽出した文字がEOFならループ終了
		if (c == EOF)
		{
			break;
		}
		// 抽出した文字がドットなら、通常餌を生成
		else if (c == '.')
		{
			//Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);

			//CreateObject<Food>(generate_location);
			x++;
		}
		// 抽出した文字がドットなら、パワー餌を生成
		else if (c == 'P')
		{
			//Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			//CreateObject<PowerFood>(generate_location);
			x++;
		}
		// 抽出した文字が空白文字なら、生成しないで次の文字を見に行く
		else if (c == ' ')
		{
			x++;
		}
		// 抽出した文字が改行文字なら、次の行を見に行く
		else if (c == '\n')
		{
			x = 0;
			y++;
		}
	}
	// 開いたファイルを閉じる
	fclose(fp);
}

// 作成したステージの情報配列を使って背景を生成
void InGameScene::DrawStageMap()
{
}

// csvを読み込んでオブジェクトの情報配列を作成
void InGameScene::LoadStageObjectCSV()
{
	// 読み込むファイル名
	std::string file_name = "Resource/Map/StageMap.csv";
	// 指定ファイルを読み込む
	std::ifstream ifs(file_name);

	// エラーチェック
	if (ifs.fail())
	{
		throw (file_name + "が開けません\n");
	}

	// ファイルから1行ずつ読み込む
	std::string line;
	// 生成するオブジェクト情報を生成
	MapObjectData data;
	while (std::getline(ifs, line))
	{
		// 読み込んだ文字と値を代入する
		sscanf_s(
			line.c_str(),
			"%c,%d,%d,%d,%d",
			&data.mode, (unsigned int)sizeof(data.mode),
			&data.x_size, &data.y_size,
			&data.spos_x, &data.spos_y
		);

		// 値を代入されたオブジェクト情報を配列に挿入
		map_object.push_back(data);
	}
}

// 作成したオブジェクトの情報配列（map_object）を使ってオブジェクトを生成
void InGameScene::CreateMapObject()
{
}
