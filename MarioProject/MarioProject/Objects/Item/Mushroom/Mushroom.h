#pragma once
#include "../ItemBase.h"

// キノコクラス
class Mushroom : public ItemBase
{
public:
	Mushroom();
	~Mushroom();

public:
	// 初期化処理
	virtual void Initialize() override;
	// 終了時処理
	virtual void Finalize() override;
};

