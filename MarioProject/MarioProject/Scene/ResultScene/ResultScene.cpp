#include"ResultScene.h"
#include"../../Utility/InputManager.h"
#include"DxLib.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

void ResultScene::Initialize()
{

}

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

void ResultScene::Draw(float delta_second) const
{
	DrawFormatString(10, 10, GetColor(100, 255, 0), "リザルト画面です");
}

void ResultScene::Finalize()
{
}

eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}
