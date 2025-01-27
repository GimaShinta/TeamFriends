#include "Collision.h"

/// <summary>
/// �K�p�I�u�W�F�N�g���m�F���鏈��
/// </summary>
/// <param name="hit_object">����̃I�u�W�F�N�g�^�C�v</param>
/// <returns>�K�p����I�u�W�F�N�g�Ȃ�Atrue</returns>
bool BoxCollision::IsCheckHitTarget(eObjectType hit_object) const
{
    // �K�p����I�u�W�F�N�g�^�C�v�Ȃ�Atrue
    for (eObjectType type : hit_object_type)
    {
        if (type == hit_object)
        {
            return true;
        }
    }

    return false;
}

// ��`�̕ӂ̊֌W�ʒu�œ����蔻����`�F�b�N
bool IsCheckCollision(const BoxCollision& c1, const BoxCollision& c2)
{
    // ��`1�̍��ӂƋ�`2�̉E�ӂ̈ʒu�֌W
    bool is_left_less_right = false;
    if (c1.point[0].x <= c2.point[1].x)
    {
        is_left_less_right = true;
    }

    // ��`1�̉E�ӂƋ�`2�̍��ӂ̈ʒu�֌W
    bool is_right_greater_left = false;
    if (c1.point[1].x >= c2.point[0].x)
    {
        is_right_greater_left = true;
    }

    // ��`1�̏�ӂƋ�`2�̉��ӂ̈ʒu�֌W
    bool is_top_less_bottom = false;
    if (c1.point[0].y <= c2.point[1].y)
    {
        is_top_less_bottom = true;
    }

    // ��`1�̉��ӂƋ�`2�̏�ӂ̈ʒu�֌W
    bool is_bottom_greater_top = false;
    if (c1.point[1].y >= c2.point[0].y)
    {
        is_bottom_greater_top = true;
    }

    // �S�Ă̏��������Ă͂܂��Ă�����A�q�b�g
    if (is_left_less_right == true &&
        is_right_greater_left == true &&
        is_top_less_bottom == true &&
        is_bottom_greater_top == true)
    {
        return true;
    }

    // ������1�ł������Ă��Ȃ�������A�m�[�q�b�g
    return false;
}