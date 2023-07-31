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

	aqua::CLabel m_MagNumLabel;//�c�e�\���X�v���C�g
	aqua::CLabel m_MaxMagLabel;//�c�e�\���X�v���C�g

	aqua::CLabel m_CountLabel;//�J�E���g�X�v���C�g

	aqua::CLabel m_SecondsLabel;//�b���X�v���C�g
	aqua::CLabel m_MinutesLabel;//�����X�v���C�g

	aqua::CLabel m_Score;//�X�R�A�l�[���X�v���C�g
	aqua::CLabel m_ScoreNum;//�X�R�A�\���X�v���C�g

private:
	CCharacter* m_pChara;
	CCameraSet* m_pCamera;
	CBulletManager* m_pBulletM;
	CGun* m_pGun;
	CGameMainScene* m_pGameMain;
	CScore* m_pScore;

};