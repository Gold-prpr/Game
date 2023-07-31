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

	aqua::CModel m_Enemy;//�G�̃��f��

	int m_EnemyHp;//�G��HP

protected:
	MV1_COLL_RESULT_POLY m_HitPolygon;//�����蔻��q���W�����\����

	aqua::CModelColl m_EnemyColl;//�G�̃R���W����

	aqua::CVector3 m_Vec;//�ړ��x�N�g��

	aqua::CVector3 m_Position;//�ʒu

	aqua::CVector3 m_Scale;//�X�P�[��

	aqua::CVector3 m_Rotation;//��]�l

	bool m_TurnFlag;//���E�t���O

	CStage* m_pStage;
	CGameMainScene* m_pGameMain;
};