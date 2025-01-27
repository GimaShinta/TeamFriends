#include"InGameScene.h"
#include"../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"

//�R�����g�A�E�g
//#include"../../Object/Character/Player/Player.h"

#include"DxLib.h"

#include <fstream>
#include <iostream>

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
	// �ǂݍ��ރt�@�C����
	std::string file_name = "Resource/Map/StageMap.csv";
	// �w��t�@�C����ǂݍ���
	std::ifstream ifs(file_name);

	// �G���[�`�F�b�N
	if (ifs.fail())
	{
		throw (file_name + "���J���܂���\n");
	}

	// �t�@�C������1�s���ǂݍ���
	std::string line;
	// ��������I�u�W�F�N�g���𐶐�
	MapObjectData data;
	while (std::getline(ifs, line))
	{
		// �ǂݍ��񂾕����ƒl��������
		sscanf_s(
			line.c_str(),
			"%c,%d,%d,%d,%d",
			&data.mode, (unsigned int)sizeof(data.mode),
			&data.x_size, &data.y_size,
			&data.spos_x, &data.spos_y
		);

		// �l�������ꂽ�I�u�W�F�N�g����z��ɑ}��
		map_object.push_back(data);
	}
}

// �쐬�����I�u�W�F�N�g�̏��z��imap_object�j���g���ăI�u�W�F�N�g�𐶐�
void InGameScene::CreateMapObject()
{
}
