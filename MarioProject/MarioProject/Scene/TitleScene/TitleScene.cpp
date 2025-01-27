#include"TitleScene.h"
#include"../../Utility/InputManager.h"
#include"DxLib.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

// 初期化処理
void TitleScene::Initialize()
{

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
		return eSceneType::eInGame;
	}

	return GetNowSceneType();
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
/// <returns></returns>
void TitleScene::Draw(float delta_second) const
{
	DrawFormatString(10, 10, GetColor(255, 255, 255), "タイトル画面です");
}

// 終了時処理
void TitleScene::Finalize()
{
}

/// <summary>
/// 現在のシーン情報
/// </summary>
/// <returns>現在はタイトルシーンです</returns>
eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}
