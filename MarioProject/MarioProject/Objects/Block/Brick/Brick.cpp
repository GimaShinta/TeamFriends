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

// ����������
void Brick::Initialize()
{
	// ����t���O�̃I��
	is_mobility = true;

	//�摜�̐ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Block/block.png", 1, 1, 1, 32, 32)[0];

	//�����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::eBlock;
	collision.hit_object_type.push_back(eObjectType::ePlayer);
	collision.hit_object_type.push_back(eObjectType::eEnemy);

	// �����蔻��T�C�Y�̐ݒ�
	box_size = D_OBJECT_SIZE;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delata_second">�P�t���[��������̎���</param>
void Brick::Update(float delata_second)
{
	// �j�󂳂�Ă�����
	if (is_destruction == true)
	{
		// �C���X�^���X�̎擾
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
/// �`�揈��
/// </summary>
/// <param name="screen_offset"></param>
void Brick::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
	// �����蔻��̉���
	DrawBox(this->location.x - this->box_size.x, this->location.y - this->box_size.y,
		this->location.x + this->box_size.x, this->location.y + this->box_size.y, GetColor(255, 0, 0), FALSE);
}

// �I���������i�g�����C���X�^���X�Ȃǂ̍폜�j
void Brick::Finalize()
{
	ResourceManager::DeleteInstance();
	GameObjectManager::DeleteInstance();
}

/// <summary>
/// �q�b�g������
/// </summary>
/// <param name="hit_object">������������</param>
void Brick::OnHitCollision(GameObjectBase* hit_object)
{
	// �����������肪�}���I�������炩�A�}���I�̐i�s�������ゾ������
	if (hit_object->GetCollision().object_type == eObjectType::ePlayer && hit_object->GetVelocity().y < -1.0f)
	{
		// �}���I�����~������
		hit_object->SetVelocity(Vector2D(hit_object->GetVelocity().x, 1.0f));

		// �j�󂳂�Ă��Ȃ�������
		if (is_destruction == false)
		{
			// �C���X�^���X�̎擾
			GameObjectManager* gm = Singleton<GameObjectManager>::GetInstance();
			// �R�C���̐���
			coin = gm->CreateObject<Coin>(location);
			// �j��t���O���I���ɂ���
			is_destruction = true;
		}
	}
}
