#pragma once
#include "../BlockBase.h"

// �j��s�u���b�N�N���X
class Kai :
    public BlockBase
{
public:
	Kai();
	~Kai();

public:
	// ����������
	void Initialize() override;
	// �I��������
	void Finalize() override;
};

