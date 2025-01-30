#include "BlockBase.h"
#include "DxLib.h"

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
	// �����蔻��̉���
	DrawBox(this->location.x - this->box_size.x, this->location.y - this->box_size.y,
		this->location.x + this->box_size.x, this->location.y + this->box_size.y, GetColor(255, 0, 0), TRUE);
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