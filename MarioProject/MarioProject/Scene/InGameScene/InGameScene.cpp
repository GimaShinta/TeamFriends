#include"InGameScene.h"
#include"../../Utility/InputManager.h"

//コメントアウト
//#include"../../Object/Character/Player/Player.h"
//#include"../../Object/ObjectManager.h"

#include"DxLib.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

void InGameScene::Initialize()
{
	//コメントアウト
	//ObjectManager* object_manager = Singleton<ObjectManager>::GetInstance();
	//object_manager->CreateObject<Player>(Vector2D(100, 600));
}

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

void InGameScene::Draw(float delta_second) const
{
	//コメントアウト
	//ObjectManager* obj_manager = Singleton<ObjectManager>::GetInstance();
	//obj_manager->Draw(delta_second);

	DrawFormatString(10, 10, GetColor(0, 255, 255), "インゲーム画面です");
}

void InGameScene::Finalize()
{
}

eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}
