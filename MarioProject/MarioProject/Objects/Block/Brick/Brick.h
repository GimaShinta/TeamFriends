#pragma once
#include "../BlockBase.h"

// �j��\�u���b�N
class Brick :
    public BlockBase
{
public:
	Brick();
	~Brick();

public:
	// ����������
	void Initialize() override;

	// �I��������
	void Finalize() override;
};

