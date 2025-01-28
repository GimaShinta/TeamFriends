#include"InGameScene.h"
#include"../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"

#include "../../Objects/GameObjectManager.h"
#include "../../Objects/Character/Player/Player.h"
#include "../../Objects/Character/Kuribo/Kuribo.h"

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
	// �C���X�^���X�̎擾
	GameObjectManager* object_manager = Singleton<GameObjectManager>::GetInstance();
	object_manager->CreateObject<Player>(Vector2D(100, 600));
	object_manager->CreateObject<Kuribo>(Vector2D(700, 600));
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
/// <returns></returns>
eSceneType InGameScene::Update(float delta_second)
{
	// �C���X�^���X�̎擾
	GameObjectManager* obj_manager = Singleton<GameObjectManager>::GetInstance();
	InputManager* input = Singleton<InputManager>::GetInstance();

	// GameObjectManager�N���X��Update�֐��ɃA�N�Z�X
	obj_manager->Update(delta_second);

	//�y�f�o�b�O�p�zY�L�[�Ń��U���g��ʂɑJ�ڂ���
	if (input->GetKeyDown(KEY_INPUT_Y))
	{
		return eSceneType::eResult;
	}

	// ���݂̃V�[���^�C�v�̓C���Q�[���ł��Ƃ������Ƃ��Ăяo������return�ő���
	return GetNowSceneType();
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
/// <returns></returns>
void InGameScene::Draw(float delta_second) const
{
	// �e�N���X�̕`�揈��
	__super::Draw(delta_second);

	// �R�����g�A�E�e�B
	//GameObjectManager* obj_manager = Singleton<GameObjectManager>::GetInstance();
	//obj_manager->Draw();

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

// csv��ǂݍ���ŃX�e�[�W�̏��z����쐬
void InGameScene::LoadStageMapCSV()
{
	FILE* fp = NULL;
	std::string file_name = "Resource/Map/StageMapFoods.csv";

	// �w�肳�ꂽ�t�@�C�����J��
	errno_t result = fopen_s(&fp, file_name.c_str(), "r");

	// �G���[�`�F�b�N
	if (result != 0)
	{
		throw (file_name + "���J���܂���");
	}

	int x = 0;
	int y = 0;

	// �t�@�C�����̕������m�F���Ă���
	while (true)
	{
		// �t�@�C������1�������o����
		int c = fgetc(fp);

		// ���o����������EOF�Ȃ烋�[�v�I��
		if (c == EOF)
		{
			break;
		}
		// ���o�����������h�b�g�Ȃ�A�ʏ�a�𐶐�
		else if (c == '.')
		{
			//Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);

			//CreateObject<Food>(generate_location);
			x++;
		}
		// ���o�����������h�b�g�Ȃ�A�p���[�a�𐶐�
		else if (c == 'P')
		{
			//Vector2D generate_location = (Vector2D((float)x, (float)y) * D_OBJECT_SIZE) + (D_OBJECT_SIZE / 2.0f);
			//CreateObject<PowerFood>(generate_location);
			x++;
		}
		// ���o�����������󔒕����Ȃ�A�������Ȃ��Ŏ��̕��������ɍs��
		else if (c == ' ')
		{
			x++;
		}
		// ���o�������������s�����Ȃ�A���̍s�����ɍs��
		else if (c == '\n')
		{
			x = 0;
			y++;
		}
	}
	// �J�����t�@�C�������
	fclose(fp);
}

// �쐬�����X�e�[�W�̏��z����g���Ĕw�i�𐶐�
void InGameScene::DrawStageMap()
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
