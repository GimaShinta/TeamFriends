#include"InGameScene.h"
#include"../../Utility/InputManager.h"

//�R�����g�A�E�g
//#include"../../Object/Character/Player/Player.h"

#include"DxLib.h"

InGameScene::InGameScene()
{
}

InGameScene::~InGameScene()
{
}

// ����������
void InGameScene::Initialize()
{
	//�R�����g�A�E�g
	//ObjectManager* object_manager = Singleton<ObjectManager>::GetInstance();
	//object_manager->CreateObject<Player>(Vector2D(100, 600));
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
/// <returns></returns>
eSceneType InGameScene::Update(float delta_second)
{
	//�R�����g�A�E�g
	//ObjectManager* obj_manager = Singleton<ObjectManager>::GetInstance();
	//obj_manager->Update(delta_second);

	//���͋@�\�̎擾
	InputManager* input = Singleton<InputManager>::GetInstance();

	//�y�f�o�b�O�p�zY�L�[�Ń��U���g��ʂɑJ�ڂ���
	if (input->GetKeyDown(KEY_INPUT_Y))
	{
		return eSceneType::eResult;
	}

	return GetNowSceneType();
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
/// <returns></returns>
void InGameScene::Draw(float delta_second) const
{
	//�R�����g�A�E�g
	//ObjectManager* obj_manager = Singleton<ObjectManager>::GetInstance();
	//obj_manager->Draw(delta_second);

	DrawFormatString(10, 10, GetColor(0, 255, 255), "�C���Q�[����ʂł�");
}

// �I���������i�g�����C���X�^���X�̍폜�Ƃ��j
void InGameScene::Finalize()
{
	InputManager::DeleteInstance();
}

/// <summary>
/// ���݂̃V�[�����
/// </summary>
/// <returns>���݂̓C���Q�[���V�[���ł�</returns>
eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}

// �摜�̓ǂݍ���
void InGameScene::LoadImages()
{
}

// csv��ǂݍ���ŃX�e�[�W��`��
void InGameScene::DrawStageMapCSV()
{
}

// csv��ǂݍ���ŃI�u�W�F�N�g�̏��z����쐬
void InGameScene::LoadStageObjectCSV()
{
}

// �쐬�����I�u�W�F�N�g�̏��z����g���ăI�u�W�F�N�g�𐶐�
void InGameScene::CreateMapObject()
{
}
