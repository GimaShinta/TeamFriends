#pragma once
#include "../ItemBase.h"

// コインクラス
class Coin : public ItemBase
{
public:
	Coin();
	~Coin();

public:
	// 初期化処理
	virtual void Initialize() override;
	// 終了時処理
	virtual void Finalize() override;
};

