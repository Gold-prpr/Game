#pragma once
#include "aqua.h"
#include "../../gun/gun.h"
#include "../../enemy_manager/enemy/enemy.h"

class CGun;
class IEnemy;

class IBullet
    : public aqua::IGameObject
{
public:
    IBullet(aqua::IGameObject* parent, const std::string& name);

    virtual ~IBullet(void) = default;

    virtual void Initialize(void);

    void    Update(void);

    void    Draw(void);

    void    Finalize(void);

    void    EnemyColl(void);

protected:
    aqua::CModel m_Bullet;//�e�e�̃��f��

    aqua::CVector3 m_Posotion;//�e�e��

    aqua::CVector3 m_Rotation;//�e�e�̉�]

    aqua::CVector3 m_BulletStart;//�����蔻�胉�C���̍ŏ�
    aqua::CVector3 m_BulletEnd;//�����蔻�胉�C���̍Ō�

    int m_DamegeNum;//�e�e�̃_���[�W��

    bool m_FireCheck;//�e�e�̔��˃`�F�b�N

    MV1_COLL_RESULT_POLY m_HitPolygon;//�����蔻��|���S���\����

    aqua::CModelColl m_BulletColl;//�e�e�̃R���W����

    CGun* m_pGun;
    IEnemy* m_pEnemy;
};
