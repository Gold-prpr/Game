#pragma once
#include "aqua.h"
#include <DxLib.h>
#include "../character/character.h"
#include "../gun/gun.h"
#include "../stage/stage.h"
#include "../scene_manager/scene/game_main_scene/game_main_scene.h"
#include "../data_keep/data.h"

class CCharacter;
class CGun;
class CStage;
class CGameMainScene;
class CData;

class CCameraSet
	:public aqua::IGameObject
{
public:
	CCameraSet(IGameObject* parent);
	~CCameraSet() = default;

	void Initialize(void) override;

	void Update(void) override;

	void Draw(void) override;

	aqua::CVector3 GetPos(void);

	aqua::CMatrix GetMatrix(void);

	void ResetAngle(void);

	float m_AngleH;//���̃A���O��
	float m_AngleV;//�c�̃A���O��

	aqua::CVector3 m_Position;//�ʒu
	aqua::CVector3 m_Target;//�^�[�Q�b�g�ʒu

	aqua::CMatrix m_Matrix;//��]�p�}�g���b�N�X
private:
	aqua::CCamera m_Camera;//�J����

	aqua::CVector2 m_MousePos;//�}�E�X�̈ʒu

	aqua::CVector2 m_CenterPos;//�J�[�\���̈ʒu

	int m_FrameIndex;//�t���[���ԍ�

	float m_MouseSensi;//�}�E�X�̊��x

	aqua::CVector3 m_Diff;//�덷

	float m_Near;//�J�������ǂ��܂ňڂ�����O
	float m_Far;//�J�������ǂ��܂ňڂ�����

	aqua::CVector3 m_UpDir;//������x�N�g��

	CCharacter* m_pChara;
	CGun* m_pGun;
	CStage* m_pStage;
	CGameMainScene* m_pGameMain;
	CData* m_pData;
};