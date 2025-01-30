#include "Nokonoko.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"

Nokonoko::Nokonoko() :
	noko_state(eNokonokoState::NORMAL)
	, revival_size(0.0f)
{
}

Nokonoko::~Nokonoko()
{
}

// 初期化処理
void Nokonoko::Initialize()
{
	// 判定サイズの設定
	box_size = Vector2D(D_OBJECT_SIZE, D_OBJECT_SIZE);
	// 動くかどうか（trueなら動く、falseなら止まる）
	is_mobility = true;
	// 速度の設定
	velocity.x = -100.0f;

	// 画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	nokonoko_animation = rm->GetImages("Resource/Images/Enemy/nokonoko.png", 2, 2, 1, 32, 64);
	revival_animation = rm->GetImages("Resource/Images/Enemy/nokonoko_revival.png", 2, 2, 1, 32, 32);

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
void Nokonoko::Update(float delta_second)
{
	switch (noko_state)
	{
	case Nokonoko::NORMAL:
		// 移動の実行
		__super::Movement(delta_second);
		image = nokonoko_animation[0];
		break;
	case Nokonoko::REVIVAL:
		image = revival_animation[0];
		break;
	case Nokonoko::DEAD:
		break;
	default:
		break;
	}


	// 親クラスの更新処理を呼び出す
	__super::Update(delta_second);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset"></param>
void Nokonoko::Draw(const Vector2D& screen_offset) const
{
	//親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

// 終了時処理（使ったインスタンスなどの削除）
void Nokonoko::Finalize()
{
	ResourceManager::DeleteInstance();
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="hit_object">当たった相手</param>
void Nokonoko::OnHitCollision(GameObjectBase* hit_object)
{
	// インスタンスの取得
	GameObjectManager* rm = Singleton<GameObjectManager>::GetInstance();
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		// ノコノコの上に触れたら
		if (hit_object->GetVelocity().y > 1000.0f)
		{
			noko_state = eNokonokoState::REVIVAL;
			// マリオをジャンプさせる
			hit_object->SetVelocity(Vector2D(hit_object->GetVelocity().x, -1500));
		}
		// ノコノコの上以外に触れたら
		else
		{
			// マリオを削除する
			rm->DestroyGameObject(hit_object);
		}
	}
}