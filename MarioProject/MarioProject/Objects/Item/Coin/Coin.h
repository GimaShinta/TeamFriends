#pragma once
#include "../ItemBase.h"

// �R�C���N���X
class Coin : public ItemBase
{
public:
	Coin();
	~Coin();

public:
	// ����������
	virtual void Initialize() override;

	/// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="delta_second">�P�t���[��������̎���</param>
	virtual void Update(float delta_second);

	// �I��������
	virtual void Finalize() override;

	/// <summary>
    /// �q�b�g�����Ƃ��̏���
    /// </summary>
    // <param name="hit_object">�v���C���[���Ƃ�����A�����͓G�Ƃ��u���b�N�Ɠ����������ƂɂȂ�</param>
	virtual void OnHitCollision(GameObjectBase* hit_object);
};

