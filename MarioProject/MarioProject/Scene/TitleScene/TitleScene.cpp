#include"TitleScene.h"
#include"../../Utility/InputManager.h"
#include"DxLib.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

// ����������
void TitleScene::Initialize()
{

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
		return eSceneType::eInGame;
	}

	return GetNowSceneType();
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
/// <returns></returns>
void TitleScene::Draw(float delta_second) const
{
	DrawFormatString(10, 10, GetColor(255, 255, 255), "�^�C�g����ʂł�");
}

// �I��������
void TitleScene::Finalize()
{
}

/// <summary>
/// ���݂̃V�[�����
/// </summary>
/// <returns>���݂̓^�C�g���V�[���ł�</returns>
eSceneType TitleScene::GetNowSceneType() const
{
	return eSceneType::eTitle;
}
