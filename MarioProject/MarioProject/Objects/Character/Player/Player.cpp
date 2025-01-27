#include "Player.h"

#include "../../../Utility/ResourceManager.h"
#include "StateBase/State/PlayerStateFactory.h"

#include "DxLib.h"

#define D_GRAVITY (30.0f)      //重力加速度(m/ss)

Player::Player():
	  flip_flag(false)
	, now_state(ePlayerState::NONE)
	, next_state(ePlayerState::NONE)
{
}

Player::~Player()
{
}

// 初期化処理
void Player::Initialize()
{
	// 値の初期化
	state = PlayerStateFactory::Get((*this), ePlayerState::IDLE);

	// リソースマネージャーのインスタンスの取得（rmにはリソースマネージャークラスにアクセスできるアドレスが入る）
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	/* GetImagesは画像を切り分けて配列に入れてくれる関数だけど、代入するimage変数は配列変数じゃないから
	 画像が1つしか入らないため、引数の後に[0]をつける*/
	image = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32)[0];

	// 当たり判定のオブジェクト設定
	collision.is_blocking = true;
	// 自分のオブジェクトタイプ
	collision.object_type = eObjectType::ePlayer;
	// 当たる相手のオブジェクトタイプ
	collision.hit_object_type.push_back(eObjectType::eEnemy);

	is_mobility = true;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delata_second">１フレーム当たりの時間</param>
void Player::Update(float delta_second)
{
	// stateの変更処理
	if (next_state != ePlayerState::NONE && is_mobility == true)
	{
		//現在の移動状態を保管
		now_state = next_state;

		state = PlayerStateFactory::Get((*this), next_state);
		next_state = ePlayerState::NONE;
	}
	//状態別の更新処理を行う
	state->Update(delta_second);

	//重力速度の計算
	g_velocity += D_GRAVITY;
	velocity.y += g_velocity * delta_second;

	// 移動を実行する関数の呼び出し
	__super::Movement(delta_second);

	// y500.0f地点を地面と仮定
	if (location.y > 600.0f)
	{
		location.y = 600.0f;
		g_velocity = 0.0f;
	}

}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset"></param>
void Player::Draw(const Vector2D& screen_offset) const
{
	// オフセット値を基に画像の描画を行う
	Vector2D graph_location = this->location + screen_offset;
	DrawRotaGraphF(graph_location.x, graph_location.y, 1.5, 0.0, image, TRUE, flip_flag);

	// 親クラスの描画処理
	//__super::Draw(screen_offset);
}

// 終了時処理（使ったインスタンスなどの削除）
void Player::Finalize()
{
	ResourceManager::DeleteInstance();
}

void Player::OnHitCollision(GameObjectBase* hit_object)
{
}

void Player::SetNextState(ePlayerState next_state)
{
	this->next_state = next_state;
}
