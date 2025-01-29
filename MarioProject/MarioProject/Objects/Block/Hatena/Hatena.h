#pragma once
#include "../BlockBase.h"
class Hatena :
    public BlockBase
{
public:
	Hatena();
	~Hatena();

public:
	void Initialize() override;
	void Draw(const Vector2D& screen_offset)const override;
};

