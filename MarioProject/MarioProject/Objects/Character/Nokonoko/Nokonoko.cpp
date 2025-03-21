#include "Nokonoko.h"
#include "DxLib.h"

// シングルトン継承クラスのインクルード
#include "../../../Utility/ResourceManager.h"

Nokonoko::Nokonoko() :
	noko_state(eNokonokoState::NORMAL)
	, revival_move(false)
{
}

Nokonoko::~Nokonoko()
{
}

// 初期化処理
void Nokonoko::Initialize()
{
	// 判定サイズの設定
	box_size = D_OBJECT_SIZE;
	// 動くかどうか（trueなら動く、falseなら止まる）
	is_mobility = true;
	// 速度の設定
	velocity.x = -100.0f;

	// 画像の設定
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	nokonoko_animation = rm->GetImages("Resource/Images/Enemy/nokonoko.png", 2, 2, 1, 32, 64);
	revival_animation = rm->GetImages("Resource/Images/Enemy/nokonoko_revival.png", 2, 2, 1, 32, 32);
	image = nokonoko_animation[0];

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::eEnemy;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eBlock);
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
void Nokonoko::Update(float delta_second)
{
	// ノコノコの状態管理
	switch (noko_state)
	{
	case Nokonoko::NORMAL:
		// 移動の実行
		__super::Movement(delta_second);
		// アニメーション
		GameObjectBase::AnimationControl(delta_second, nokonoko_animation, nokonoko_animation_num, 8.0f);
		break;
		// 甲羅状態の時
	case Nokonoko::REVIVAL:
		image = revival_animation[0];
		// 甲羅状態で移動しているか
		if (revival_move == true)
		{
			// 移動の実行
			__super::Movement(delta_second);
			// アニメーション
			GameObjectBase::AnimationControl(delta_second, revival_animation, revival_animation_num, 8.0f);
		}
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
	// マリオに当たったら
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer)
	{
		// ノコノコの上に触れたら（ぶつかって飛び跳ねたらこのマジックナンバーのせい）
		if (hit_object->GetVelocity().y > 0.0f) 
		{
			// ノーマル状態だったら
			if (noko_state == eNokonokoState::NORMAL)
			{
				// 甲羅状態に変更
				noko_state = eNokonokoState::REVIVAL;
				// 座標少し下げる
				location.y += D_OBJECT_SIZE;
			}
			else
			{
				// 甲羅状態で踏まれたら移動
				revival_move = true;

				// マリオが左半分を踏んだ時
				if (location.x > hit_object->GetLocation().x)
				{
					// 右に速度を上げて進む
					velocity *= -5.0f;
				}
				// マリオが右半分を踏んだ時
				else if (location.x < hit_object->GetLocation().x)
				{
					// 左に速度を上げて進む
					velocity *= 5.0f;
				}
			}

			// マリオをジャンプさせる
			hit_object->SetVelocity(Vector2D(hit_object->GetVelocity().x, -1500));
		}
		// ノコノコの上以外に触れたら
		else 
		{
			//// マリオを削除する（バグあり）
			//rm->DestroyGameObject(hit_object);
		}
	}
}