#pragma once
#include "Brick.h"
// �j��\�u���b�N�̔j�ЃN���X
class BlickDebris : public BlockBase
{
private:
	float g_velocity;
	float kaiten;

public:
	BlickDebris();
	~BlickDebris();

public:
	// ����������
	void Initialize() override;

	/// <summary>
    /// �X�V����
    /// </summary>
    /// <param name="delata_second">�P�t���[��������̎���</param>
	virtual void Update(float delta_second) override;
};