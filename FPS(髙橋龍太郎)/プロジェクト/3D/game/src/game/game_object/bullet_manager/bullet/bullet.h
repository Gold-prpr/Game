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
    aqua::CModel m_Bullet;//e’e‚Ìƒ‚ƒfƒ‹

    aqua::CVector3 m_Posotion;//e’e‚Ì

    aqua::CVector3 m_Rotation;//e’e‚Ì‰ñ“]

    aqua::CVector3 m_BulletStart;//“–‚½‚è”»’èƒ‰ƒCƒ“‚ÌÅ‰
    aqua::CVector3 m_BulletEnd;//“–‚½‚è”»’èƒ‰ƒCƒ“‚ÌÅŒã

    int m_DamegeNum;//e’e‚Ìƒ_ƒ[ƒW”

    bool m_FireCheck;//e’e‚Ì”­Ëƒ`ƒFƒbƒN

    MV1_COLL_RESULT_POLY m_HitPolygon;//“–‚½‚è”»’èƒ|ƒŠƒSƒ“\‘¢‘Ì

    aqua::CModelColl m_BulletColl;//e’e‚ÌƒRƒŠƒWƒ‡ƒ“

    CGun* m_pGun;
    IEnemy* m_pEnemy;
};
