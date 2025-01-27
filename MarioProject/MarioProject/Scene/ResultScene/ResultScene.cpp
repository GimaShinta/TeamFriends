#include"ResultScene.h"
#include"../../Utility/InputManager.h"
#include"DxLib.h"

ResultScene::ResultScene()
{
}

ResultScene::~ResultScene()
{
}

// ����������
void ResultScene::Initialize()
{

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

	return GetNowSceneType();
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
/// <returns></returns>
void ResultScene::Draw(float delta_second) const
{
	DrawFormatString(10, 10, GetColor(100, 255, 0), "���U���g��ʂł�");
}

// �I��������
void ResultScene::Finalize()
{
}

/// <summary>
/// ���݂̃V�[�����
/// </summary>
/// <returns>���݂̓��U���g�V�[���ł�</returns>
eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}
