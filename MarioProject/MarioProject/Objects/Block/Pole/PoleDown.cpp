#include "PoleDown.h"

#include "../../../Utility/ResourceManager.h"

PoleDown::PoleDown()
{
}

PoleDown::~PoleDown()
{
}

// 初期化処理
void PoleDown::Initialize()
{
	// 動作フラグのオン
	is_mobility = true;

	//画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/pole_down.png")[0];

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eGoal;
	collision.hit_object_type.push_back(eObjectType::ePlayer);

	// 当たり判定サイズの設定
	box_size = D_OBJECT_SIZE;
}

// 更新処理
void PoleDown::Update(float delta_second)
{
}

// 終了時処理
void PoleDown::Finalize()
{
	ResourceManager::DeleteInstance();
}

void PoleDown::OnHitCollision(GameObjectBase* hit_object)
{
}
