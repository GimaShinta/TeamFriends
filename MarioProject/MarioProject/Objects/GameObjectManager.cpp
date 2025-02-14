#include "GameObjectManager.h"
#include "../Application/Application.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
	// ����Y��h�~
	Finalize();
}

// �C���X�^���X�i�I�u�W�F�N�g�ւ̎Q�Ɓj�̍폜
void GameObjectManager::DeleteInstance()
{
	// ���N���X�̃|�C���^�i���̂��A�h���X�̐�ŕۗL�j
	static GameObjectManager* instance = nullptr;

	// �C���X�^���X�����݂��Ă���ꍇ�A�폜����
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

// ����������
void GameObjectManager::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
void GameObjectManager::Update(const float& delta_second)
{
	// �����ł���I�u�W�F�N�g���Q�[���z��Ɉړ�������
	CheckCreateObject();

	// �C���Q�[���z����̃I�u�W�F�N�g���X�V����
	for (GameObjectBase* obj : game_object)
	{
		// �Q�[���I�u�W�F�N�g�̍X�V�������J�n����i���삪�d���Ȃ�̂�h���j
		obj->Update(delta_second);
	}

	// �����蔻��m�F����
	for (int i = 0; i < game_object.size(); i++)
	{
		// �ړ��̋���
		if (game_object[i]->GetMobility() == false)
		{
			continue;
		}

		// ���Ă���I�u�W�F�N�g�������ł���Γ����蔻��𖳂���
		for (int j = 0; j < game_object.size(); j++)
		{
			if (i == j)
			{
				continue;
			}

			// �v���C���[�ƃG�l�~�[���������Ă��邩���`�F�b�N
			CheckCollision(game_object[i], game_object[j]);
		}
	}

	// �폜�����I�u�W�F�N�g��z��ɓ����
	CheckDesroyObject();
}

// �`�揈��
void GameObjectManager::Draw() const
{
	// �Q�[���z����̃I�u�W�F�N�g��`�悷��
	for (GameObjectBase* obj : game_object)
	{
		// �Q�[���I�u�W�F�N�g�̕`�揈�����J�n����i���삪�d���Ȃ�̂�h���j
		obj->Draw(screen_offset);
	}
}

// �I���������i��ɃI�u�W�F�N�g���X�g�j
void GameObjectManager::Finalize()
{
	// �I�u�W�F�N�g���X�g���̃I�u�W�F�N�g��j������
	DestoryAllObject();

	// ���I�z��̉��
	if (!create_object.empty())
	{
		create_object.clear();
	}
	if (!destroy_object.empty())
	{
		destroy_object.clear();
	}
}

// ��������I�u�W�F�N�g�����邩������
void GameObjectManager::CheckCreateObject()
{
	// �����z��ɃI�u�W�F�N�g������΁A�C���Q�[���z��ɑ}������
	if (!create_object.empty())
	{
		std::vector<GameObjectBase*> object_to_add;

		// �����z��ɂ���I�u�W�F�N�g�̐�������
		for (GameObjectBase* obj : create_object)
		{
			// �E�B���h�E���ɓ����Ă�����
			if (obj->GetLocation().x >= 0 && obj->GetLocation().x - (D_OBJECT_SIZE * 2) <= D_WIN_MAX_X &&
				obj->GetLocation().y >= 0 && obj->GetLocation().y + (D_OBJECT_SIZE * 2) <=D_WIN_MAX_Y)
			{
				// �ꎞ�ێ�
				object_to_add.push_back(obj);
			}
		}
		// �E�B���h�E���I�u�W�F�N�g�̐�������
		for (GameObjectBase* obj_game : object_to_add)
		{
			// ���C���[������ɏ��Ԃ����ւ���
			int z_layer = obj_game->GetZLayer();
			std::vector<GameObjectBase*>::iterator itr = game_object.begin();	// �I�u�W�F�N�g���X�g�̐擪
			// ���X�g�̖����ɂȂ�܂ő�������
			for (; itr != game_object.end(); itr++)
			{
				// Z���C���[���傫���ꏊ�ɗv�f��ǉ�����
				// �� itr->ZLayer{1, 1, 2, 3}�Az_layer = 2 �̎�
				//    itr->ZLayer{1, 1, 2, z_layer, 3}�Ƃ���
				if (z_layer < (*itr)->GetZLayer())
				{
					break;
				}
			}
			// �C���Q�[���z��֊i�[
			game_object.insert(itr, obj_game);
			// �ǉ��ς݃I�u�W�F�N�g�̍폜
			create_object.erase(std::remove(create_object.begin(), create_object.end(), obj_game), create_object.end());
		}
		// �����z����������
		object_to_add.clear();
	}
}

// �폜�����I�u�W�F�N�g�����邩������
void GameObjectManager::CheckDesroyObject()
{
	// �폜�z�񂪋�łȂ��ꍇ�A�C���Q�[���z��̃I�u�W�F�N�g��j������
	if (!destroy_object.empty())
	{
		// �폜�z��̃I�u�W�F�N�g�̐�������
		for (GameObjectBase* obj : destroy_object)
		{
			std::vector<GameObjectBase*>::iterator itr = game_object.begin();	// �I�u�W�F�N�g���X�g�̐擪
			// ���X�g�̖����ɂȂ�܂ő�������
			for (; itr != game_object.end(); itr++)
			{
				// ���X�g���ɂ���΁A�폜����
				if ((*itr) == obj)
				{
					game_object.erase(itr);
					obj->Finalize();
					delete obj;
					break;
				}
			}
		}
	}
}

//std::vector<GameObjectBase*>& GameObjectManager::CreateGameObject()
//{
//	return ;
//}

// �폜�z��ɂ���I�u�W�F�N�g���폜����
void GameObjectManager::DestroyGameObject(GameObjectBase* target)
{
	// �k���|�`�F�b�N
	if (target == nullptr)
	{
		return;
	}

	// �폜�z��ɂ���΁A�ǉ����Ȃ�
	for (GameObjectBase* obj : destroy_object)
	{
		if (obj == target)
		{
			return;
		}
	}

	// �폜�z��ɒǉ�����
	destroy_object.push_back(target);
}

/// <summary>
/// �����蔻��̃`�F�b�N
/// </summary>
/// <param name="target">��F�v���C���[</param>
/// <param name="partner">��F�G</param>
void GameObjectManager::CheckCollision(GameObjectBase* target, GameObjectBase* partner)
{
	// ���g�������Ă��邩���`�F�b�N
	if (target == nullptr || partner == nullptr)
	{
		return;
	}

	// �����蔻������쐬
	// tc��pc�́ACollision�N���X�̃����o�ϐ��𗘗p�ł���
	BoxCollision tc = target->GetCollision();
	BoxCollision pc = partner->GetCollision();

	// �����蔻�肪�L�����m�F����
	if (tc.IsCheckHitTarget(pc.object_type) || pc.IsCheckHitTarget(tc.object_type))
	{
		// �Ίp����̒��_���W�����߂�
		// �v���C���[�̍���̍��W�����߂�
		tc.point[0] += target->GetLocation() - target->GetBoxSize();
		// �v���C���[�̉E���̍��W�����߂�
		tc.point[1] += target->GetLocation() + target->GetBoxSize();
		// �G�Ƃ��u���b�N�̍���̍��W�����߂�
		pc.point[0] += partner->GetLocation() - partner->GetBoxSize();
		// �G�Ƃ��u���b�N�̉E���̍��W�����߂�
		pc.point[1] += partner->GetLocation() + partner->GetBoxSize();

		// �{�b�N�X���m�̓����蔻��
		if (IsCheckCollision(tc, pc))
		{
			// �������Ă��邱�Ƃ�ʒm����
			target->OnHitCollision(partner);
			partner->OnHitCollision(target);
		}
	}
}

const Vector2D GameObjectManager::GetScreenOffset() const
{
	return screen_offset;
}

// �C���Q�[���z��ɂ���I�u�W�F�N�g��S�č폜
void GameObjectManager::DestoryAllObject()
{
	// �C���Q�[���z�񂪋�Ȃ珈�����I������
	if (game_object.empty())
	{
		return;
	}
	// �C���Q�[���z��̃I�u�W�F�N�g���폜����
	for (GameObjectBase* obj : game_object)
	{
		obj->Finalize();
		delete obj;
	}
	// ���I�z��i�C���Q�[���z��j�̉��
	game_object.clear();
}