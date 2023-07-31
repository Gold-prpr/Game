#pragma once
#include "aqua.h"
#include "../character/character.h"
#include "../camera_setting/camera_setting.h"
#include "../bullet_manager/bullet_manager.h"
#include "../gun/gun.h"
#include "../score/score.h"
#include "../scene_manager/scene/game_main_scene/game_main_scene.h"

class CCharacter;
class CCameraSet;
class CBulletManager;
class CGun;
class CGameMainScene;
class CScore;

class CUi
	:public aqua::IGameObject
{
public:
	CUi(aqua::IGameObject* parent);
	~CUi() = default;

	void Initialize(void);

	void Update(void);

	void Draw(void);

	void Finalize(void);

	aqua::CLabel m_MagNumLabel;//残弾表示スプライト
	aqua::CLabel m_MaxMagLabel;//残弾表示スプライト

	aqua::CLabel m_CountLabel;//カウントスプライト

	aqua::CLabel m_SecondsLabel;//秒数スプライト
	aqua::CLabel m_MinutesLabel;//分数スプライト

	aqua::CLabel m_Score;//スコアネームスプライト
	aqua::CLabel m_ScoreNum;//スコア表示スプライト

private:
	CCharacter* m_pChara;
	CCameraSet* m_pCamera;
	CBulletManager* m_pBulletM;
	CGun* m_pGun;
	CGameMainScene* m_pGameMain;
	CScore* m_pScore;

};