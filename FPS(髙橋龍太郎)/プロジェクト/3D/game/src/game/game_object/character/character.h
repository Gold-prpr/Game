#pragma once
#include "aqua.h"
#include "../stage/stage.h"
#include "../camera_setting/camera_setting.h"
#include "../gun/gun.h"
#include "../scene_manager/scene/game_main_scene/game_main_scene.h"
#include "../data_keep/data.h"

class CStage;
class CCameraSet;
class CGun;
class CGameMainScene;
class CData;

class CCharacter
	:public aqua::IGameObject
{
public:
	CCharacter(aqua::IGameObject* parent);
	~CCharacter() = default;

	void Initialize(void) override;

	void Update(void) override;

	void Draw(void) override;

	void Finalize(void) override;

	void MoveChara(void);

	void WallCheck(void);

	void LoadAnimation(void);

	aqua::CModel m_Chara;//�L�����̃��f��

	aqua::CVector3 m_Velocity;//�ړ��x�N�g��

	aqua::CVector3 m_FastPerCamPos;//�J�����̈ʒu

	int m_CharaHp;//�L������HP 
private:
	float m_CharaSpeed;//�L�����̃X�s�[�h

	static const float m_jump_power;//�W�����v�̑傫��

	bool m_LandingFlag;//�n�ʐڒ��t���O

	int m_FrameIndex;//�t���[���ԍ�

	aqua::CMatrix m_Matrix;//��]�p�s��

	aqua::CModelColl m_CharaColl;//�L�����̃R���W����

	aqua::CVector3 m_JumpPos;//�W�����v��̈ʒu

	aqua::CVector3 m_Pos;//�W�����v��̈ʒu

	CStage* m_pStage;
	CCameraSet* m_pCamSet;
	CGun* m_pGun;
	CGameMainScene* m_pGameMain;
	CData* m_pData;
};