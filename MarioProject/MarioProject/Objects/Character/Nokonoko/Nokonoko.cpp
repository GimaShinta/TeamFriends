#include "Nokonoko.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"

Nokonoko::Nokonoko()
{
}

Nokonoko::~Nokonoko()
{
}

// 初期化処理
void Nokonoko::Initialize()
{
	// 判定サイズの設定
	box_size = Vector2D(24.0f, 48.0f);
	// 動くかどうか（trueなら動く、falseなら止まる）
	is_mobility = true;
	// 速度の設定
	velocity.x = -100.0f;

	// 画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Enemy/nokonoko.png", 2, 2, 1, 32, 64)[0];

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
	// 移動の実行
	__super::Movement(delta_second);

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
}