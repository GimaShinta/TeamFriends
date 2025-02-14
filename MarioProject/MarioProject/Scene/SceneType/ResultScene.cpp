#include"ResultScene.h"
#include"DxLib.h"

// �V���O���g���p���N���X�̃C���N���[�h
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

// ����������
void ResultScene::Initialize()
{
	// �}���I�摜�̓Ǎ��݂Ə����ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	mario_image = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32)[0];
	ui_num = rm->GetImages("Resource/Images/UI/num.png", 15, 15, 1, 16, 16);

	game_over_sound = rm->GetSounds("Resource/Sounds/SE_GameOver.wav");
	death_sound = rm->GetSounds("Resource/Sounds/SE_Death.wav");
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
/// <returns></returns>
eSceneType ResultScene::Update(float delta_second)
{
	//���͋@�\�̎擾
	InputManager* input = Singleton<InputManager>::GetInstance();

	// �c�@��0�ł͂Ȃ��Ƃ�
	if (zanki > 0)
	{
		//SPACE�L�[�Ń^�C�g����ʂɑJ�ڂ���
		if (input->GetKeyDown(KEY_INPUT_SPACE))
		{
			if (zanki < 3)
			{
				PlaySoundMem(death_sound, DX_PLAYTYPE_NORMAL);
			}
			// �c�@�����炷
			zanki--;
			return eSceneType::eInGame;
		}
	}
	else
	{
		PlaySoundMem(game_over_sound, DX_PLAYTYPE_NORMAL);
		// �c�@��0�ɂȂ�����^�C�g���֑J��
		zanki = 3;
		return eSceneType::eTitle;
	}

	// ���U���g�V�[�����Ƃ������Ƃ�Ԃ�
	return GetNowSceneType();
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
/// <returns></returns>
void ResultScene::Draw(float delta_second)
{
	DrawRotaGraph(D_WIN_MAX_X / 2 - ((D_OBJECT_SIZE * 2) * 1.5), D_WIN_MAX_Y / 2, 1.2, 0.0, mario_image, TRUE);
	DrawRotaGraph(D_WIN_MAX_X / 2 - (D_OBJECT_SIZE / 2), D_WIN_MAX_Y / 2, 2.5, 0.0, ui_num[11], TRUE);
	DrawRotaGraph(D_WIN_MAX_X / 2 + (D_OBJECT_SIZE * 2), D_WIN_MAX_Y / 2 + (D_OBJECT_SIZE / 6), 2.0, 0.0, ui_num[zanki], TRUE);
	SetFontSize(32);
	// �t���O�ŃX�^�[�g�����X�^�[�g�����߂�
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

// �I���������i�g�����C���X�^���X�̍폜�Ƃ��j
void ResultScene::Finalize()
{
	InputManager::DeleteInstance();
	ResourceManager::DeleteInstance();
}

/// <summary>
/// ���݂̃V�[�����
/// </summary>
/// <returns>���݂̓��U���g�V�[���ł�</returns>
eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}
