#include "ItemHatena.h"
#include "../../../Utility/ResourceManager.h"

ItemHatena::ItemHatena()
{
}

ItemHatena::~ItemHatena()
{
}

void ItemHatena::Initialize()
{
	__super::Initialize();
	//‰æ‘œ‚Ìİ’è
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	item_sound = rm->GetSounds("Resource/Sounds/SE_ItemAppearance.wav");
}
