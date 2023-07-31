#include "stage.h"

const float CStage::m_gravity = -15.0f;

CStage::CStage(aqua::IGameObject* parent)
	:IGameObject(parent, "Stage")
{
}

void CStage::Initialize(void)
{
	//m_Stage.Load("data\\stage\\Stage.mv1");
	m_Stage.Load("data\\stage\\Stage1.mv1");
	m_Stage.position = aqua::CVector3(0.0f, 0.0f, 0.0f);
	m_Stage.scale = aqua::CVector3::ONE;
	
	m_StageObjMesh.Load("data\\Stage_Obj009_c.mv1");
	m_StageObjMesh.position = aqua::CVector3(0.0f, 80.0f, 50.0f);
	m_StageObjMesh.scale = aqua::CVector3::ONE;

	m_ModelCollStage.SetUpColl(m_Stage.GetResourceHandle(), -1, 2, 2, 2);
	m_ModelCollWall.SetUpColl(m_StageObjMesh.GetResourceHandle(), -1, 1, 1, 1);

	
	
	IGameObject::Initialize();
}

void CStage::Update(void)
{
	m_ModelCollWall.UpdateColl();

	IGameObject::Update();
}

void CStage::Draw(void)
{
	m_Stage.Draw();
	m_StageObjMesh.Draw();

	IGameObject::Draw();
}

void CStage::Finalize(void)
{
	m_Stage.Unload();
	m_StageObjMesh.Unload();

	IGameObject::Finalize();
}

bool CStage::CheckCollStage(const aqua::CVector3& start_pos, const aqua::CVector3& end_pos)
{
	m_HitPolygon = m_ModelCollStage.CollCheckLine(start_pos, end_pos);

	return m_HitPolygon.HitFlag;
}

bool CStage::CheckCollWall(const aqua::CVector3& start_pos, const aqua::CVector3& end_pos)
{
	m_HitPolygonWall = m_ModelCollWall.CollCheckLine(start_pos, end_pos);

	return m_HitPolygonWall.HitFlag;
}

bool CStage::CheckCollEnemy(const aqua::CVector3& start_pos, const aqua::CVector3& end_pos)
{
	m_HitPolygonEnemy = m_ModelCollWall.CollCheckLine(start_pos, end_pos);

	return m_HitPolygonEnemy.HitFlag;
}

aqua::CVector3 CStage::GetHitPositionStage(void)
{
	return aqua::CVector3(m_HitPolygon.HitPosition);
}

aqua::CVector3 CStage::GetHitPositionWall(void)
{
	return aqua::CVector3(m_HitPolygonWall.HitPosition);
}

aqua::CVector3 CStage::GetHitPositionEnemy(void)
{
	return aqua::CVector3(m_HitPolygonEnemy.HitPosition);
}

float CStage::GetGravity(void)
{
	return m_gravity;
}
