#include "BlockBase.h"

BlockBase::BlockBase()
{
}

BlockBase::~BlockBase()
{
}

// ����������
void BlockBase::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delata_second">�P�t���[��������̎���</param>
void BlockBase::Update(float delata_second)
{
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset"></param>
void BlockBase::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

// �I��������
void BlockBase::Finalize()
{
}

/// <summary>
/// �q�b�g������
/// </summary>
/// <param name="hit_object">������������</param>
void BlockBase::OnHitCollision(GameObjectBase* hit_object)
{
}

/// <summary>
/// �Q�[���I�W�F�N�g�̃T�C�Y�ύX
/// </summary>
/// <param name="x_size">x�̃T�C�Y</param>
/// <param name="y_size">y�̃T�C�Y</param>
void BlockBase::SetSizeData(int x_size, int y_size)
{
	box_size.x = x_size * D_OBJECT_SIZE;
	box_size.y = y_size * D_OBJECT_SIZE;
}