#pragma once

#include "Vector2D.h"
#include <vector>

// �I�u�W�F�N�g�̃^�C�v
enum eObjectType
{
    eNone,
    ePlayer,
    eFireball,
    eEnemy,
    eBlock,
    eItem,
    eGoal
};

//�����蔻��N���X
class BoxCollision
{
public:
    bool                        is_blocking;        // ���蔲���t���O
    eObjectType                    object_type;        // ���g�̃I�u�W�F�N�g�^�C�v
    std::vector<eObjectType>    hit_object_type;    // �K�p����I�u�W�F�N�g�^�C�v
    Vector2D point[2];                              // �I�u�W�F�N�g�̍���ƉE���̍��W�ێ�

public:
    BoxCollision() :
        is_blocking(false),
        object_type(eObjectType::eNone),
        hit_object_type()
    {
    }
    ~BoxCollision()
    {
        hit_object_type.clear();
    }

    // �����蔻��L���m�F����
    bool IsCheckHitTarget(eObjectType hit_object) const;
};

/// <summary>
/// �����蔻��m�F����
/// </summary>
/// <param name="c1">�`��̏��1</param>
/// <param name="c2">�`��̏��2</param>
/// <returns>�������Ă���Ȃ�Atrue</returns>
bool IsCheckCollision(const BoxCollision& c1, const BoxCollision& c2);