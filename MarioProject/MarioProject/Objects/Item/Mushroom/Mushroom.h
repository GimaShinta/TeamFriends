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
	// �I��������
	virtual void Finalize() override;
};

