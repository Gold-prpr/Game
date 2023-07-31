#pragma once
#include "aqua.h"
#include "../../character/character.h"
#include "../../camera_setting/camera_setting.h"
#include "../../bullet_manager/bullet_manager.h"
#include "../../stage/stage.h"
#include "../../scene_manager/scene/game_main_scene/game_main_scene.h"

class CStage;
class CGameMainScene;

class IEnemy
	:public aqua::IGameObject
{
public:
	IEnemy(aqua::IGameObject* parent, const std::string& name);
	~IEnemy() = default;

	virtual void Initialize(void);

	virtual void Update(void);

	void Draw(void);

	void Finalize(void);

	bool CheckCollEnemy(const aqua::CVector3& start_pos, const aqua::CVector3& end_pos);

	aqua::CVector3 GetHitPos(void);

	bool    CheckLife(void);

	aqua::CModel m_Enemy;//敵のモデル

	int m_EnemyHp;//敵のHP

protected:
	MV1_COLL_RESULT_POLY m_HitPolygon;//当たり判定子リジョン構造体

	aqua::CModelColl m_EnemyColl;//敵のコリジョン

	aqua::CVector3 m_Vec;//移動ベクトル

	aqua::CVector3 m_Position;//位置

	aqua::CVector3 m_Scale;//スケール

	aqua::CVector3 m_Rotation;//回転値

	bool m_TurnFlag;//左右フラグ

	CStage* m_pStage;
	CGameMainScene* m_pGameMain;
};