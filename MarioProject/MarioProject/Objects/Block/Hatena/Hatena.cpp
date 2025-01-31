#include "Hatena.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"
#include "../../../Objects/Item/Mushroom/Mushroom.h"

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
void Hatena::Update(float delata_second)
{
	// 空になったら
	if (is_kara == true)
	{
		// 空ブロックの画像にする
		image = kara_image;
	}
	else
	{
		image = hatena_animation[0];
	}
}

// 終了時処理（使ったインスタンスなどの削除）
void Hatena::Finalize()
{
	ResourceManager::DeleteInstance();
}

/// <summary>
/// ヒット時処理
/// </summary>
/// <param name="hit_object">当たった相手</param>
void Hatena::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たった相手がマリオだったらかつ、マリオの進行方向が上だったら
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		if (hit_object->GetVelocity().y < -1.0f)
		{
			// マリオを下降させる
			hit_object->SetVelocity(Vector2D(hit_object->GetVelocity().x, 1.0f));
			// 空じゃなかったら
			if (is_kara == false)
			{
				// インスタンスの取得
				GameObjectManager* gm = Singleton<GameObjectManager>::GetInstance();
				// キノコの生成
				gm->CreateObject<Mushroom>(location);
				// 空になる
				is_kara = true;
			}
		}
		//else if(hit_object->GetVelocity().x > 1.0f)
		//{
		//	// マリオを下降させる
		//	hit_object->SetVelocity(Vector2D(0.0f, hit_object->GetVelocity().y));
		//}
		//else if(hit_object->GetVelocity().x < -1.0f)
		//{
		//	// マリオを下降させる
		//	hit_object->SetVelocity(Vector2D(0.0f, hit_object->GetVelocity().y));
		//}
	}
}