#include"InGameScene.h"
#include"DxLib.h"

// Singleton�p���N���X�̃C���N���[�h
#include"../../Utility/InputManager.h"
#include"../../Utility/ResourceManager.h"
#include "../../Objects/GameObjectManager.h"
#include "../../Application/Application.h"

// �Q�[���I�u�W�F�N�g�̃C���N���[�h
#include "../../Objects/GameObjectBase.h"
#include "../../Objects/Character/Player/Player.h"
#include "../../Objects/Character/Kuribo/Kuribo.h"
#include "../../Objects/Character/Nokonoko/Nokonoko.h"
#include "../../Objects/Block/Brick/Brick.h"
#include "../../Objects/Block/Hatena/Hatena.h"
#include "../../Objects/Block/Hatena/ItemHatena.h"
#include "../../Objects/Item/Coin/Coin.h"
#include "../../Objects/Item/Mushroom/Mushroom.h"
#include "../../Objects/Block/Pole/PoleDown.h"
#include "../../Objects/Block/Pole/PoleTop.h"

//�X�e�[�g
#include"../../Objects/Character/Player/StateBase/PlayerStateBase.h"

#include <fstream>
#include <iostream>
#include <sstream>

// �X�e�[�W�̍ő�}�X��
#define MAP_SQUARE_X 211
#define MAP_SQUARE_Y 15

InGameScene::InGameScene():
	  player(nullptr)
	, game_object(nullptr)
	, image(NULL)
	, bgm(NULL)
	, scroll(0.0f)
	, score(0)
	, animation_count(0)
	, animation_time(0.0f)
{
}

InGameScene::~InGameScene()
{
}

