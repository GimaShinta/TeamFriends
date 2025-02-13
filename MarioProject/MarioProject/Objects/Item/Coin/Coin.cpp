#include "Coin.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"

Coin::Coin()
{
}

Coin::~Coin()
{
}

// 初期化処理
void Coin::Initialize()
{
	// 動作フラグのオン
	is_mobility = true;

	//画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Item/coin.png", 4, 4, 1, 32, 32)[0];

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eItem;
	collision.hit_object_type.push_back(eObjectType::ePlayer);

	// 当たり判定サイズの設定
	box_size = D_OBJECT_SIZE;

	//// 上に飛ばす
	//velocity.y -= 700.0f;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
void Coin::Update(float delta_second)
{
	// 出現したら
	if (is_appearance == true)
	{
		// 重力速度の計算
		g_velocity += D_GRAVITY;
		velocity.y += g_velocity * delta_second;
	}

	// 下に落ちているとき
	if (velocity.y > 1000.0f)
	{
		// インスタンスの取得
		GameObjectManager* gm = Singleton<GameObjectManager>::GetInstance();
		// 自身を削除
		gm->DestroyGameObject(this);
	}

	// 親クラスの移動処理
	__super::Movement(delta_second);
}

// 終了時処理（使ったインスタンスなどの削除）
void Coin::Finalize()
{
	ResourceManager::DeleteInstance();
	GameObjectManager::DeleteInstance();
}

/// <summary>
/// ヒット時処理
/// </summary>
/// <param name="hit_object">当たった相手</param>
void Coin::OnHitCollision(GameObjectBase* hit_object)
{
	// マリオに当たったら
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		// マリオの進行方向が上だったら
		if (hit_object->GetVelocity().y < 0.0f)
		{
			// 初期速度の設定
			velocity.y -= 1000;
			is_appearance = true;
		}
	}
}