#pragma once
#include "Hatena.h"
class ItemHatena :
    public Hatena
{
public:
	ItemHatena();
	~ItemHatena();

	/// <summary>
    /// ƒqƒbƒgˆ—
    /// </summary>
    /// <param name="hit_object">“–‚½‚Á‚½‘Šè</param>
	void OnHitCollision(GameObjectBase* hit_object) override;
};

