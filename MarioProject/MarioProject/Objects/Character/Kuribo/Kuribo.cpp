#include "Kuribo.h"
#include "DxLib.h"

// シングルトン継承クラスのインクルード
#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"

Kuribo::Kuribo() :
	kuribo_state(eKuriboState::NORMAL)
{
}

Kuribo::~Kuribo()
{
}

// 初期化処理
void Kuribo::Initialize()
{
	// 判定サイズの設定
	box_size = D_OBJECT_SIZE;
	// 動くかどうか（trueなら動く、falseなら止まる）
	is_mobility = true;
	// 速度の設定
	velocity.x = -100.0f;

	// 画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Enemy/kuribo.png", 3, 3, 1, 32, 32)[0];

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eBlock);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
void Kuribo::Update(float delta_second)
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
void Kuribo::Draw(const Vector2D& screen_offset) const
{
	//親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
	// 当たり判定の可視化
	DrawBox(this->location.x - this->box_size.x, this->location.y - this->box_size.y,
		this->location.x + this->box_size.x, this->location.y + this->box_size.y, GetColor(255, 0, 0), TRUE);
}

// 終了時処理（使ったインスタンスなどの削除）
void Kuribo::Finalize()
{
	ResourceManager::DeleteInstance();
	GameObjectManager::DeleteInstance();
}

/// <summary>
/// ヒットした時の処理
/// </summary>
/// <param name="hit_object">当たった相手</param>
void Kuribo::OnHitCollision(GameObjectBase* hit_object)
{
	// インスタンスの取得
	GameObjectManager* rm = Singleton<GameObjectManager>::GetInstance();
	// マリオに当たったら
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		// クリボーの上に触れたら
		if (hit_object->GetVelocity().y > 1000.0f)
		{
			// enumかなにかで死んだ状態にするのがいいかも
			// 動きを止める
			is_mobility = false;

			// マリオをジャンプさせる
			hit_object->SetVelocity(Vector2D(hit_object->GetVelocity().x, -1500));
			// 削除配列へ
			rm->DestroyGameObject(this);
		}
		// クリボーの上以外に触れたら
		else
		{
			rm->DestroyGameObject(hit_object);
		}
	}
}