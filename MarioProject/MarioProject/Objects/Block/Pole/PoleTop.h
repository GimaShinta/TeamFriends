#pragma once
#include "PoleDown.h"
class PoleTop :
    public PoleDown
{
public:
	PoleTop();
	~PoleTop();

public:
	// ����������
	void Initialize() override;
};

