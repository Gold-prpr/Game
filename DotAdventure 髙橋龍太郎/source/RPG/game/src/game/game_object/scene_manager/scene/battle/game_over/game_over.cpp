#include "game_over.h"

CGameOverScene::
CGameOverScene(aqua::IGameObject* parent)
	: IScene(parent, "TitleScene")
{
}

void
CGameOverScene::
Initialize(void)
{
	m_pSound = (CSoundManager*)aqua::FindGameObject("SoundManager");
	m_pData = (CData*)aqua::FindGameObject("Data");
	
	m_pSound->Play(SOUND_ID::LOSEBGM);

	m_BackGroundSprite.Create("data\\タイトル\\無題.png");
	m_BackGroundSprite.position = aqua::CVector2::ZERO;

	m_GameOverSprite.Create("data\\タイトル\\gameover.png");
	m_GameOverSprite.position = aqua::CVector2(200, 200);

	IGameObject::Initialize();
}

void
CGameOverScene::
Update(void)
{
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER))
	{
		m_pSound->Play(SOUND_ID::ENTER);
		Change(SCENE_ID::TITLE);
		m_pSound->Stop(SOUND_ID::LOSEBGM);
	}

	IGameObject::Update();
}

void
CGameOverScene::
Draw(void)
{
	m_BackGroundSprite.Draw();
	m_GameOverSprite.Draw();

	IGameObject::Draw();
}

void
CGameOverScene::
Finalize(void)
{
	m_BackGroundSprite.Delete();
	m_GameOverSprite.Delete();

	IGameObject::Finalize();
}