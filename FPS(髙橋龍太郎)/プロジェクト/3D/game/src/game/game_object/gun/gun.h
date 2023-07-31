#pragma once
#include "aqua.h"
#include "../character/character.h"
#include "../camera_setting/camera_setting.h"
#include "../bullet_manager/bullet_manager.h"
#include "../stage/stage.h"
#include "../scene_manager/scene/game_main_scene/game_main_scene.h"
#include "../data_keep/data.h"

class CCharacter;
class CCameraSet;
class CBulletManager;
class CStage;
class CGameMainScene;
class CData;

class CGun
	:public aqua::IGameObject
{
public:
	CGun(aqua::IGameObject* parent);
	~CGun() = default;

	void Initialize(void);

	void Update(void);

	void Draw(void);

	void Finalize(void);

	void Fire(void);

	void SetGunPos(void);

	void UpdateDummyGun(void);

	aqua::CModel m_Gun;//銃のモデル

	aqua::CModel m_DummyGun;//エイム用銃モデル

	aqua::CVector3 m_BulletVec;//弾の移動ベクトル
	aqua::CVector3 m_BulletRot;//弾の回転値

	int m_MagCap;//マガジン容量
	
private:
	bool m_CanShoot;//射撃判断フラグ

	bool m_CheckAim;//エイム判断フラグ

	int m_FrameIndex;//フレーム番号

	int m_DummyFrameIndex;//フレーム番号

	int m_PrevAmmoNum;//ひとつ前の弾丸量
	int m_PreAmmoNum;//ひとつ後の弾丸量

	aqua::CTimer m_RateTimer;//銃のレートタイマー

	aqua::CMatrix m_FrameLocalWorldMatrix;//ワールド座標返還マトリックス

	aqua::CMatrix m_DummyFrameLocalWorldMatrix;//ワールド座標返還マトリックス

	CCharacter* m_pChara;
	CCameraSet* m_pCamera;
	CBulletManager* m_pBulletM;
	CStage* m_pStage;
	CGameMainScene* m_pGameMain;
	CData* m_pData;
};