#include "BlickDebris.h"

#include "../../../Utility/ResourceManager.h"
#include "DxLib.h"

BlickDebris::BlickDebris() :
	g_velocity(0.0f)
	, kaiten(0.0f)
{
}

BlickDebris::~BlickDebris()
{
}

// 初期化処理
void BlickDebris::Initialize()
{
	// 動作フラグのオン
	is_mobility = true;

	//画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Block/bloak_1.png")[0];

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eNone;

	velocity.y -= 100.0f;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delata_second">１フレーム当たりの時間</param>
void BlickDebris::Update(float delta_second)
{
	//重力速度の計算
	g_velocity += D_GRAVITY;
	velocity.y += g_velocity * delta_second;

	kaiten += 0.1f;

	location += velocity * delta_second;
}
