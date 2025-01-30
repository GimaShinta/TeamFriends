#pragma once
#include "../ItemBase.h"

// �L�m�R�N���X
class Mushroom : public ItemBase
{
public:
	Mushroom();
	~Mushroom();

public:
	// ����������
	virtual void Initialize() override;

	/// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="delta_second">�P�t���[��������̎���</param>
	virtual void Update(float delata_second);

	// �I��������
	virtual void Finalize() override;

	/// <summary>
    /// �q�b�g�����Ƃ��̏���
    /// </summary>
    /// <param name="hit_object">�v���C���[���Ƃ�����A�����͓G�Ƃ��u���b�N�Ɠ����������ƂɂȂ�</param>
	virtual void OnHitCollision(GameObjectBase* hit_object);

};

