#include "Player.h"
#include "DxLib.h"

// シングルトン継承クラスのインクルード
#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"
#include "StateBase/State/PlayerStateFactory.h"
#include"../../../Application/Application.h"

#define P_MAX_SPEED 500.0f

Player::Player():
	  flip_flag(false)
	, now_state(ePlayerState::IDLE)
	, next_state(ePlayerState::NONE)
	,stage_end(FALSE)
	, isOnGround(false) //初期値(地面)
	, is_goal(false)
	, is_clear(false)
	, sound_bgm(NULL)
	, sound_clear(NULL)
	, sound_destroy(NULL)
	, sound_tach(NULL)
	, coin(0)
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
	mario_aniamtion = rm->GetImages("Resource/Images/Mario/mario.png", 9, 9, 1, 32, 32);
	// 分割した画像の先頭を代入
	image = mario_aniamtion[0];

	//BGMの読み込み
	sound_bgm = LoadSoundMem("Resource/Sounds/BGM/Nonomura.wav");
	sound_clear = rm->GetSounds("Resource/Sounds/SE_Goal.wav");
	sound_tach = rm->GetSounds("Resource/Sounds/SE_PoleTouch.wav");
	//BGM再生
	PlaySoundMem(sound_bgm, DX_PLAYTYPE_LOOP);

	// 当たり判定のオブジェクト設定
	collision.is_blocking = true;
	// 自分のオブジェクトタイプ
	collision.object_type = eObjectType::ePlayer;
	// 当たる相手のオブジェクトタイプ
	collision.hit_object_type.push_back(eObjectType::eEnemy);
	collision.hit_object_type.push_back(eObjectType::eBlock);

	// 動くかどうか（trueなら動く、falseなら止まる）
	is_mobility = true;

	// プレイヤーの当たり判定サイズの設定
	box_size = D_OBJECT_SIZE;

	z_layer = 2;
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delata_second">１フレーム当たりの時間</param>
void Player::Update(float delta_second)
{
	// 値を初期化
	score = 0;
	coin = 0;

	// アニメーション
	AnimationControl(delta_second, mario_aniamtion, mario_animation_num, 5, NULL, 6);

	//プレーヤーの行動制御を行う
	PlayerControl(delta_second);

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

	// ゴールしたら
	if (is_goal == true)
	{
		if (CheckSoundMem(sound_bgm) == true)
		{
			StopSoundMem(sound_bgm);
			PlaySoundMem(sound_tach, DX_PLAYTYPE_BACK);
		}

		// 操作不可状態にする
		is_mobility = false;
		velocity.x = 0;
		// 地面に当たったら自動で進む
		if (isOnGround == true)
		{
			if (CheckSoundMem(sound_tach) == true)
			{
				StopSoundMem(sound_tach);
				PlaySoundMem(sound_clear, DX_PLAYTYPE_BACK);
			}
			velocity.x += 100;
		}
		// お城の中に消える
		if (location.x > ((D_OBJECT_SIZE * 2) * 13) + D_OBJECT_SIZE)
		{
			image = NULL;
			is_clear = true;
		}
	}

	// 移動を実行する関数の呼び出し
	__super::Movement(delta_second);

	// 親クラスの更新処理
	__super::Update(delta_second);
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
}

// 終了時処理（使ったインスタンスなどの削除）
void Player::Finalize()
{
	ResourceManager::DeleteInstance();
	PlayerStateFactory::DeleteInstance();
	GameObjectManager::DeleteInstance();
	StopSoundMem(sound_bgm);
}

/// <summary>
/// ヒット判定処理
/// </summary>
/// <param name="hit_object"></param>
void Player::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たった相手がゴールだったら
	if (hit_object->GetCollision().object_type == eObjectType::eGoal)
	{
		is_goal = true;
	}

	// 敵に触れたら
	if (hit_object->GetCollision().object_type == eObjectType::eEnemy)
	{
		velocity.y = 0;
		// スコアの値を設定
		score = 300;
	}

	// アイテムに触れたら
	if (hit_object->GetCollision().object_type == eObjectType::eItem)
	{
		// コインカウント加算
		coin++;
	}
}