// ����������
void InGameScene::Initialize()
{
	// csv��ǂݍ���ŃI�u�W�F�N�g�̏��z����쐬
	LoadStageObjectCSV();
	// �쐬�����I�u�W�F�N�g�̏��z��imap_object�j���g���ăI�u�W�F�N�g�𐶐�
	CreateMapObject();
	// csv��ǂݍ���ŃX�e�[�W�̏��z����쐬
	map_array = LoadStageMapCSV();

	// �Q�[���I�u�W�F�N�g�ɃX�e�[�W�̏��z����Q�Ƃ��ēn��
	player->SetMapData(map_array);

	// ���\�[�X�}�l�[�W���[�̃C���X�^���X�̎擾�irm�ɂ̓��\�[�X�}�l�[�W���[�N���X�ɃA�N�Z�X�ł���A�h���X������j
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	ui_num = rm->GetImages("Resource/Images/UI/num.png", 15, 15, 1, 16, 16);

	//UI����
	ui_image[0] = rm->GetImages("Resource/Images/UI/name_mario.png", 1, 0, 0, 32, 32)[0];
	ui_image[1] = rm->GetImages("Resource/Images/UI/time.png", 1, 0, 0, 32, 32)[0];
	ui_image[2] = rm->GetImages("Resource/Images/UI/top.png", 1, 0, 0, 32, 32)[0];
	ui_image[3] = rm->GetImages("Resource/Images/UI/world.png", 1, 0, 0, 32, 32)[0];

	//BGM�̓ǂݍ���
	bgm = LoadSoundMem("Resource/Sounds/BGM/Nonomura.wav");
	//�{�����[���iBGM�j
	ChangeVolumeSoundMem(255 * 30 / 100, bgm);

	// �X�R�A�i�f�o�b�O�p�j
	score = 12000;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
/// <returns></returns>
eSceneType InGameScene::Update(float delta_second)
{
	//BGM�Đ�
	PlaySoundMem(bgm, DX_PLAYTYPE_LOOP, FALSE);

	// �C���X�^���X�̎擾
	GameObjectManager* obj_manager = Singleton<GameObjectManager>::GetInstance();
	InputManager* input = Singleton<InputManager>::GetInstance();

	// GameObjectManager�N���X��Update�֐��ɃA�N�Z�X
	obj_manager->Update(delta_second);

	// �X�N���[������
	Scroll(delta_second);


	//�y�f�o�b�O�p�zY�L�[�Ń��U���g��ʂɑJ�ڂ���
	if (input->GetKeyDown(KEY_INPUT_Y))
	{
		return eSceneType::eResult;
	}

	// �}���I������ł�����
	if (player->GetIsDestroy() == true)
	{
		return eSceneType::eResult;
	}
	// �N���A���Ă�����
	if (player->GetIsClear() == true)
	{
		// �N���A�]�C
		animation_time += delta_second;
		if (animation_time >= 0.07f)
		{
			animation_time = 0.0f;
			animation_count++;
			if (animation_count >= 50)
			{
			    obj_manager->DestroyGameObject(player);
				return eSceneType::eResult;
			}
		}
	}

	// ���݂̃V�[���^�C�v�̓C���Q�[���ł��Ƃ������Ƃ��Ăяo������return�ő���
	return GetNowSceneType();
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
/// <returns></returns>
void InGameScene::Draw(float delta_second)
{
	//��(Stage)
	DrawBox(0, 0, D_WIN_MAX_X, D_WIN_MAX_Y, GetColor(147, 187, 236), TRUE);

	//UI_�}���I
	DrawRotaGraph(150,40,1.8,0.0, ui_image[0], TRUE);

	//UI_�X�R�A
	DrawRotaGraph(3 * 30, 70, 1.8, 0.0, ui_num[score / 100000], TRUE);
	DrawRotaGraph(4 * 30, 70, 1.8, 0.0, ui_num[(score % 100000) / 10000], TRUE);
	DrawRotaGraph(5 * 30, 70, 1.8, 0.0, ui_num[(score % 100000 % 10000) / 1000], TRUE);
	DrawRotaGraph(6 * 30, 70, 1.8, 0.0, ui_num[(score % 100000 % 10000 % 1000) / 100], TRUE);
	DrawRotaGraph(7 * 30, 70, 1.8, 0.0, ui_num[(score % 100000 % 10000 % 1000 % 100) / 10], TRUE);
	DrawRotaGraph(8 * 30, 70, 1.8, 0.0, ui_num[(score % 100000 % 10000 % 1000 % 100) % 10], TRUE);

	// �쐬�����X�e�[�W�̏��z����g���Ĕw�i��`��
	DrawStageMap();

	// �e�N���X�̕`�揈��
	__super::Draw(delta_second);
}

// �I���������i�g�����C���X�^���X�̍폜�Ƃ��j
void InGameScene::Finalize()
{
	GameObjectManager* obj_manager = Singleton<GameObjectManager>::GetInstance();
	obj_manager->Finalize();

	InputManager::DeleteInstance();
	GameObjectManager::DeleteInstance();
	ResourceManager::DeleteInstance();	
}

/// <summary>
/// ���݂̃V�[�����
/// </summary>
/// <returns>���݂̓C���Q�[���V�[���ł�</returns>
eSceneType InGameScene::GetNowSceneType() const
{
	return eSceneType::eInGame;
}

// �X�N���[������
void InGameScene::Scroll(float delta_second)
{
	// �X�N���[���ʂ��}���I�ɑ���
	player->SetScrollValue(scroll);

	//�v���C���[���^�񒆂��ړ����̎�...
	if (player->GetLocation().x >= D_WIN_MAX_X / 2 && player->now_state == ePlayerState::RUN)
	{
		//�X�N���[������
		if (scroll <= (D_OBJECT_SIZE * 2) * MAP_SQUARE_X - D_WIN_MAX_X)
		{
			//�}���I�̑��x�ɍ��킹�ăX�N���[������
			float p_speed = player->GetVelocity().x;
			scroll += p_speed * delta_second;

			// �����̃I�u�W�F�N�g�p�X�N���[��
			for (GameObjectBase* object : object_array)
			{
				// �I�u�W�F�N�g�̑��x���}���I�ɍ��킹��
				object->SetScroll(object->GetLocation().x - (p_speed * delta_second));
			}
		}
		else
		{
			//���䏈���̐؂�ւ�
			player->stage_end = TRUE;
		}
	}
}

// csv��ǂݍ���ŃX�e�[�W�̏��z����쐬
std::vector<std::vector<char>> InGameScene::LoadStageMapCSV()
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

	// �߂�l�p�X�e�[�W���z��
	std::vector<std::vector<char>> data;
	// csv��1�s�̕������ۑ�����ϐ�
	std::string line;

	// getline��csv�t�@�C����1�s�̕������ǂݍ��݁A�����line�ɑ��
	while (std::getline(ifs, line))
	{
		std::vector<char> row;
		// line�ɓ����Ă��镶������J���}��؂�ŕ���
		std::stringstream ss(line);
		std::string cell;

		// getline�ŃJ���}�ŋ�؂�ꂽ������ǂݍ���
		while (std::getline(ss, cell, ','))
		{
			// �ŏ��̕����݂̂𒊏o
			row.push_back(cell[0]);
		}
		// �P�s�̕������S�ĕ������ꂽ��ԂŊi�[
		data.push_back(row);
	}

	// �쐬�����X�e�[�W�̏��z��
	return data;
}

// �쐬�����X�e�[�W�̏��z����g���Ĕw�i��`��
void InGameScene::DrawStageMap()
{
	//Resource�̃C���X�^���X�擾
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();

	// �X�e�[�W�Ǎ��݂ō쐬�����I�u�W�F�N�g���̔z�񂩂�`�悷��
	for (int i = 0; i < MAP_SQUARE_Y; i++)
	{
		for (int j = 0; j < MAP_SQUARE_X; j++)
		{
			// �P�����𒊏o
			char c = map_array[i][j];
			// �����Ă��镶���ŉ摜�̕ύX
			switch (c)
			{
			case '0':	//��͕`�悵�Ȃ��̂ŉ摜�ǂݍ��݂͍s��Ȃ�
			case '1':	//�n�� => �����\��
				continue;
			case '2':
				image = rm->GetImages("Resource/Images/Block/floor.png")[0];
				break;
			case 'a':
				image = rm->GetImages("Resource/Images/mountain_left.png")[0];
				break;
			case 'b':
				image = rm->GetImages("Resource/Images/mountain_surface2.png")[0];
				break;
			case 'c':
				image = rm->GetImages("Resource/Images/mountain_surface.png")[0];
				break;
			case 'd':
				image = rm->GetImages("Resource/Images/mountain_surface1.png")[0];
				break;
			case 'e':
				image = rm->GetImages("Resource/Images/mountain_right.png")[0];
				break;
			case 'f':
				image = rm->GetImages("Resource/Images/mountain_up.png")[0];
				break;
			case 'g':
				image = rm->GetImages("Resource/Images/ha0.png")[0];
				break;
			case 'h':
				image = rm->GetImages("Resource/Images/ha1.png")[0];
				break;
			case 'i':
				image = rm->GetImages("Resource/Images/ha2.png")[0];
				break;
			case 'j':
				image = rm->GetImages("Resource/Images/dokan_left_down.png")[0];
				break;
			case 'k':
				image = rm->GetImages("Resource/Images/dokan_right_down.png")[0];
				break;
			case 'l':
				image = rm->GetImages("Resource/Images/dokan_left_up.png")[0];
				break;
			case 'm':
				image = rm->GetImages("Resource/Images/dokan_right_up.png")[0];
				break;
			case 'n':
				image = rm->GetImages("Resource/Images/Block/kai_block.png")[0];
				break;
			case 'o':
				image = rm->GetImages("Resource/Images/flag.png")[0];
				break;
			case 'p':
				image = rm->GetImages("Resource/Images/siro1.png")[0];
				break;
			case 'q':
				image = rm->GetImages("Resource/Images/pole.png")[0];
				break;
			case 'r':
				image = rm->GetImages("Resource/Images/cloud1.png")[0];
				break;
			case 's':
				image = rm->GetImages("Resource/Images/cloud2.png")[0];
				break;
			case 't':
				image = rm->GetImages("Resource/Images/cloud3.png")[0];
				break;
			case 'u':
				image = rm->GetImages("Resource/Images/cloud4.png")[0];
				break;
			case 'v':
				image = rm->GetImages("Resource/Images/cloud5.png")[0];
				break;
			case 'w':
				image = rm->GetImages("Resource/Images/cloud6.png")[0];
				break;
			}
			// �X�e�[�W�������ĕ`��
			DrawRotaGraphF(D_OBJECT_SIZE + ((D_OBJECT_SIZE * 2) * j) - scroll, D_OBJECT_SIZE + ((D_OBJECT_SIZE *  2) * i), 1.5, 0.0, image, TRUE);
		}
	}
}
// csv��ǂݍ���ŃI�u�W�F�N�g�̏��z����쐬
void InGameScene::LoadStageObjectCSV()
{
	// �ǂݍ��ރt�@�C����
	std::string file_name = "Resource/Map/ObjectData.csv";
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
	ObjectMapData data;
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
	//�C���X�^���X�̎擾
	GameObjectManager* obj_m = Singleton<GameObjectManager>::GetInstance();

	// �X�e�[�W�Ǎ��݂ō쐬�����I�u�W�F�N�g���̔z�񂩂�`�悷��
	for (int i = 0; i < map_object.size(); i++)
	{
		// csv����ǂݍ��񂾏��𗘗p�ł���悤�ɂ���
		const ObjectMapData& object = map_object[i];

		// �I�u�W�F�N�g�̐������W
		Vector2D generate_location = Vector2D((D_OBJECT_SIZE * 2) * object.spos_x, (D_OBJECT_SIZE * 2) * object.spos_y ) - D_OBJECT_SIZE;

		// �ŏ��̕���������đ������l��ς���
		switch (object.mode)
		{
		case 'P':
			// �v���C���[�̐���
			player = obj_m->CreateObject<Player>(generate_location);
			break;
		case 'K':
			// �N���{�[�̐���
			game_object = obj_m->CreateObject<Kuribo>(generate_location);
			// �������p�ł���悤�ɔz��ŊǗ�
			object_array.push_back(game_object);
			break;
		case 'N':
			// �m�R�m�R�̐���
			// �w����������ɂ��炵�Đ���
			generate_location.y -= D_OBJECT_SIZE;
			game_object = obj_m->CreateObject<Nokonoko>(generate_location);
			// �������p�ł���悤�ɔz��ŊǗ�
			object_array.push_back(game_object);
			break;
		case 'B':
			// �j��\�u���b�N�̐���
			game_object = obj_m->CreateObject<Brick>(generate_location);
			// �������p�ł���悤�ɔz��ŊǗ�
			object_array.push_back(game_object);
			break;
		case 'H':
			// �R�C���̐���
			game_object = obj_m->CreateObject<Coin>(generate_location);
			// �������p�ł���悤�ɔz��ŊǗ�
			object_array.push_back(game_object);
			// �n�e�i�u���b�N�̐���
			game_object = obj_m->CreateObject<Hatena>(generate_location);
			// �������p�ł���悤�ɔz��ŊǗ�
			object_array.push_back(game_object);
			break;
		case 'O':
			// �L�m�R�̐���
			game_object = obj_m->CreateObject<Mushroom>(generate_location);
			// �������p�ł���悤�ɔz��ŊǗ�
			object_array.push_back(game_object);
			// �n�e�i�u���b�N�̐���
			game_object = obj_m->CreateObject<ItemHatena>(generate_location);
			// �������p�ł���悤�ɔz��ŊǗ�
			object_array.push_back(game_object);
			break;
		case 'D':
			// �|�[���_�E���̐���
			game_object = obj_m->CreateObject<PoleDown>(generate_location);
			// �������p�ł���悤�ɔz��ŊǗ�
			object_array.push_back(game_object);
			break;
		case 'T':
			// �|�[���g�b�v�̐���
			game_object = obj_m->CreateObject<PoleTop>(generate_location);
			// �������p�ł���悤�ɔz��ŊǗ�
			object_array.push_back(game_object);
			break;
		default:
			continue;
		}
	}
}
