#pragma once
#include "Hatena.h"
class ItemHatena :
    public Hatena
{
public:
	ItemHatena();
	~ItemHatena();

	/// <summary>
    /// �q�b�g������
    /// </summary>
    /// <param name="hit_object">������������</param>
	void OnHitCollision(GameObjectBase* hit_object) override;
};

