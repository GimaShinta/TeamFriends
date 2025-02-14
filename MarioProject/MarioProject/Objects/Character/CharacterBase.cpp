#include "CharacterBase.h"

#include "../../Scene/SceneType/InGameScene.h"

#include <cmath>

CharacterBase::CharacterBase():
	g_velocity(0.0f)
	, scroll_value(0.0f)
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

/// <summary>
/// �X�N���[���ʂ̐ݒ�
/// </summary>
/// <param name="scroll">�X�N���[����</param>
void CharacterBase::SetScrollValue(float& scroll)
{
	this->scroll_value = scroll;
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
bool CharacterBase::MapCollision(int x, int y)
{
	// ���[���h���W��ۑ�
	Vector2D object_rect = Vector2D (this->location.x + scroll_value, this->location.y);
	// �T�C�Y��ۑ�
	Vector2D object_box = this->GetBoxSize();
	// �l�̒��_��ۑ�
	Vector2D vertices[4] =
	{
		// ����̍��W
		Vector2D(object_rect - object_box),
		// �����̍��W
		Vector2D(object_rect.x - object_box.x, object_rect.y + object_box.y),
		// �E��̍��W
		Vector2D(object_rect.x + object_box.x, object_rect.y - object_box.y),
		// �E���̍��W
		Vector2D(object_rect + object_box),
	};

	for (int i = 0; i < 4; i++)
	{
		// �v���C���[�̌��݂̃}�X�̈ʒu
		int x_id = std::floor(vertices[i].x) / (D_OBJECT_SIZE * 2);
		int y_id = std::floor(vertices[i].y) / (D_OBJECT_SIZE * 2);
		// �v���C���[������}�X��0�ȊO�̕�����������
		if (map_data[y_id + y][x_id + x] == '2' || map_data[y_id + y][x_id + x] == 'j' || map_data[y_id + y][x_id + x] == 'k'
			|| map_data[y_id + y][x_id + x] == 'l' || map_data[y_id + y][x_id + x] == 'm' || map_data[y_id + y][x_id + x] == 'n'
			|| map_data[y_id + y][x_id + x] == 'H'|| map_data[y_id + y][x_id + x] == 'B'|| map_data[y_id + y][x_id + x] == 'O')
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
