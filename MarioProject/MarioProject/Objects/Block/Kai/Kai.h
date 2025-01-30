#pragma once
#include "../BlockBase.h"

// 破壊不可ブロッククラス
class Kai :
    public BlockBase
{
public:
	Kai();
	~Kai();

public:
	// 初期化処理
	void Initialize() override;
	// 終了時処理
	void Finalize() override;
};

