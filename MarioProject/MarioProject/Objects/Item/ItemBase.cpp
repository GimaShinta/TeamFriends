#include "ItemBase.h"

ItemBase::ItemBase() :
	g_velocity(0.0f)
{
}

ItemBase::~ItemBase()
{
}

// ����������
void ItemBase::Initialize()
{
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
/// <returns></returns>
void ItemBase::Update(float delata_second)
{
}

// �I��������
void ItemBase::Finalize()
{
}

/// <summary>
/// �q�b�g������
/// </summary>
/// <param name="hit_object">������������</param>
void ItemBase::OnHitCollision(GameObjectBase* hit_object)
{
}

/// <summary>
/// �ړ�����
/// </summary>
/// <param name="delta_second">�P�t���[��������̎���</param>
void ItemBase::Movement(float delta_second)
{
	this->location += velocity * delta_second;
}
