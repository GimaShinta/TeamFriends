#pragma once
#include "../BlockBase.h"
class Kai :
    public BlockBase
{
public:
	Kai();
	~Kai();

public:
	void Initialize() override;
	void Draw(const Vector2D& screen_offset)const override;
	void Finalize() override;
};

