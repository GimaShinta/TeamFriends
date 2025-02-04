#include "CharacterBase.h"

#include "../../Scene/SceneType/InGameScene.h"

#include <cmath>

CharacterBase::CharacterBase():
	g_velocity(0.0f)
{
}

CharacterBase::~CharacterBase()
{
}

// 初期化処理
void CharacterBase::Initialize()
{
}

/// <summary>
/// 更新処理
/// </summary>
/// <param name="delata_second">1フレーム当たりの時間</param>
void CharacterBase::Update(float delata_second)
{
	// 親クラスの更新処理を呼び出す
	__super::Update(delata_second);
}

/// <summary>
/// 描画処理
/// </summary>
/// <param name="screen_offset"></param>
void CharacterBase::Draw(const Vector2D& screen_offset) const
{
	// 親クラスの描画処理を呼び出す
	__super::Draw(screen_offset);
}

// 終了時処理
void CharacterBase::Finalize()
{
}

/// <summary>
/// ヒット時処理
/// </summary>
/// <param name="hit_object">当たった相手</param>
void CharacterBase::OnHitCollision(GameObjectBase* hit_object)
{
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">１フレーム当たりの時間</param>
void CharacterBase::Movement(float delta_second)
{
	location += velocity * delta_second;
}

/// <summary>
/// スクロールに合わせて加速させる
/// </summary>
/// <param name="velocity">thisオブジェクトの速度</param>
void CharacterBase::SetVelocity(const Vector2D& velocity)
{
	this->velocity = velocity;
}

/// <summary>
/// ステージの情報を設定
/// </summary>
/// <param name="map">インゲームで作ったステージ情報を参照で受け取る</param>
void CharacterBase::SetMapData( const std::vector<std::vector<char>>& map)
{
	map_data = map;
}

// マップとの当たり判定
bool CharacterBase::MapCollision()
{
	//int x_id = std::floor(this->location.x) / (D_OBJECT_SIZE * 2);
	//int y_id = std::floor(this->location.y) / (D_OBJECT_SIZE * 2);

	//for (int i = 0; i < 2; i++)
	//{
	//	for (int j = 0; j < 2; j++)
	//	{
	//		if (y_id + i >= 0 && y_id + i < map_data.size() &&
	//			x_id + j >= 0 && x_id + j < map_data[0].size() &&
	//			map_data[y_id + j][x_id + j] != '0')
	//		{
	//			return true;
	//		}
	//	}
	//}
	//return false;

	// プレイヤーの現在地を保存
	Vector2D p_rect = this->GetLocation();
	// プレイヤーのサイズを保存
	Vector2D p_box = this->GetBoxSize();
	// プレイヤーの四つの頂点を保存
	Vector2D vertices[4] =
	{
		// 左上の座標
		Vector2D(p_rect - p_box),
		// 左下の座標
		Vector2D(p_rect.x - p_box.x, p_rect.y + p_box.y),
		// 右上の座標
		Vector2D(p_rect.x + p_box.x, p_rect.y - p_box.y),
		// 右下の座標
		Vector2D(p_rect + p_box),
	};

	for (int i = 0; i < 4; i++)
	{
		// プレイヤーの現在のマスの位置
		int x_id = vertices[i].x / (D_OBJECT_SIZE * 2);
		int y_id = vertices[i].y / (D_OBJECT_SIZE * 2);
		// プレイヤーがいるマスが0以外の文字だったら
		if (map_data[y_id][x_id] != '0')
		{
			// 当たっている
			return true;
		}
	}
	// 当たっていない
	return false;
}
