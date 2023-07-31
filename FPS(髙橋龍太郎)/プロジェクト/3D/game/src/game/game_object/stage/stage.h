#pragma once
#include "aqua.h"
#include <DxLib.h>

class CStage
	:public aqua::IGameObject
{
public:
	CStage(aqua::IGameObject* parent);
	~CStage() = default;

	void Initialize(void) override;

	void Update(void) override;

	void Draw(void) override;

	void Finalize(void) override;

	bool CheckCollStage(const aqua::CVector3& start_pos, const aqua::CVector3& end_pos);

	bool CheckCollWall(const aqua::CVector3& start_pos, const aqua::CVector3& end_pos);

	bool CheckCollEnemy(const aqua::CVector3& start_pos, const aqua::CVector3& end_pos);

	aqua::CVector3 GetHitPositionStage(void);
	
	aqua::CVector3 GetHitPositionWall(void);

	aqua::CVector3 GetHitPositionEnemy(void);

	float GetGravity(void);

	aqua::CModel m_Stage;

	aqua::CModel m_StageObj;
	aqua::CModel m_StageObjMesh;

	MV1_COLL_RESULT_POLY m_HitPolygon;
	MV1_COLL_RESULT_POLY m_HitPolygonWall;
	MV1_COLL_RESULT_POLY m_HitPolygonEnemy;

private:
	aqua::CModelColl m_ModelCollStage;
	aqua::CModelColl m_ModelCollWall;

	static const float m_gravity;
};