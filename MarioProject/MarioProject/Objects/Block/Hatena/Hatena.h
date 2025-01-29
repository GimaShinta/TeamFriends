#pragma once
#include "../BlockBase.h"
class Hatena :
    public BlockBase
{
public:
	std::vector<int> hatena_animation;
	bool is_kara;
public:
	Hatena();
	~Hatena();

public:
	void Initialize() override;
	void Draw(const Vector2D& screen_offset)const override;
	void Finalize() override;
};

