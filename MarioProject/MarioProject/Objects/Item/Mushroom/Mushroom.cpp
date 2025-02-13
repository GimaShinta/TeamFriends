#include "Mushroom.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"

Mushroom::Mushroom()
{
}

Mushroom::~Mushroom()
{
}

// 初期化処理
void Mushroom::Initialize()
{
	// 動作フラグのオン
	is_mobility = true;

	//画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Item/mushroom.png", 1, 1, 1, 32, 32)[0];

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eItem;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eBlock);

	// 当たり判定サイズの設定
	box_size = D_OBJECT_SIZE;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
void Mushroom::Update(float delta_second)
{
	// 出現していなかったら
	if (is_appearance == false)
	{
		// 少しずつ上に上げて出現しているように
		// 出現位置より一マス上まで上げる
		if (location.y < ((D_OBJECT_SIZE * 2) * 9) - D_OBJECT_SIZE)
		{
			location.y = ((D_OBJECT_SIZE * 2) * 9) - D_OBJECT_SIZE;
			// 到達したら移動処理のフラグをオン
			is_appearance = true;
		}
	}
	// 出現していたら
	else
	{
		// 速度の設定
		velocity = Vector2D(100, 0);
		//重力速度の計算
		g_velocity += D_GRAVITY;
		velocity.y += g_velocity * delta_second;
	}

	// 移動処理
	__super::Movement(delta_second);
}

// 終了時処理（使ったインスタンスなどの削除）
void Mushroom::Finalize()
{
	ResourceManager::DeleteInstance();
	GameObjectManager::DeleteInstance();
}

/// <summary>
/// ヒット時処理
/// </summary>
/// <param name="hit_object">当たった相手</param>
void Mushroom::OnHitCollision(GameObjectBase* hit_object)
{
	// マリオに当たったら
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		// マリオの進行方向が上だったら
		if (hit_object->GetVelocity().y < 0.0f)
		{
			// 初期速度の設定
			velocity.y -= 100;
		}
	}
}