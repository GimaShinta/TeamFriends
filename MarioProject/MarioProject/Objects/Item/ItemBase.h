#pragma once
#include "../GameObjectBase.h"

#define D_GRAVITY (30.0f)    //�d�͉����x(m/ss)

// �A�C�e�����N���X
class ItemBase : public GameObjectBase
{
protected:
	float g_velocity;       // �d��

public:
	ItemBase();
	~ItemBase();

public:
	// ����������
	virtual void Initialize() override;

	/// <summary>
	/// �X�V����
	/// </summary>
	/// <param name="delta_second">�P�t���[��������̎���</param>
	/// <returns></returns>
	virtual void Update(float delata_second);

	// �I��������
	virtual void Finalize() override;

	/// <summary>
	/// �q�b�g�����Ƃ��̏���
	/// </summary>
	/// <param name="hit_object">�v���C���[���Ƃ�����A�����͓G�Ƃ��u���b�N�Ɠ����������ƂɂȂ�</param>
	virtual void OnHitCollision(GameObjectBase* hit_object);

	/// <summary>
    /// �ړ�����
    /// </summary>
    /// <param name="delta_second">�P�t���[��������̎���</param>
	virtual void Movement(float delta_second);
};

