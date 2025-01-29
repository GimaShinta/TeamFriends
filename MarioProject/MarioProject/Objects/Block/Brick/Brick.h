#pragma once
#include "../BlockBase.h"
class Brick :
    public BlockBase
{
public:
	Brick();
	~Brick();

public:
	void Initialize() override;
	void Draw(const Vector2D& screen_offset)const override;
	void Finalize() override;
};

