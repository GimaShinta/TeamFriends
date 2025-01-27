#include"ResultScene.h"
#include"../../Utility/InputManager.h"
#include"DxLib.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

// 初期化処理
void ResultScene::Initialize()
{

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

	return GetNowSceneType();
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
/// <returns></returns>
void ResultScene::Draw(float delta_second) const
{
	DrawFormatString(10, 10, GetColor(100, 255, 0), "リザルト画面です");
}

// 終了時処理
void ResultScene::Finalize()
{
}

/// <summary>
/// 現在のシーン情報
/// </summary>
/// <returns>現在はリザルトシーンです</returns>
eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}
