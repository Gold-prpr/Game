#include "ui.h"
#include <cmath>

CUi::CUi(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Ui")
{
}

void CUi::Initialize(void)
{
	m_pChara = (CCharacter*)aqua::FindGameObject("Character");
	m_pCamera = (CCameraSet*)aqua::FindGameObject("CameraSetting");
	m_pGun = (CGun*)aqua::FindGameObject("Gun");
	m_pGameMain = (CGameMainScene*)aqua::FindGameObject("GameMainScene");
	m_pScore = (CScore*)aqua::FindGameObject("Score");

	m_MaxMagLabel.Create(40);
	m_MaxMagLabel.text = "/30";
	m_MaxMagLabel.position = aqua::CVector2(aqua::GetWindowWidth() / 2.0f, (float)(aqua::GetWindowHeight() - m_MaxMagLabel.GetFontHeight()));

	m_MagNumLabel.Create(40);

	m_CountLabel.Create(40);
	m_CountLabel.position = aqua::CVector2(aqua::GetWindowWidth() / 2.0f, aqua::GetWindowHeight() / 2.0f);
	
	m_MinutesLabel.Create(40);
	m_SecondsLabel.Create(40);

	m_Score.Create(40);
	m_Score.text = "スコア";
	m_Score.position = aqua::CVector2(aqua::GetWindowWidth() / 2.0f, aqua::GetWindowHeight() / 2.0f);
	m_ScoreNum.Create(40);

	IGameObject::Initialize();
}

void CUi::Update(void)
{
	//マガジン容量更新
	m_MagNumLabel.text = std::to_string(m_pGun->m_MagCap);
	m_MagNumLabel.position = aqua::CVector2((aqua::GetWindowWidth() / 2.0f) - m_MagNumLabel.GetTextWidth(), m_MaxMagLabel.position.y);

	//カウント秒数更新
	m_CountLabel.text = 
		std::to_string((int)(m_pGameMain->m_CountTimer.GetLimit() - m_pGameMain->m_CountTimer.GetTime()));

	//制限時間更新
	float nowTime = m_pGameMain->m_GameTime.GetLimit() - m_pGameMain->m_GameTime.GetTime();

	m_MinutesLabel.text = std::to_string((int)nowTime / 60) + "：";
	m_SecondsLabel.text = std::to_string((int)nowTime % 60);

	if((int)nowTime % 60 < 10)
		m_SecondsLabel.text = "0" + std::to_string((int)nowTime % 60);

	m_MinutesLabel.position = aqua::CVector2((aqua::GetWindowWidth() / 2.0f) - m_MinutesLabel.GetTextWidth(), 0.0f);
	m_SecondsLabel.position = aqua::CVector2(m_MinutesLabel.position.x + m_MinutesLabel.GetTextWidth(), 0.0f);

	m_ScoreNum.text = std::to_string(m_pScore->GetScore());
	m_ScoreNum.position = aqua::CVector2(m_Score.position.x, m_Score.position.y + 100.0f);

	IGameObject::Update();
}

void CUi::Draw(void)
{
	if (m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::MAIN ||
		m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::FREETIME)
	{
		m_MaxMagLabel.Draw();
		m_MagNumLabel.Draw();
	}

	if (m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::COMMENT)
		m_pGameMain->m_Comment.Draw();

	if (m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::COUNT)
		m_CountLabel.Draw();

	if (m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::MAIN)
	{
		m_MinutesLabel.Draw();
		m_SecondsLabel.Draw();
	}

	if (m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::SCORE)
	{
		m_Score.Draw();
		m_ScoreNum.Draw();
	}

	if (m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::COMMENT ||
		m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::SCORE || 
		m_pGameMain->m_GameState == CGameMainScene::GAME_STATE::FREETIME)
	{
		m_pGameMain->m_Click.Draw();
	}

	IGameObject::Draw();
}

void CUi::Finalize(void)
{
	m_MaxMagLabel.Delete();
	m_MagNumLabel.Delete();

	m_CountLabel.Delete();

	m_MinutesLabel.Delete();
	m_SecondsLabel.Delete();

	m_Score.Delete();
	m_ScoreNum.Delete();

	IGameObject::Finalize();
}
