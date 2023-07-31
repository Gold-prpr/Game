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

	float m_AngleH;//横のアングル
	float m_AngleV;//縦のアングル

	aqua::CVector3 m_Position;//位置
	aqua::CVector3 m_Target;//ターゲット位置

	aqua::CMatrix m_Matrix;//回転用マトリックス
private:
	aqua::CCamera m_Camera;//カメラ

	aqua::CVector2 m_MousePos;//マウスの位置

	aqua::CVector2 m_CenterPos;//カーソルの位置

	int m_FrameIndex;//フレーム番号

	float m_MouseSensi;//マウスの感度

	aqua::CVector3 m_Diff;//誤差

	float m_Near;//カメラをどこまで移すか手前
	float m_Far;//カメラをどこまで移すか奥

	aqua::CVector3 m_UpDir;//上方向ベクトル

	CCharacter* m_pChara;
	CGun* m_pGun;
	CStage* m_pStage;
	CGameMainScene* m_pGameMain;
	CData* m_pData;
};