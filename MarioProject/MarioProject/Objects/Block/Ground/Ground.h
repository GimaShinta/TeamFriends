#pragma once

#include "../BlockBase.h"

// �n�ʃN���X
class Ground : public BlockBase
{
public:
	Ground();
	~Ground();

public:
	// ����������
	void Initialize() override;
	// �I��������
	void Finalize() override;
};

