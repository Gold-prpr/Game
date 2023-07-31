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

	aqua::CModel m_Gun;//�e�̃��f��

	aqua::CModel m_DummyGun;//�G�C���p�e���f��

	aqua::CVector3 m_BulletVec;//�e�̈ړ��x�N�g��
	aqua::CVector3 m_BulletRot;//�e�̉�]�l

	int m_MagCap;//�}�K�W���e��
	
private:
	bool m_CanShoot;//�ˌ����f�t���O

	bool m_CheckAim;//�G�C�����f�t���O

	int m_FrameIndex;//�t���[���ԍ�

	int m_DummyFrameIndex;//�t���[���ԍ�

	int m_PrevAmmoNum;//�ЂƂO�̒e�ۗ�
	int m_PreAmmoNum;//�ЂƂ�̒e�ۗ�

	aqua::CTimer m_RateTimer;//�e�̃��[�g�^�C�}�[

	aqua::CMatrix m_FrameLocalWorldMatrix;//���[���h���W�Ԋ҃}�g���b�N�X

	aqua::CMatrix m_DummyFrameLocalWorldMatrix;//���[���h���W�Ԋ҃}�g���b�N�X

	CCharacter* m_pChara;
	CCameraSet* m_pCamera;
	CBulletManager* m_pBulletM;
	CStage* m_pStage;
	CGameMainScene* m_pGameMain;
	CData* m_pData;
};