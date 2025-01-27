#include"InGameScene.h"
#include"../../Utility/InputManager.h"

//コメントアウト
//#include"../../Object/Character/Player/Player.h"

#include"DxLib.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

// 初期化処理
void InGameScene::Initialize()
{
	//コメントアウト
	//ObjectManager* object_manager = Singleton<ObjectManager>::GetInstance();
	//object_manager->CreateObject<Player>(Vector2D(100, 600));
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
/// <returns></returns>
eSceneType InGameScene::Update(float delta_second)
{
	//コメントアウト
	//ObjectManager* obj_manager = Singleton<ObjectManager>::GetInstance();
	//obj_manager->Update(delta_second);

	//入力機能の取得
	InputManager* input = Singleton<InputManager>::GetInstance();

	//【デバッグ用】Yキーでリザルト画面に遷移する
	if (input->GetKeyDown(KEY_INPUT_Y))
	{
		return eSceneType::eResult;
	}

	return GetNowSceneType();
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
/// <returns></returns>
void InGameScene::Draw(float delta_second) const
{
	//コメントアウト
	//ObjectManager* obj_manager = Singleton<ObjectManager>::GetInstance();
	//obj_manager->Draw(delta_second);

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

// csvを読み込んでステージを描画
void InGameScene::DrawStageMapCSV()
{
}

// csvを読み込んでオブジェクトの情報配列を作成
void InGameScene::LoadStageObjectCSV()
{
}

// 作成したオブジェクトの情報配列を使ってオブジェクトを生成
void InGameScene::CreateMapObject()
{
}
