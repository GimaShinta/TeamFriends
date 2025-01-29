#include"InGameScene.h"
#include"DxLib.h"

// Singleton継承クラスのインクルード
#include"../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include "../../Objects/GameObjectManager.h"
#include "../../Application/Application.h"

// ゲームオブジェクトのインクルード
#include "../../Objects/Character/Player/Player.h"
#include "../../Objects/Character/Kuribo/Kuribo.h"
#include "../../Objects/Character/Nokonoko/Nokonoko.h"

//ステート
#include"../../Objects/Character/Player/StateBase/PlayerStateBase.h"

#include <fstream>
#include <iostream>
#include <sstream>

// ステージの最大マス数
#define MAP_SQUARE_X 211
#define MAP_SQUARE_Y 15

InGameScene::InGameScene():
	  player(nullptr)
	, kuribo(nullptr)
	, nokonoko(nullptr)
{
}

InGameScene::~InGameScene()
{
}

// 初期化処理
void InGameScene::Initialize()
{
	// csvを読み込んでオブジェクトの情報配列を作成
	LoadStageObjectCSV();
	// 作成したオブジェクトの情報配列（map_object）を使ってオブジェクトを生成
	CreateMapObject();
	// csvを読み込んでステージの情報配列を作成
	map_array = LoadStageMapCSV();

	// リソースマネージャーのインスタンスの取得（rmにはリソースマネージャークラスにアクセスできるアドレスが入る）
	//ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	//image = rm->GetImages("Resource/Images/Block/floor.png", 1, 1, 1, 32, 32)[0];

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

	Vector2D p_location = player->GetLocation();

	if (p_location.x >= D_WIN_MAX_X / 2 && player->now_state == ePlayerState::RUN) 
	{
		scroll += player->GetVelocity().x * delta_second;
	}

	// 現在のシーンタイプはインゲームですということを呼び出し元へreturnで送る
	return GetNowSceneType();
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
/// <returns></returns>
void InGameScene::Draw(float delta_second)
{
	//空(Stage)
	DrawBox(0, 0, D_WIN_MAX_X, D_WIN_MAX_Y, GetColor(92, 148, 252), TRUE);

	// 作成したステージの情報配列を使って背景を描画
	DrawStageMap();


	// 親クラスの描画処理
	__super::Draw(delta_second);

	DrawFormatString(10, 10, GetColor(0, 255, 255), "インゲーム画面です");
}

// 終了時処理（使ったインスタンスの削除とか）
void InGameScene::Finalize()
{
	InputManager::DeleteInstance();
	GameObjectManager::DeleteInstance();
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
std::vector<std::vector<char>> InGameScene::LoadStageMapCSV()
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

	// 戻り値用ステージ情報配列
	std::vector<std::vector<char>> data;
	// csvの1行の文字列を保存する変数
	std::string line;

	// getlineでcsvファイルの1行の文字列を読み込み、それをlineに代入
	while (std::getline(ifs, line))
	{
		std::vector<char> row;
		// lineに入っている文字列をカンマ区切りで分割
		std::stringstream ss(line);
		std::string cell;

		// getlineでカンマで区切られた文字を読み込む
		while (std::getline(ss, cell, ','))
		{
			// 最初の文字のみを抽出
			row.push_back(cell[0]);
		}
		// １行の文字列を全て分割された状態で格納
		data.push_back(row);
	}

	// 作成したステージの情報配列
	return data;
}

// 作成したステージの情報配列を使って背景を描画
void InGameScene::DrawStageMap()
{
	//Resourceのインスタンス取得
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();

	// ステージ読込みで作成したオブジェクト情報の配列から描画する
	for (int i = 0; i < MAP_SQUARE_Y; i++)
	{
		for (int j = 0; j < MAP_SQUARE_X; j++)
		{
			// １文字を抽出
			char c = map_array[i][j];
			// 入っている文字で画像の変更
			switch (c)
			{
			case '0':	//空は描画しないので画像読み込みは行わない
			case '1':	//地下 => 実装予定
				continue;
			case '2':
				image = rm->GetImages("Resource/Images/Block/floor.png", 1, 1, 1, 32, 32)[0];
				break;
			}
				DrawRotaGraphF(D_OBJECT_SIZE + ((D_OBJECT_SIZE * 2) * j) - scroll, D_OBJECT_SIZE + ((D_OBJECT_SIZE *  2) * i), 1.5, 0.0, image, TRUE);
		}
	}
}

// csvを読み込んでオブジェクトの情報配列を作成
void InGameScene::LoadStageObjectCSV()
{
	// 読み込むファイル名
	std::string file_name = "Resource/Map/ObjectData.csv";
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
	ObjectMapData data;
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
	//インスタンスの取得
	GameObjectManager* obj_m = Singleton<GameObjectManager>::GetInstance();

	// ステージ読込みで作成したオブジェクト情報の配列から描画する
	for (int i = 0; i < map_object.size(); i++)
	{
		// csvから読み込んだ情報を利用できるようにする
		const ObjectMapData& object = map_object[i];

		// オブジェクトの生成座標
		Vector2D generate_location = Vector2D(object.spos_x * (D_OBJECT_SIZE * 2), (object.spos_y * (D_OBJECT_SIZE * 2))) - D_OBJECT_SIZE;

		// 最初の文字列を見て代入する値を変える
		switch (object.mode)
		{
		case 'P':
			// プレイヤーの生成
			player = obj_m->CreateObject<Player>(generate_location);
			break;
		case 'K':
			// クリボーの生成
			kuribo = obj_m->CreateObject<Kuribo>(generate_location);
			break;
		case 'N':
			// ノコノコの生成
			// 背が高い分上にずらして生成
			generate_location.y -= D_OBJECT_SIZE;
			nokonoko = obj_m->CreateObject<Nokonoko>(generate_location);
			break;
		default:
			continue;
		}
	}
}
