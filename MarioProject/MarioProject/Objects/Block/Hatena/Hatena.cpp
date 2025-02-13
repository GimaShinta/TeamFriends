#include "Hatena.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"

Hatena::Hatena() :
	 is_kara(false)
	, kara_image(NULL)
{
}

Hatena::~Hatena()
{
}
 
// 初期化処理
void Hatena::Initialize()
{
	// 動作フラグのオン
	is_mobility = true;

	//画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	hatena_animation = rm->GetImages("Resource/Images/Block/hatena.png", 4, 4, 1, 32, 32);
	kara_image = rm->GetImages("Resource/Images/Block/kara_block.png")[0];
	image = hatena_animation[0];

	//当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);

	// 当たり判定サイズの設定
	box_size = D_OBJECT_SIZE;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delata_second">１フレーム当たりの時間</param>
void Hatena::Update(float delta_second)
{
	// 空になったら
	if (is_kara == true)
	{
		// 空ブロックの画像にする
		image = kara_image;
	}
	else
	{
		// アニメーション
		GameObjectBase::AnimationControl(delta_second, hatena_animation, hatena_animation_num, 6.0f);
	}

	// 一マス上に到達したら移動反転
	if (location.y < old_location.y - D_OBJECT_SIZE)
	{
		velocity.y *= -1;
	}

	// 初期位置に戻る
	if (location.y > old_location.y)
	{
		location.y = old_location.y;
		velocity = 0;
	}

	// 移動処理
	location += velocity * delta_second;
}

// 終了時処理（使ったインスタンスなどの削除）
void Hatena::Finalize()
{
	ResourceManager::DeleteInstance();
	GameObjectManager::DeleteInstance();
}

/// <summary>
/// ヒット時処理
/// </summary>
/// <param name="hit_object">当たった相手</param>
void Hatena::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たった相手がマリオだったら
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		// マリオの進行方向が上だったら
		if (hit_object->GetVelocity().y < -1.0f)
		{
			// マリオを下降させる
			hit_object->SetVelocity(Vector2D(hit_object->GetVelocity().x, 1.0f));
			// 空じゃなかったら
			if (is_kara == false)
			{
				// 上に上昇させる
				velocity.y -= 500;
				// 空になる
				is_kara = true;
			}
		}
	}
}