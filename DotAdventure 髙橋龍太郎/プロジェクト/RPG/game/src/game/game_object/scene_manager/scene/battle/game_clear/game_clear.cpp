#include "game_clear.h"

/*
 *  コンストラクタ
 */
CGameClearScene::
CGameClearScene(aqua::IGameObject* parent)
	: IScene(parent, "TitleScene")
{
}

void
CGameClearScene::
Initialize(void)
{
	m_pSound = (CSoundManager*)aqua::FindGameObject("SoundManager");
	m_pItem = (CItem*)aqua::FindGameObject("Item");

	m_pItem->DeleteObject();

	m_pSound->Play(SOUND_ID::GAMECLEAR);

	m_BackGroundSprite.Create("data\\タイトル\\無題.png");
	m_BackGroundSprite.position = aqua::CVector2::ZERO;

	m_GameClearSprite.Create("data\\タイトル\\gameclear.png");
	m_GameClearSprite.position = aqua::CVector2(200, 200);

	IGameObject::Initialize();
}

void
CGameClearScene::
Update(void)
{
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER))
	{
		m_pSound->Play(SOUND_ID::ENTER);
		m_pSound->Stop(SOUND_ID::GAMECLEAR);
		Change(SCENE_ID::TITLE);
	}

	IGameObject::Update();
}

void
CGameClearScene::
Draw(void)
{
	m_BackGroundSprite.Draw();
	m_GameClearSprite.Draw();

	IGameObject::Draw();
}

void
CGameClearScene::
Finalize(void)
{
	m_BackGroundSprite.Delete();
	m_GameClearSprite.Delete();

	IGameObject::Finalize();
}