#include "Kuribo.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"

Kuribo::Kuribo()
{
}

Kuribo::~Kuribo()
{
}

// 初期化処理
void Kuribo::Initialize()
{
	// 判定サイズの設定
	box_size = Vector2D(24.0f);
	is_mobility = true;
	velocity.x = 100.0f;

	// 画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32)[0];

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
}

// 更新処理
void Kuribo::Update(float delta_second)
{
	// 移動の実行
	location.x -= velocity.x * delta_second;

	// 親クラスの更新処理を呼び出す
	__super::Update(delta_second);
}

// 描画処理
void Kuribo::Draw(const Vector2D& screen_offset) const
{
	//親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

// 終了時処理（使ったインスタンスなどの削除）
void Kuribo::Finalize()
{
	ResourceManager::DeleteInstance();
}

//ヒット時処理
void Kuribo::OnHitCollision(GameObjectBase* hit_object)
{
}