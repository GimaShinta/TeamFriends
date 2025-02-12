#include"InGameScene.h"
#include"DxLib.h"

// Singleton継承クラスのインクルード
#include"../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include "../../Objects/GameObjectManager.h"
#include "../../Application/Application.h"

// ゲームオブジェクトのインクルード
#include "../../Objects/GameObjectBase.h"
#include "../../Objects/Character/Player/Player.h"
#include "../../Objects/Character/Kuribo/Kuribo.h"
#include "../../Objects/Character/Nokonoko/Nokonoko.h"
#include "../../Objects/Block/Ground/Ground.h"
#include "../../Objects/Block/Brick/Brick.h"
#include "../../Objects/Block/Hatena/Hatena.h"
#include "../../Objects/Block/Kai/Kai.h"
#include "../../Objects/Item/Coin/Coin.h"
#include "../../Objects/Item/Mushroom/Mushroom.h"

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
	, game_object(nullptr)
	, image(NULL)
	, scroll(0.0f)
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

	// ゲームオブジェクトにステージの情報配列を参照して渡す
	player->SetMapData(map_array);

	// リソースマネージャーのインスタンスの取得（rmにはリソースマネージャークラスにアクセスできるアドレスが入る）
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	ui_num = rm->GetImages("Resource/Images/UI/num.png", 15, 15, 1, 16, 16);

	//UI文字
	ui_image[0] = rm->GetImages("Resource/Images/UI/name_mario.png", 1, 0, 0, 32, 32)[0];
	ui_image[1] = rm->GetImages("Resource/Images/UI/time.png", 1, 0, 0, 32, 32)[0];
	ui_image[2] = rm->GetImages("Resource/Images/UI/top.png", 1, 0, 0, 32, 32)[0];
	ui_image[3] = rm->GetImages("Resource/Images/UI/world.png", 1, 0, 0, 32, 32)[0];


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

	//プレイヤーが真ん中かつ移動中の時...
	if (player->GetLocation().x >= D_WIN_MAX_X / 2 && player->now_state == ePlayerState::RUN)
	{
		//スクロール処理
		if (scroll <= (D_OBJECT_SIZE * 2) * MAP_SQUARE_X - D_WIN_MAX_X)
		{
			//マリオの速度に合わせてスクロールする
			float p_speed = player->GetVelocity().x;
			scroll += p_speed * delta_second;

			// 複数のオブジェクト用スクロール
			for (GameObjectBase* object : object_array)
			{
				// オブジェクトの速度もマリオに合わせる
				object->SetScroll(object->GetLocation().x - (p_speed * delta_second));
			}
		}
		else 
		{
			//制御処理の切り替え
			player->stage_end = TRUE;
		}
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
	DrawBox(0, 0, D_WIN_MAX_X, D_WIN_MAX_Y, GetColor(147, 187, 236), TRUE);

	//UI_マリオ
	DrawRotaGraph(150,40,1.8,0.0, ui_image[0], TRUE);

	//UI_数字(表示するだけ)
	/*for (int i = 0; i < 6; i++)
	{
		DrawRotaGraph(0 + i*30, 70, 1.8, 0.0, ui_num[0], TRUE);
	}*/


	// 作成したステージの情報配列を使って背景を描画
	DrawStageMap();


	// 親クラスの描画処理
	__super::Draw(delta_second);
}

// 終了時処理（使ったインスタンスの削除とか）
void InGameScene::Finalize()
{
	InputManager::DeleteInstance();
	GameObjectManager::DeleteInstance();
	ResourceManager::DeleteInstance();
}

/// <summary>
/// 現在のシーン情報
/// </summary>
/// <returns>現在はインゲームシーンです</returns>
eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}

