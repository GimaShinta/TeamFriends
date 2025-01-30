#pragma once
#include "../GameObjectBase.h"

// アイテム基底クラス
class ItemBase : public GameObjectBase
{
public:
	ItemBase();
	~ItemBase();

public:
	// 初期化処理
	virtual void Initialize() override;
	// 終了時処理
	virtual void Finalize() override;
};

