#pragma once
#include "../GameObjectBase.h"

// �A�C�e�����N���X
class ItemBase : public GameObjectBase
{
public:
	ItemBase();
	~ItemBase();

public:
	// ����������
	virtual void Initialize() override;
	// �I��������
	virtual void Finalize() override;
};

