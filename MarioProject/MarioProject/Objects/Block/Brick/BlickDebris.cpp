#include "BlickDebris.h"

#include "../../../Utility/ResourceManager.h"
#include "DxLib.h"

BlickDebris::BlickDebris() :
	g_velocity(0.0f)
	, kaiten(0.0f)
{
}

BlickDebris::~BlickDebris()
{
}

// ����������
void BlickDebris::Initialize()
{
	// ����t���O�̃I��
	is_mobility = true;

	//�摜�̐ݒ�
	ResourceManager* rm = Singleton<ResourceManager>::GetInstance();
	image = rm->GetImages("Resource/Images/Block/bloak_1.png")[0];

	//�����蔻��̐ݒ�
	collision.is_blocking = true;
	collision.object_type = eObjectType::eNone;

	velocity.y -= 100.0f;
}

/// <summary>
/// �X�V����
/// </summary>
/// <param name="delata_second">�P�t���[��������̎���</param>
void BlickDebris::Update(float delta_second)
{
	//�d�͑��x�̌v�Z
	g_velocity += D_GRAVITY;
	velocity.y += g_velocity * delta_second;

	kaiten += 0.1f;

	location += velocity * delta_second;
}
