#pragma once
#include "../GameObjectBase.h"

class BlockBase : public GameObjectBase
{
public:
	BlockBase();
	~BlockBase();

public:
	virtual void Initialize() override;
	virtual void Update(float delata_second) override;
	virtual void Draw(const Vector2D& screen_offset)const override;
	virtual void Finalize() override;

public:
	virtual void OnHitCollision(GameObjectBase* hit_object) override;
	void SetSizeData(int x_size, int y_size);

};

