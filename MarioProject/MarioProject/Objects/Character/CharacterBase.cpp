#include "CharacterBase.h"

#include "../../Scene/SceneType/InGameScene.h"

#include <cmath>

CharacterBase::CharacterBase():
	g_velocity(0.0f)
	, scroll_value(0.0f)
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
/// スクロール量の設定
/// </summary>
/// <param name="scroll">スクロール量</param>
void CharacterBase::SetScrollValue(float& scroll)
{
	this->scroll_value = scroll;
}

/// <summary>
/// ステージの情報を設定
/// </summary>
/// <param name="map">インゲームで作ったステージ情報を参照で受け取る</param>
void CharacterBase::SetMapData( const std::vector<std::vector<char>>& map)
{
	this->map_data = map;
}

// マップとの当たり判定
bool CharacterBase::MapCollision(int x, int y)
{
	// ワールド座標を保存
	Vector2D object_rect = Vector2D (this->location.x + scroll_value, this->location.y);
	// サイズを保存
	Vector2D object_box = this->GetBoxSize();
	// 四つの頂点を保存
	Vector2D vertices[4] =
	{
		// 左上の座標
		Vector2D(object_rect - object_box),
		// 左下の座標
		Vector2D(object_rect.x - object_box.x, object_rect.y + object_box.y),
		// 右上の座標
		Vector2D(object_rect.x + object_box.x, object_rect.y - object_box.y),
		// 右下の座標
		Vector2D(object_rect + object_box),
	};

	for (int i = 0; i < 4; i++)
	{
		// プレイヤーの現在のマスの位置
		int x_id = std::floor(vertices[i].x) / (D_OBJECT_SIZE * 2);
		int y_id = std::floor(vertices[i].y) / (D_OBJECT_SIZE * 2);
		// 当たり判定を付ける背景
		if (map_data[y_id + y][x_id + x] == '2' || map_data[y_id + y][x_id + x] == 'j' || map_data[y_id + y][x_id + x] == 'k'
			|| map_data[y_id + y][x_id + x] == 'l' || map_data[y_id + y][x_id + x] == 'm' || map_data[y_id + y][x_id + x] == 'n'
			|| map_data[y_id + y][x_id + x] == 'H'|| map_data[y_id + y][x_id + x] == 'B'|| map_data[y_id + y][x_id + x] == 'O')
		{
			// どのポイントが当たっているか
			int id = i;
			// 当たっている
			return true;
		}
	}
	// 当たっていない
	return false;
}
