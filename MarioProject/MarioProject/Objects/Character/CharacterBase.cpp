#include "CharacterBase.h"

#include "../../Scene/SceneType/InGameScene.h"

#include <cmath>

CharacterBase::CharacterBase():
	g_velocity(0.0f)
	, world_location(0.0f)
{
}

CharacterBase::~CharacterBase()
{
}

// ����������
void CharacterBase::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delata_second">1�t���[��������̎���</param>
void CharacterBase::Update(float delata_second)
{
	// �e�N���X�̍X�V�������Ăяo��
	__super::Update(delata_second);
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset"></param>
void CharacterBase::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈�����Ăяo��
	__super::Draw(screen_offset);
}

// �I��������
void CharacterBase::Finalize()
{
}

/// <summary>
/// �q�b�g������
/// </summary>
/// <param name="hit_object">������������</param>
void CharacterBase::OnHitCollision(GameObjectBase* hit_object)
{
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
void CharacterBase::Movement(float delta_second)
{
	location += velocity * delta_second;
}

/// <summary>
/// �X�N���[���ɍ��킹�ĉ���������
/// </summary>
/// <param name="velocity">this�I�u�W�F�N�g�̑��x</param>
void CharacterBase::SetVelocity(const Vector2D& velocity)
{
	this->velocity = velocity;
}

void CharacterBase::SetScrollValue(float& scroll)
{
	this->world_location = scroll;
}

/// <summary>
/// �X�e�[�W�̏���ݒ�
/// </summary>
/// <param name="map">�C���Q�[���ō�����X�e�[�W�����Q�ƂŎ󂯎��</param>
void CharacterBase::SetMapData( const std::vector<std::vector<char>>& map)
{
	this->map_data = map;
}

// �}�b�v�Ƃ̓����蔻��
bool CharacterBase::MapCollision()
{
	// �v���C���[�̃��[���h���W��ۑ�
	Vector2D p_rect = Vector2D (this->location.x + world_location, this->location.y);
	// �v���C���[�̃T�C�Y��ۑ�
	Vector2D p_box = this->GetBoxSize();
	// �v���C���[�̎l�̒��_��ۑ�
	Vector2D vertices[4] =
	{
		// ����̍��W
		Vector2D(p_rect - p_box),
		// �����̍��W
		Vector2D(p_rect.x - p_box.x, p_rect.y + p_box.y),
		// �E��̍��W
		Vector2D(p_rect.x + p_box.x, p_rect.y - p_box.y),
		// �E���̍��W
		Vector2D(p_rect + p_box),
	};

	for (int i = 0; i < 4; i++)
	{
		// �v���C���[�̌��݂̃}�X�̈ʒu
		int x_id = std::floor(vertices[i].x) / (D_OBJECT_SIZE * 2);
		int y_id = std::floor(vertices[i].y) / (D_OBJECT_SIZE * 2);
		// �v���C���[������}�X��0�ȊO�̕�����������
		if (map_data[y_id][x_id] == '2' || map_data[y_id][x_id] == 'j' || map_data[y_id][x_id] == 'k'
			|| map_data[y_id][x_id] == 'l' || map_data[y_id][x_id] == 'm' || map_data[y_id][x_id] == 'n')
		{
			// �ǂ̃|�C���g���������Ă��邩
			int id = i;
			// �������Ă���
			return true;
		}
	}
	// �������Ă��Ȃ�
	return false;


	//int width_range_ids[2]
	//{
	//	(world_location.x - D_OBJECT_SIZE) / (D_OBJECT_SIZE * 2),
	//	(world_location.x + D_OBJECT_SIZE) / (D_OBJECT_SIZE * 2)
	//};
	//int height_range_ids[2]
	//{
	//	(world_location.y - D_OBJECT_SIZE) / (D_OBJECT_SIZE * 2),
	//	(world_location.y + D_OBJECT_SIZE) / (D_OBJECT_SIZE * 2)
	//};

	//const int start = 0;
	//const int end = 1;

	//for (int i = height_range_ids[start]; i <= height_range_ids[end]; i++)
	//{
	//	for (int j = width_range_ids[start]; j <= width_range_ids[end]; j++)
	//	{
	//		if (map_data[i][j] == '2')
	//		{
	//			// ������
	//			return true;
	//		}
	//	}
	//}
	//return false;
}
