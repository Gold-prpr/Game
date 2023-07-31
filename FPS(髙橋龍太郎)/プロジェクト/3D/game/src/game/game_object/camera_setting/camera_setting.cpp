#include "camera_setting.h"
using namespace aqua::controller;
using namespace aqua::keyboard;

CCameraSet::CCameraSet(IGameObject* parent)
	:IGameObject(parent, "CameraSetting")
{
}

void CCameraSet::Initialize(void)
{
	m_pChara = (CCharacter*)aqua::FindGameObject("Character");
	m_pGun = (CGun*)aqua::FindGameObject("Gun");
	m_pStage = (CStage*)aqua::FindGameObject("Stage");
	m_pGameMain = (CGameMainScene*)aqua::FindGameObject("GameMainScene");
	m_pData = (CData*)aqua::FindGameObject("Data");

	m_Near = 1.0f;
	m_Far = 100000.0f;

	m_Camera.SetCameraDepth(m_Near, m_Far);

	m_Position = aqua::CVector3(0.0f, 0.0f, 0.0f);

	m_UpDir = aqua::CVector3(0.0f, 1.0f, 0.0f);

	m_MouseSensi = 6.0f;

	m_MousePos = aqua::CVector2::ZERO;

	m_Diff = aqua::CVector3::ZERO;

	m_AngleH = 0.0f;
	m_AngleV = 0.0f;

	IGameObject::Initialize();
}

void CCameraSet::Update(void)
{
	m_Matrix = aqua::CMatrix::GetIdent();

	//�}�E�X�̈ړ���
	aqua::CPoint mouse_movement = aqua::mouse::GetCursorMovement();

	//�}�E�X�̈ړ��ʂ��A���O���ɑ����Ă���
	m_AngleH += (float)mouse_movement.x / m_MouseSensi;
	m_AngleV += (float)mouse_movement.y / m_MouseSensi;

	//�A���O���̑傫������
	if (m_AngleH >= 360.0f)
	{
		m_AngleH -= 360.0f;
	}
	else if (m_AngleH <= -360.0f)
	{
		m_AngleH += 360.0f;
	}
	if (m_AngleV >= 89.0f)
	{
		m_AngleV = 89.0f;
	}
	else if (m_AngleV <= -89.0f)
	{
		m_AngleV = -89.0f;
	}

	if (m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::MAIN ||
		m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::FREETIME)
	{
		//�J�[�\����^�񒆂ɌŒ�
		aqua::mouse::SetCursorPos(aqua::CPoint(aqua::GetWindowWidth() / 2, aqua::GetWindowHeight() / 2));
		
		//�}�E�X�̈ʒu���X�V
		m_MousePos = aqua::CVector2((float)aqua::mouse::GetCursorPos().x, (float)aqua::mouse::GetCursorPos().x);

		//�A���O�������Ƃɍs��쐬
		m_Matrix.RotationX(aqua::DegToRad(m_AngleV));
		m_Matrix.RotationY(aqua::DegToRad(m_AngleH));
	}

	//�x�N�g���ɉ�]�s���������
	aqua::CVector3 camVec(0.0f, 0.0f, 1.0f);
	camVec = camVec.Transform(m_Matrix);
	m_Diff = aqua::CVector3(-20.0f, 0.0f, 50.0f).Transform(m_Matrix);
	m_Position = m_pData->GetPos() + m_Diff;
	m_Target = m_Position + camVec;

	//�J�������Z�b�g
	m_Camera.SetCamera(m_Position, m_Target, m_UpDir);

	IGameObject::Update();
}

void CCameraSet::Draw(void)
{
	IGameObject::Draw();
}

aqua::CVector3 CCameraSet::GetPos(void)
{
	return m_Position - m_Diff;
}

aqua::CMatrix CCameraSet::GetMatrix(void)
{
	return m_Matrix;
}

void CCameraSet::ResetAngle(void)
{
	m_AngleH = 0.0f;
	m_AngleV = 0.0f;
}
