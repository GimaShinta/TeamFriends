#include"ResultScene.h"
#include"DxLib.h"

// �V���O���g���p���N���X�̃C���N���[�h
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

// ����������
void ResultScene::Initialize()
{
	// �}���I�摜�̓Ǎ��݂Ə����ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	mario_image = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32)[0];
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

	//�y�f�o�b�O�p�z�X�y�[�X�L�[�ŏI������(end��ʂɑJ��)
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::eXit;
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
	SetFontSize(32);
	//DrawFormatString(D_WIN_MAX_X / 2 - ((D_OBJECT_SIZE * 2) * 1), D_WIN_MAX_Y / 2 - (D_OBJECT_SIZE / 2), GetColor(255, 255, 255), " �~ %d", player_zanki, TRUE);
	// �t���O�ŃX�^�[�g�����X�^�[�g�����߂�
	DrawString(340, 450, "SPACE TO RESTART", GetColor(255, 255, 255), TRUE);
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
