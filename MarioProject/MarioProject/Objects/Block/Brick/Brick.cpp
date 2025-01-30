#include "Brick.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"
#include "../../../Objects/Item/Coin/Coin.h"
#include "BlickDebris.h"

Brick::Brick() :
	coin(nullptr)
	, is_destruction(false)
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
void Brick::Update(float delata_second)
{
	// 破壊されていたら
	if (is_destruction == true)
	{
		// インスタンスの取得
		GameObjectManager* gm = Singleton<GameObjectManager>::GetInstance();
		gm->DestroyGameObject(this);
		gm->CreateObject<BlickDebris>(location + box_size);
		gm->CreateObject<BlickDebris>(location - box_size);
		gm->CreateObject<BlickDebris>(Vector2D(location.x + box_size.x, location.y - box_size.y));
		gm->CreateObject<BlickDebris>(Vector2D(location.x - box_size.x, location.y + box_size.y));
		is_destruction = false;
	}
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset"></param>
void Brick::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
	// 当たり判定の可視化
	DrawBox(this->location.x - this->box_size.x, this->location.y - this->box_size.y,
		this->location.x + this->box_size.x, this->location.y + this->box_size.y, GetColor(255, 0, 0), FALSE);
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

		// 破壊されていなかったら
		if (is_destruction == false)
		{
			// インスタンスの取得
			GameObjectManager* gm = Singleton<GameObjectManager>::GetInstance();
			// コインの生成
			coin = gm->CreateObject<Coin>(location);
			// 破壊フラグをオンにする
			is_destruction = true;
		}
	}
}