// マップとの当たり判定（collisionでやったほうがいいかも）
bool InGameScene::LoadImages()
{
	// プレイヤーの現在地を保存
	Vector2D p_rect = player->GetLocation();
	// プレイヤーのサイズを保存
	Vector2D p_box = player->GetBoxSize();
	// プレイヤーの四つの頂点を保存
	Vector2D vertices[4] =
	{
		// 左上の座標
		Vector2D(p_rect - p_box),
		// 左下の座標
		Vector2D(p_rect.x - p_box.x, p_rect.y + p_box.y),
		// 右上の座標
		Vector2D(p_rect.x + p_box.x, p_rect.y - p_box.y),
		// 右下の座標
		Vector2D(p_rect + p_box),
	};

	for (int i = 0; i < 4 ; i++)
	{
		// プレイヤーの現在のマスの位置
		int x_id = vertices[i].x / (D_OBJECT_SIZE * 2);
		int y_id = vertices[i].y / (D_OBJECT_SIZE * 2);
		// プレイヤーがいるマスが0以外の文字だったら
		if (map_array[y_id][x_id] != '0')
		{
			// 当たっている
			return true;
		}
	}
	// 当たっていない
	return false;
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
			case 'a':
				image = rm->GetImages("Resource/Images/mountain_left.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'b':
				image = rm->GetImages("Resource/Images/mountain_surface2.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'c':
				image = rm->GetImages("Resource/Images/mountain_surface.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'd':
				image = rm->GetImages("Resource/Images/mountain_surface1.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'e':
				image = rm->GetImages("Resource/Images/mountain_right.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'f':
				image = rm->GetImages("Resource/Images/mountain_up.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'g':
				image = rm->GetImages("Resource/Images/ha0.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'h':
				image = rm->GetImages("Resource/Images/ha1.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'i':
				image = rm->GetImages("Resource/Images/ha2.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'j':
				image = rm->GetImages("Resource/Images/dokan_left_down.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'k':
				image = rm->GetImages("Resource/Images/dokan_right_down.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'l':
				image = rm->GetImages("Resource/Images/dokan_left_up.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'm':
				image = rm->GetImages("Resource/Images/dokan_right_up.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'n':
				image = rm->GetImages("Resource/Images/Block/kai_block.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'o':
				image = rm->GetImages("Resource/Images/flag.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'p':
				image = rm->GetImages("Resource/Images/siro1.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'q':
				image = rm->GetImages("Resource/Images/pole.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'r':
				image = rm->GetImages("Resource/Images/cloud1.png", 1, 1, 1, 32, 32)[0];
				break;
			case 's':
				image = rm->GetImages("Resource/Images/cloud2.png", 1, 1, 1, 32, 32)[0];
				break;
			case 't':
				image = rm->GetImages("Resource/Images/cloud3.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'u':
				image = rm->GetImages("Resource/Images/cloud4.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'v':
				image = rm->GetImages("Resource/Images/cloud5.png", 1, 1, 1, 32, 32)[0];
				break;
			case 'w':
				image = rm->GetImages("Resource/Images/cloud6.png", 1, 1, 1, 32, 32)[0];
				break;
			}
			// ステージ情報を見て描画
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
		Vector2D generate_location = Vector2D((D_OBJECT_SIZE * 2) * object.spos_x, (D_OBJECT_SIZE * 2) * object.spos_y ) - D_OBJECT_SIZE;

		// 最初の文字列を見て代入する値を変える
		switch (object.mode)
		{
		case 'P':
			// プレイヤーの生成
			player = obj_m->CreateObject<Player>(generate_location);
			break;
		case 'K':
			// クリボーの生成
			game_object = obj_m->CreateObject<Kuribo>(generate_location);
			// 複数利用できるように配列で管理
			object_array.push_back(game_object);
			break;
		case 'N':
			// ノコノコの生成
			// 背が高い分上にずらして生成
			generate_location.y -= D_OBJECT_SIZE;
			game_object = obj_m->CreateObject<Nokonoko>(generate_location);
			// 複数利用できるように配列で管理
			object_array.push_back(game_object);
			break;
		case 'B':
			// 破壊可能ブロックの生成
			game_object = obj_m->CreateObject<Brick>(generate_location);
			// 複数利用できるように配列で管理
			object_array.push_back(game_object);
			break;
		case 'H':
			// ハテナブロックの生成
			game_object = obj_m->CreateObject<Hatena>(generate_location);
			// 複数利用できるように配列で管理
			object_array.push_back(game_object);
			break;
		case 'I':
			// 繋がったブロックは1つのオブジェクトとして扱うために中心座標を求める
			generate_location = Vector2D((object.x_size * D_OBJECT_SIZE) + (object.spos_x * (D_OBJECT_SIZE * 2)) - (D_OBJECT_SIZE * 2), (object.spos_y * (D_OBJECT_SIZE * 2)));
			// 破壊不可ブロックの生成
			game_object = obj_m->CreateObject<Kai>(generate_location);
			// 複数利用できるように配列で管理
			object_array.push_back(game_object);
			// オブジェクトサイズの変更
			game_object->box_size.x = object.x_size * D_OBJECT_SIZE;
			game_object->box_size.y = object.y_size * D_OBJECT_SIZE;
			break;
		case 'G':
			// 繋がったブロックは1つのオブジェクトとして扱うために中心座標を求める
			generate_location = Vector2D((object.x_size * D_OBJECT_SIZE) + (object.spos_x * (D_OBJECT_SIZE * 2)) - (D_OBJECT_SIZE * 2), (object.spos_y * (D_OBJECT_SIZE * 2)));
			// 地面の生成
			game_object = obj_m->CreateObject<Ground>(generate_location);
			// 複数利用できるように配列で管理
			object_array.push_back(game_object);
			// オブジェクトサイズの変更
			game_object->box_size.x = object.x_size * D_OBJECT_SIZE;
			game_object->box_size.y = object.y_size * D_OBJECT_SIZE;
			break;
		case 'C':
			// コインの生成
			game_object = obj_m->CreateObject<Coin>(generate_location);
			// 複数利用できるように配列で管理
			object_array.push_back(game_object);
			break;
		default:
			continue;
		}
	}
}
