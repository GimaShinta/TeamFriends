#include"ResultScene.h"
#include"DxLib.h"

// シングルトン継承クラスのインクルード
#include"../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include"../../Application/Application.h"

ResultScene::ResultScene() :
	mario_image(NULL)
{
}

ResultScene::~ResultScene()
{
}

// 初期化処理
void ResultScene::Initialize()
{
	// マリオ画像の読込みと初期設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	mario_image = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32)[0];
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
/// <returns></returns>
eSceneType ResultScene::Update(float delta_second)
{
	//入力機能の取得
	InputManager* input = Singleton<InputManager>::GetInstance();

	//【デバッグ用】スペースキーで終了する(end画面に遷移)
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::eXit;
	}

	// リザルトシーンだということを返す
	return GetNowSceneType();
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
/// <returns></returns>
void ResultScene::Draw(float delta_second)
{
	DrawRotaGraph(D_WIN_MAX_X / 2 - ((D_OBJECT_SIZE * 2) * 1.5), D_WIN_MAX_Y / 2, 1.2, 0.0, mario_image, TRUE);
	SetFontSize(32);
	//DrawFormatString(D_WIN_MAX_X / 2 - ((D_OBJECT_SIZE * 2) * 1), D_WIN_MAX_Y / 2 - (D_OBJECT_SIZE / 2), GetColor(255, 255, 255), " × %d", player_zanki, TRUE);
	// フラグでスタートかリスタートか決める
	DrawString(340, 450, "SPACE TO RESTART", GetColor(255, 255, 255), TRUE);
	SetFontSize(16);
}

// 終了時処理（使ったインスタンスの削除とか）
void ResultScene::Finalize()
{
	InputManager::DeleteInstance();
	ResourceManager::DeleteInstance();
}

/// <summary>
/// 現在のシーン情報
/// </summary>
/// <returns>現在はリザルトシーンです</returns>
eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}
