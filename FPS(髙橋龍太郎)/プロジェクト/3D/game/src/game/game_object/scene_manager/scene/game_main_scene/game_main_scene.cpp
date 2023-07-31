
/*!
*  @file       game_main_scene.cpp
*  @brief      �Q�[�����C���V�[��
*  @author     Kazuya Maruyama
*  @date       2021/05/20
*  @version    1.0
*
*  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
*/

#include "game_main_scene.h"

/*
 *  �R���X�g���N�^
 */
CGameMainScene::
CGameMainScene(aqua::IGameObject* parent)
	: IScene(parent, "GameMainScene")
{
}

/*
 *  ������
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

	//�G�̐���
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
 *  �X�V
 */
void
CGameMainScene::
Update(void)
{
	//�����X�v���C�g�̈ʒu�w��p�ϐ�
	float posSpriteX = 320.0f;

	switch (m_GameState)
	{
	case CGameMainScene::GAME_STATE::FREETIME:
	{
		//�}�E�X�J�[�\����\��
		aqua::mouse::SetMouseFlag(false);

		//�G���S�ōĐ���
		if (m_pEnemyManager->m_pEnemy->CheckLife() == false)
		{
			m_pEnemyManager->m_pEnemy->DeleteObject();
			m_pEnemyManager->Create(ENEMY_ID::CAPSULE);
		}

		m_Click.text = "ENTER�ŃX�^�[�g";
		m_Click.position =
			aqua::CVector2((320.0f + m_Comment.GetTextureWidth()) - m_Click.GetTextWidth(),
				(float)(aqua::GetWindowHeight() - m_Click.GetFontHeight()));

		//���̏��
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
		//�}�E�X�J�[�\���\��
		aqua::mouse::SetMouseFlag(true);

		//�J�������ʂɃ��Z�b�g
		m_pCamera->ResetAngle();

		//�����X�v���C�g�ʒu�w��
		if (posSpriteX < m_Comment.position.x)
		{
			m_Comment.position.x -= 80.0f;
		}

		//���̏��
		if (posSpriteX == m_Comment.position.x)
		{
			m_Click.text = "�}�E�X�N���b�N�ŃX�^�[�g";
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
		//�}�E�X�J�[�\����\��
		aqua::mouse::SetMouseFlag(false);

		//�J�������ʂɃ��Z�b�g
		m_pCamera->ResetAngle();

		m_CountTimer.Update();

		//�^�C�}�[�I���㎟�̏��
		if (m_CountTimer.Finished())
		{
			m_GameState = GAME_STATE::MAIN;
			m_CountTimer.Reset();
		}

		break;
	}
	case CGameMainScene::GAME_STATE::MAIN:
	{
		//�}�E�X�J�[�\����\��
		aqua::mouse::SetMouseFlag(false);

		//�������Ԍ��炷
		m_GameTime.Update();

		//�G���S���ɍ폜�A�����A�X�R�A���Z
		if (m_pEnemyManager->m_pEnemy->CheckLife() == false)
		{
			m_pEnemyManager->m_pEnemy->DeleteObject();
			m_pScore->AddScore();
			m_pEnemyManager->Create(ENEMY_ID::CAPSULE);
		}

		//�^�C�}�[�I���㎟�̏��
		if (m_GameTime.Finished())
		{
			m_GameState = GAME_STATE::SCORE;
			m_GameTime.Reset();
		}

		break;
	}
	case CGameMainScene::GAME_STATE::SCORE:
	{
		//�}�E�X�J�[�\����\��
		aqua::mouse::SetMouseFlag(true);

		//�J�������ʂɃ��Z�b�g
		m_pCamera->ResetAngle();

		//�N���b�N�𐧌�
		m_WaitTimer.Update();

		if (!m_WaitTimer.Finished())
		{
			m_Click.text = std::to_string((int)(m_WaitTimer.GetLimit() - m_WaitTimer.GetTime())) + "�b��}�E�X�N���b�N�Ńt���[�t�B�[���h";
			m_Click.position =
				aqua::CVector2((320.0f + m_Comment.GetTextureWidth()) - m_Click.GetTextWidth(),
					(180.0f + m_Comment.GetTextureHeight()) - m_Click.GetFontHeight());
		}
		else if (m_WaitTimer.GetLimit() <= m_WaitTimer.GetTime())
		{
			m_Click.text = "�}�E�X�N���b�N�Ńt���[�t�B�[���h";
			m_Click.position =
				aqua::CVector2((320.0f + m_Comment.GetTextureWidth()) - m_Click.GetTextWidth(),
					(180.0f + m_Comment.GetTextureHeight()) - m_Click.GetFontHeight());


			//�}�E�X�N���b�N�Ŏ��̏��
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
