#include "PoleTop.h"

#include "../../../Utility/ResourceManager.h"

PoleTop::PoleTop()
{
}

PoleTop::~PoleTop()
{
}

void PoleTop::Initialize()
{
	// 動作フラグのオン
	is_mobility = true;

	//画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/pole.png")[0];

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eGoal;
	collision.hit_object_type.push_back(eObjectType::ePlayer);

	// 当たり判定サイズの設定
	box_size = D_OBJECT_SIZE;
}
