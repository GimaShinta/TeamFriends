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
	// �I��������
	virtual void Finalize() override;
};

