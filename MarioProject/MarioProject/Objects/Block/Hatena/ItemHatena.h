#pragma once
#include "Hatena.h"
class ItemHatena :
    public Hatena
{
public:
	ItemHatena();
	~ItemHatena();

	/// <summary>
    /// ヒット時処理
    /// </summary>
    /// <param name="hit_object">当たった相手</param>
	void OnHitCollision(GameObjectBase* hit_object) override;
};

