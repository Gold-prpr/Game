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

	aqua::CModel m_Chara;//キャラのモデル

	aqua::CVector3 m_Velocity;//移動ベクトル

	aqua::CVector3 m_FastPerCamPos;//カメラの位置

	int m_CharaHp;//キャラのHP 
private:
	float m_CharaSpeed;//キャラのスピード

	static const float m_jump_power;//ジャンプの大きさ

	bool m_LandingFlag;//地面接着フラグ

	int m_FrameIndex;//フレーム番号

	aqua::CMatrix m_Matrix;//回転用行列

	aqua::CModelColl m_CharaColl;//キャラのコリジョン

	aqua::CVector3 m_JumpPos;//ジャンプ後の位置

	aqua::CVector3 m_Pos;//ジャンプ後の位置

	CStage* m_pStage;
	CCameraSet* m_pCamSet;
	CGun* m_pGun;
	CGameMainScene* m_pGameMain;
	CData* m_pData;
};