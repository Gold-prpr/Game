
/*!
 *  @file       title_scene.cpp
 *  @brief      �^�C�g���V�[��
 *  @author     Kazuya Maruyama
 *  @date       2021/05/20
 *  @version    1.0
 *
 *  Copyright (c) 2013-2021, Kazuya Maruyama. All rights reserved.
 */

#include "Inventory.h"

 /*
  *  �R���X�g���N�^
  */
CInventory::
CInventory(aqua::IGameObject* parent)
	: IGameObject(parent, "Inventory")
	, m_BsFlag(false)
{
}

/*
 *  ������
 */
void
CInventory::
Initialize(void)
{
	m_pSound = (CSoundManager*)aqua::FindGameObject("SoundManager");
	m_pData = (CData*)aqua::FindGameObject("Data");

	m_InveBs.Create("data\\�퓬\\guree.png");
	m_InveBs.position = aqua::CVector2((aqua::GetWindowWidth() / 2.0f) - (m_InveBs.GetTextureWidth() / 2.0f),
		(aqua::GetWindowHeight() / 2.0f) - (m_InveBs.GetTextureHeight() / 2.0f));
	m_InveBs.color.alpha = 0x00;

	m_BsFlag = false;

	/*
	/   ���C���S�b�g
	*/
	m_GoldCount = 0;

	m_GoldLabel.Create(45);
	m_GoldLabel.text = "���C���S�b�g�F�@";
	m_GoldLabel.position = aqua::CVector2(m_InveBs.position.x + 50.0f,
		m_InveBs.position.y + 60.0f);

	m_GoldCountLabel.Create(45);
	m_GoldCountLabel.text = std::to_string(m_GoldCount);
	m_GoldCountLabel.position = aqua::CVector2(m_GoldLabel.position.x + m_GoldLabel.GetTextWidth(),
		m_InveBs.position.y + 60.0f);

	/*
	/  ��
	*/
	m_KeyCount = 0;

	m_KeyLabel.Create(45);
	m_KeyLabel.text = "���@�@�@�@�@�F�@";
	m_KeyLabel.position = aqua::CVector2(m_InveBs.position.x + 50.0f,
		m_GoldLabel.position.y + m_GoldLabel.GetFontHeight() + 80.0f);

	m_KeyCountLabel.Create(45);
	m_KeyCountLabel.text = std::to_string(m_KeyCount);
	m_KeyCountLabel.position = aqua::CVector2(m_KeyLabel.position.x + m_KeyLabel.GetTextWidth(),
		m_GoldLabel.position.y + m_GoldLabel.GetFontHeight() + 80.0f);

	/*
	/   �񕜖�
	*/
	m_HealPotionCount = 0;

	m_HealPosionLabel.Create(45);
	m_HealPosionLabel.text = "�񕜖�@�@�@�F�@";
	m_HealPosionLabel.position = aqua::CVector2(m_InveBs.position.x + 50.0f,
		m_KeyLabel.position.y + m_HealPosionLabel.GetFontHeight() + 80.0f);

	m_HealPosionCountLabel.Create(45);
	m_HealPosionCountLabel.text = std::to_string(m_HealPotionCount);
	m_HealPosionCountLabel.position = aqua::CVector2(m_HealPosionLabel.position.x + m_HealPosionLabel.GetTextWidth(),
		m_KeyLabel.position.y + m_HealPosionLabel.GetFontHeight() + 80.0f);

	IGameObject::Initialize();
}

/*
 *  �X�V
 */
void
CInventory::
Update(void)
{
	//�A�C�e���̐�����ɍŐV�̏�Ԃɂ���
	m_GoldCount = m_pData->GetGoldCount();
	m_GoldCountLabel.text = std::to_string(m_GoldCount);

	m_KeyCount = m_pData->GetKeyCount();
	m_KeyCountLabel.text = std::to_string(m_KeyCount);

	m_HealPotionCount = m_pData->GetHealPotionCount();
	m_HealPosionCountLabel.text = std::to_string(m_HealPotionCount);

	//�C���x���g���[���o�Ă��Ȃ��Ƃ��͓����ɂ���
	if (m_BsFlag == false)
	{
		m_InveBs.color.alpha = 0x00;
		m_GoldLabel.color.alpha = 0x00;
		m_GoldCountLabel.color.alpha = 0x00;
		m_KeyLabel.color.alpha = 0x00;
		m_KeyCountLabel.color.alpha = 0x00;
		m_HealPosionLabel.color.alpha = 0x00;
		m_HealPosionCountLabel.color.alpha = 0x00;
	}
	else
	{
		m_InveBs.color.alpha = 0xff;
		m_GoldLabel.color.alpha = 0xff;
		m_GoldCountLabel.color.alpha = 0xff;
		m_KeyLabel.color.alpha = 0xff;
		m_KeyCountLabel.color.alpha = 0xff;
		m_HealPosionLabel.color.alpha = 0xff;
		m_HealPosionCountLabel.color.alpha = 0xff;
	}

	//�t���b�O�ŃC���x���g���[��ʂ𔻒f����
	if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::E) && m_BsFlag == false)
	{
		m_pSound->Play(SOUND_ID::ENTER);

		m_BsFlag = true;
	}
	else if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::E) && m_BsFlag == true)
	{
		m_pSound->Play(SOUND_ID::ENTER);

		m_BsFlag = false;
	}

	IGameObject::Update();
}

/*
 *  �`��
 */
void
CInventory::
Draw(void)
{
	m_InveBs.Draw();

	m_GoldCountLabel.Draw();
	m_GoldLabel.Draw();

	m_KeyCountLabel.Draw();
	m_KeyLabel.Draw();

	m_HealPosionLabel.Draw();
	m_HealPosionCountLabel.Draw();

	IGameObject::Draw();
}

/*
 *  ���
 */
void
CInventory::
Finalize(void)
{
	m_InveBs.Delete();

	m_GoldCountLabel.Delete();
	m_GoldLabel.Delete();

	m_KeyCountLabel.Delete();
	m_KeyLabel.Delete();

	m_HealPosionLabel.Delete();
	m_HealPosionCountLabel.Delete();

	IGameObject::Finalize();
}

void CInventory::ResetNum(void)
{
	//�A�C�e���̌������Z�b�g
	m_pData->SetGoldCount(0);
	m_pData->SetKeyCount(0);
	m_pData->SetHealPotionCount(0);
}
