#pragma once
#include "PoleDown.h"
class PoleTop :
    public PoleDown
{
public:
	PoleTop();
	~PoleTop();

public:
	// 初期化処理
	void Initialize() override;
};

