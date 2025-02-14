#include "Brick.h"
#include "DxLib.h"

#include "../../../Utility/ResourceManager.h"
#include "../../../Objects/GameObjectManager.h"
#include "../../../Objects/Item/Coin/Coin.h"

Brick::Brick() :
	is_destruction(false)
	, block_sound(NULL)
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

	block_sound = rm->GetSounds("Resource/Sounds/SE_Block.wav");

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
void Brick::Update(float delta_second)
{
	// ��}�X��ɓ��B������ړ����]
	if (location.y < old_location.y - D_OBJECT_SIZE)
	{
		velocity.y *= -1;
	}

	// �����ʒu�ɖ߂�
	if (location.y > old_location.y)
	{
		location.y = old_location.y;
		velocity = 0;
	}

	// ��ʊO�ō폜
	__super::Update(delta_second);

	// �ړ�����
	location += velocity * delta_second;
}

/// <summary>
/// �`�揈��
/// </summary>
/// <param name="screen_offset"></param>
void Brick::Draw(const Vector2D& screen_offset) const
{
	// �e�N���X�̕`�揈��
	__super::Draw(screen_offset);
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

		// �j�󂳂�Ă�����
		if (is_destruction == false)
		{
			PlaySoundMem(block_sound, DX_PLAYTYPE_BACK);
			// ��ɏ㏸������
			velocity.y -= 500;
		}
	}
}