/// <summary>
/// アニメーションの制御
/// </summary>
/// <param name="delta_second">1フレーム当たりの時間</param>
/// <param name="animation_image">アニメーション総画像</param>
/// <param name="animation_num">アニメーション順序</param>
/// <param name="n_jump">ジャンプ画像の位置</param>
/// <param name="n_squat">しゃがみ画像の位置</param>
void Player::AnimationControl(float delta_second, std::vector<int>& animation_image, std::vector<int>& animation_num, int n_jump, int n_squat, int n_destroy)
{
	switch (now_state)
	{
	case ePlayerState::RUN:
		// アニメーション総画像とアニメーション順序を引数とする
		GameObjectBase::AnimationControl(delta_second, animation_image, animation_num, 16.0f);
		break;
	case ePlayerState::IDLE:
		// 停止している画像を代入
		image = animation_image[0];
		break;
	case ePlayerState::JUMP:
		// n_jump番目にあるジャンプ画像を代入
		image = animation_image[n_jump];
		break;
	case ePlayerState::SQUAT:
		// n_squat番目にあるしゃがみ画像を代入
		image = animation_image[n_squat];
		break;
	case ePlayerState::DESTROY:
		image = animation_image[n_destroy];
		break;
	case ePlayerState::NONE:
		break;
	}
}

/// <summary>
/// ステートの設定
/// </summary>
/// <param name="next_state"></param>
void Player::SetNextState(ePlayerState next_state)
{
	this->next_state = next_state;
}

/// <summary>
/// プレイヤーの制御処理
/// </summary>
void Player::PlayerControl(float delta_second)
{
	//// 歩いているとき
	//if (now_state == ePlayerState::RUN)
	//{
	//	// 当たっている場所が壁だったら
	//	if (__super::MapCollision(0, -1) == true)
	//	{
	//		// 前座標を保存
	//		old_location = location;

	//		// 変換用変数に保存
	//		float x_map = location.x;

	//		// チップサイズで割って現在のマップ位置を特定
	//		x_map /= (D_OBJECT_SIZE * 2);

	//		// 切り上げ整数に変換
	//		int x_id = std::floor(x_map);

	//		// ワールド座標を保存
	//		Vector2D object_rect = Vector2D(location.x + scroll_value, location.y);

	//		float scroll = scroll_value;

	//		// 右に歩いているとき
	//		if (velocity.x > 1.0f)
	//		{
	//			// マップサイズをかけて座標を特定
	//			x_id *= (D_OBJECT_SIZE * 2);

	//			// 座標を設定
	//			location.x = x_id;
	//		}
	//		// 左に歩いているとき
	//		else if (velocity.x < -1.0f)
	//		{
	//			// マップ位置を右にずらす
	//			x_id++;

	//			// マップサイズをかけて座標を特定
	//			x_id *= (D_OBJECT_SIZE * 2);

	//			// 座標を設定
	//			location.x = x_id;
	//		}
	//		else
	//		{
	//			// 座標を設定
	//			location.x = x_id;
	//		}
	//	}
	//}

	//最大速度の設定
	if (velocity.x >= P_MAX_SPEED)
	{
		velocity.x = P_MAX_SPEED;
	}
	else if (velocity.x <= -P_MAX_SPEED)
	{
		velocity.x = -P_MAX_SPEED;
	}

	// 当たっている場所が地面だったらその座標に設定
	if (__super::MapCollision(0, 0) == true)
	{
		// 変換用変数に保存
		float y_map = location.y;

		// チップサイズで割って現在のマップ位置を特定
		y_map /= (D_OBJECT_SIZE * 2);

		// 切り上げ整数に変換
		int y_id = std::ceil(y_map);

		// マップサイズをかけて座標を特定
		y_id *= (D_OBJECT_SIZE * 2);

		// 座標を設定
		location.y = y_id - D_OBJECT_SIZE;
		velocity.y = 0.0f;
		g_velocity = 0.0f;
		isOnGround = true; // 地面にいる
	}
	else
	{
		isOnGround = false; // 空中にいる
	}

	//画面外に行かないようにする
	if (location.x < 0 + D_OBJECT_SIZE)
	{ //←
		location.x = 0 + D_OBJECT_SIZE;
	}

	//画面外に行かないようにする
	if (location.y < 0 + D_OBJECT_SIZE)
	{ //←
		velocity.y = -1;
	}

	//スクロール処理
	if (stage_end == FALSE)
	{
		//Player->真ん中に着いたら
		if (location.x >= D_WIN_MAX_X / 2)
		{
			location.x = D_WIN_MAX_X / 2;
		}
	}
	else
	{
		//ステージの端に着いたら
		if (location.x > D_WIN_MAX_X - D_OBJECT_SIZE * 1.2)
		{ //→
			location.x = D_WIN_MAX_X - D_OBJECT_SIZE * 1.2;
		}
	}
}

// 地面にいるかどうかを確認する
bool Player::IsOnGround() const
{
	return isOnGround;
}

// 死んでいるか
bool Player::GetIsDestroy()
{
	return is_destroy;
}

// clearしているか
bool Player::GetIsClear()
{
	return is_clear;
}

// 獲得コイン数の取得
int Player::GetCoin()
{
	return coin;
}
