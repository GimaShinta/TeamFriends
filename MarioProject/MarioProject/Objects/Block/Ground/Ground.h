#pragma once

#include "../BlockBase.h"

// 地面クラス
class Ground : public BlockBase
{
public:
	Ground();
	~Ground();

public:
	// 初期化処理
	void Initialize() override;
	// 終了時処理
	void Finalize() override;
};

