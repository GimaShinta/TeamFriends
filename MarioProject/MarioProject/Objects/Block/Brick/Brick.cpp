#include "Brick.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"
#include "../../../Objects/Item/Coin/Coin.h"

Brick::Brick() :
	is_destruction(false)
	, block_sound(NULL)
{
}

Brick::~Brick()
{
}

// 初期化処理
void Brick::Initialize()
{
	// 動作フラグのオン
	is_mobility = true;

	//画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Block/block.png", 1, 1, 1, 32, 32)[0];

	block_sound = rm->GetSounds("Resource/Sounds/SE_Block.wav");

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
void Brick::Update(float delta_second)
{
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

	// 画面外で削除
	__super::Update(delta_second);

	// 移動処理
	location += velocity * delta_second;
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset"></param>
void Brick::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理
	__super::Draw(screen_offset);
}

// 終了時処理（使ったインスタンスなどの削除）
void Brick::Finalize()
{
	ResourceManager::DeleteInstance();
	GameObjectManager::DeleteInstance();
}

/// <summary>
/// ヒット時処理
/// </summary>
/// <param name="hit_object">当たった相手</param>
void Brick::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たった相手がマリオだったらかつ、マリオの進行方向が上だったら
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer && hit_object->GetVelocity().y < -1.0f)
	{
		// マリオを下降させる
		hit_object->SetVelocity(Vector2D(hit_object->GetVelocity().x, 1.0f));

		// 破壊されていたら
		if (is_destruction == false)
		{
			PlaySoundMem(block_sound, DX_PLAYTYPE_BACK);
			// 上に上昇させる
			velocity.y -= 500;
		}
	}
}
