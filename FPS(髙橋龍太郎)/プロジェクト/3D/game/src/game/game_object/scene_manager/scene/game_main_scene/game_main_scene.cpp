
/*!
*  @file       game_main_scene.cpp
*  @brief      ゲームメインシーン
*  @author     Kazuya Maruyama
*  @date       2021/05/20
*  @version    1.0
*
*  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
*/

#include "game_main_scene.h"

/*
 *  コンストラクタ
 */
CGameMainScene::
CGameMainScene(aqua::IGameObject* parent)
	: IScene(parent, "GameMainScene")
{
}

/*
 *  初期化
 */
void
CGameMainScene::
Initialize(void)
{
	aqua::CreateGameObject<CStage>(this);
	m_pEnemyManager = aqua::CreateGameObject<CEnemyManager>(this);
	aqua::CreateGameObject<CCharacter>(this);
	m_pCamera = aqua::CreateGameObject<CCameraSet>(this);
	aqua::CreateGameObject<CBulletManager>(this);
	m_pUi = aqua::CreateGameObject<CUi>(this);
	m_pScore = aqua::CreateGameObject<CScore>(this);

	//敵の生成
	m_pEnemyManager->Create(ENEMY_ID::CAPSULE);

	m_Comment.Create("data\\setumei.png");
	m_Comment.position = aqua::CVector2(3200.0f, 180.0f);
	//m_Comment.position = aqua::CVector2(320.0f, 180.0f);

	m_GameState = GAME_STATE::FREETIME;

	m_GameTime.Setup(180.0f);

	m_CountTimer.Setup(3.0f);

	m_WaitTimer.Setup(3.0f);

	m_Click.Create(40);
	m_Click.color = 0xff000000;

	IGameObject::Initialize();
}

/*
 *  更新
 */
void
CGameMainScene::
Update(void)
{
	//説明スプライトの位置指定用変数
	float posSpriteX = 320.0f;

	switch (m_GameState)
	{
	case CGameMainScene::GAME_STATE::FREETIME:
	{
		//マウスカーソル非表示
		aqua::mouse::SetMouseFlag(false);

		//敵死亡で再生成
		if (m_pEnemyManager->m_pEnemy->CheckLife() == false)
		{
			m_pEnemyManager->m_pEnemy->DeleteObject();
			m_pEnemyManager->Create(ENEMY_ID::CAPSULE);
		}

		m_Click.text = "ENTERでスタート";
		m_Click.position =
			aqua::CVector2((320.0f + m_Comment.GetTextureWidth()) - m_Click.GetTextWidth(),
				(float)(aqua::GetWindowHeight() - m_Click.GetFontHeight()));

		//次の状態
		if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::NUMPADENTER))
		{
			m_pEnemyManager->m_pEnemy->DeleteObject();
			m_pEnemyManager->Create(ENEMY_ID::CAPSULE);

			m_GameState = GAME_STATE::COMMENT;
		}

		break;
	}
	case CGameMainScene::GAME_STATE::COMMENT:
	{
		//マウスカーソル表示
		aqua::mouse::SetMouseFlag(true);

		//カメラ正面にリセット
		m_pCamera->ResetAngle();

		//説明スプライト位置指定
		if (posSpriteX < m_Comment.position.x)
		{
			m_Comment.position.x -= 80.0f;
		}

		//次の状態
		if (posSpriteX == m_Comment.position.x)
		{
			m_Click.text = "マウスクリックでスタート";
			m_Click.position =
				aqua::CVector2((m_Comment.position.x + m_Comment.GetTextureWidth()) - m_Click.GetTextWidth(),
					(m_Comment.position.y + m_Comment.GetTextureHeight()) - m_Click.GetFontHeight());

			if (aqua::mouse::Button(aqua::mouse::BUTTON_ID::LEFT))
			{
				m_GameState = GAME_STATE::COUNT;
				m_Comment.position = aqua::CVector2(3200.0f, 180.0f);
			}
		}

		break;
	}
	case CGameMainScene::GAME_STATE::COUNT:
	{
		//マウスカーソル非表示
		aqua::mouse::SetMouseFlag(false);

		//カメラ正面にリセット
		m_pCamera->ResetAngle();

		m_CountTimer.Update();

		//タイマー終了後次の状態
		if (m_CountTimer.Finished())
		{
			m_GameState = GAME_STATE::MAIN;
			m_CountTimer.Reset();
		}

		break;
	}
	case CGameMainScene::GAME_STATE::MAIN:
	{
		//マウスカーソル非表示
		aqua::mouse::SetMouseFlag(false);

		//制限時間減らす
		m_GameTime.Update();

		//敵死亡時に削除、生成、スコア加算
		if (m_pEnemyManager->m_pEnemy->CheckLife() == false)
		{
			m_pEnemyManager->m_pEnemy->DeleteObject();
			m_pScore->AddScore();
			m_pEnemyManager->Create(ENEMY_ID::CAPSULE);
		}

		//タイマー終了後次の状態
		if (m_GameTime.Finished())
		{
			m_GameState = GAME_STATE::SCORE;
			m_GameTime.Reset();
		}

		break;
	}
	case CGameMainScene::GAME_STATE::SCORE:
	{
		//マウスカーソル非表示
		aqua::mouse::SetMouseFlag(true);

		//カメラ正面にリセット
		m_pCamera->ResetAngle();

		//クリックを制限
		m_WaitTimer.Update();

		if (!m_WaitTimer.Finished())
		{
			m_Click.text = std::to_string((int)(m_WaitTimer.GetLimit() - m_WaitTimer.GetTime())) + "秒後マウスクリックでフリーフィールド";
			m_Click.position =
				aqua::CVector2((320.0f + m_Comment.GetTextureWidth()) - m_Click.GetTextWidth(),
					(180.0f + m_Comment.GetTextureHeight()) - m_Click.GetFontHeight());
		}
		else if (m_WaitTimer.GetLimit() <= m_WaitTimer.GetTime())
		{
			m_Click.text = "マウスクリックでフリーフィールド";
			m_Click.position =
				aqua::CVector2((320.0f + m_Comment.GetTextureWidth()) - m_Click.GetTextWidth(),
					(180.0f + m_Comment.GetTextureHeight()) - m_Click.GetFontHeight());


			//マウスクリックで次の状態
			if (aqua::mouse::Button(aqua::mouse::BUTTON_ID::LEFT))
			{
				m_GameState = GAME_STATE::FREETIME;
				m_WaitTimer.Reset();
				m_pScore->ResetScore();

				break;
			}
		}
	}
	default:
		break;
	}

	IGameObject::Update();
}

void CGameMainScene::Draw(void)
{
	IGameObject::Draw();
}

void CGameMainScene::Finalize(void)
{
	m_Comment.Delete();

	m_Click.Delete();

	IGameObject::Finalize();
}
