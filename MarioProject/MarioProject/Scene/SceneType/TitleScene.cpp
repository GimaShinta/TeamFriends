#include"TitleScene.h"
#include"DxLib.h"

// �V���O���g���p���N���X�̃C���N���[�h
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

// ����������
void TitleScene::Initialize()
{
	// �C���X�^���X�̎擾
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	title_image = rm->GetImages("Resource/Images/title.png", 1, 1, 1, 32, 32)[0];
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
/// <returns></returns>
eSceneType TitleScene::Update(float delta_second)
{
	//���͋@�\�̎擾
	InputManager* input = Singleton<InputManager>::GetInstance();

	//�y�f�o�b�O�p�z�X�y�[�X�L�[�ŃC���Q�[����ʂɑJ�ڂ���
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
 		return eSceneType::eResult;
	}

	// ���݂̃V�[�����^�C�g���Ƃ������Ƃ�Ԃ�
	return GetNowSceneType();
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
/// <returns></returns>
void TitleScene::Draw(float delta_second)
{
	// �^�C�g���摜�̕`��
	DrawRotaGraph(D_WIN_MAX_X / 2, D_WIN_MAX_Y / 2, 1.5, 0.0, title_image, TRUE);
}

// �I���������i�g�����C���X�^���X�̍폜�Ƃ��j
void TitleScene::Finalize()
{
	InputManager::DeleteInstance();
}

/// <summary>
/// ���݂̃V�[�����
/// </summary>
/// <returns>���݂̓^�C�g���V�[���ł�</returns>
eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}
