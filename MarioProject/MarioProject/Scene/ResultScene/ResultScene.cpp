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
	//���͋@�\�̎擾
	InputManager* input = Singleton<InputManager>::GetInstance();

	//�y�f�o�b�O�p�z�X�y�[�X�L�[�ŏI������(end��ʂɑJ��)
	if (input->GetKeyDown(KEY_INPUT_SPACE))
	{
		return eSceneType::eXit;
	}

	return GetNowSceneType();
}

void ResultScene::Draw(float delta_second) const
{
	DrawFormatString(10, 10, GetColor(100, 255, 0), "���U���g��ʂł�");
}

void ResultScene::Finalize()
{
}

eSceneType ResultScene::GetNowSceneType() const
{
	return eSceneType::eResult;
}
