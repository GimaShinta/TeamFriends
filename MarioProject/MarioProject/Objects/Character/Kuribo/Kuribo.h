#pragma once

#include "../CharacterBase.h"

class Kuribo :public CharacterBase
{
public:
	Kuribo();
	~Kuribo();

public:
	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset)const override;
	void Finalize() override;

public:
	void OnHitCollision(GameObjectBase* hit_object) override;
};

