#include"ResultScene.h"
#include"DxLib.h"

// シングルトン継承クラスのインクルード
#include"../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include"../../Application/Application.h"

int zanki = 3;

ResultScene::ResultScene() :
	mario_image(NULL)
	, game_over_sound(NULL)
	, death_sound(NULL)
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
	ui_num = rm->GetImages("Resource/Images/UI/num.png", 15, 15, 1, 16, 16);

	game_over_sound = rm->GetSounds("Resource/Sounds/SE_GameOver.wav");
	death_sound = rm->GetSounds("Resource/Sounds/SE_Death.wav");
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

	// 残機が0ではないとき
	if (zanki > 0)
	{
		//SPACEキーでタイトル画面に遷移する
		if (input->GetKeyDown(KEY_INPUT_SPACE))
		{
			if (zanki < 3)
			{
				PlaySoundMem(death_sound, DX_PLAYTYPE_NORMAL);
			}
			// 残機を減らす
			zanki--;
			return eSceneType::eInGame;
		}
	}
	else
	{
		PlaySoundMem(game_over_sound, DX_PLAYTYPE_NORMAL);
		// 残機が0になったらタイトルへ遷移
		zanki = 3;
		return eSceneType::eTitle;
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
	DrawRotaGraph(D_WIN_MAX_X / 2 - (D_OBJECT_SIZE / 2), D_WIN_MAX_Y / 2, 2.5, 0.0, ui_num[11], TRUE);
	DrawRotaGraph(D_WIN_MAX_X / 2 + (D_OBJECT_SIZE * 2), D_WIN_MAX_Y / 2 + (D_OBJECT_SIZE / 6), 2.0, 0.0, ui_num[zanki], TRUE);
	SetFontSize(32);
	// フラグでスタートかリスタートか決める
	if (zanki >= 2)
	{
		DrawString(340, 450, "SPACE TO START", GetColor(255, 255, 255), TRUE);
	}
	else if (zanki >= 1)
	{
		DrawString(340, 450, "SPACE TO RESTART", GetColor(255, 255, 255), TRUE);
	}
	else
	{
		DrawString(400, 450, "RESTART", GetColor(255, 255, 255), TRUE);
	}
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
