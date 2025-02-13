#include"TitleScene.h"
#include"DxLib.h"

// シングルトン継承クラスのインクルード
#include"../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include"../../Application/Application.h"

TitleScene::TitleScene() :
	title_image(NULL)
{
}

TitleScene::~TitleScene()
{
}

// 初期化処理
void TitleScene::Initialize()
{
	// インスタンスの取得
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	title_image = rm->GetImages("Resource/Images/title.png", 1, 1, 1, 32, 32)[0];
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
/// <returns></returns>
eSceneType TitleScene::Update(float delta_second)
{
	//入力機能の取得
	InputManager* input = Singleton<InputManager>::GetInstance();

	//【デバッグ用】スペースキーでインゲーム画面に遷移する
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
 		return eSceneType::eResult;
	}

	// 現在のシーンがタイトルということを返す
	return GetNowSceneType();
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
/// <returns></returns>
void TitleScene::Draw(float delta_second)
{
	// タイトル画像の描画
	DrawRotaGraph(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2, 1.5, 0.0, title_image, TRUE);
}

// 終了時処理（使ったインスタンスの削除とか）
void TitleScene::Finalize()
{
	InputManager::DeleteInstance();
}

/// <summary>
/// 現在のシーン情報
/// </summary>
/// <returns>現在はタイトルシーンです</returns>
eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}
