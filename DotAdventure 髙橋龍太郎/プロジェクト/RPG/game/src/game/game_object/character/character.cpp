#include "character.h"

const int CCharacter::m_character_width = 80;
const int CCharacter::m_character_height = 80;

const int CCharacter::m_chara_timer = 20;

enum class CHARA_STATE
{
	WAIT,	//�ҋ@
	MOVE,	//�ړ�
	ENCOUNT_CHECK //�G���J�E���g�̃`�F�b�N
};

CHARA_STATE	m_CharaState = CHARA_STATE::WAIT;

CCharacter::CCharacter(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Character")
	, m_Life(0)
	, m_BossFlag(false)
	, m_KeyCount(0)
	, m_HealPotion(0)
	, m_GoldCount(0)
	, m_CharaMoveTimer(0)
	,m_ScrollCamera(0,0)
{
}

void CCharacter::Initialize(void)
{
	m_pSound = (CSoundManager*)aqua::FindGameObject("SoundManager");
	m_pData = (CData*)aqua::FindGameObject("Data");
	m_pStage = (CStage*)aqua::FindGameObject("Map");
	m_pItem = (CItem*)aqua::FindGameObject("Item");
	m_pInve = (CInventory*)aqua::FindGameObject("Inventory");
	m_pScroll = (CScroll*)aqua::FindGameObject("Scroll");

	m_CharaStatus = { 50,148,10,130,105,102 };

	m_pData->SetHp(m_CharaStatus.hp);
	m_pData->SetMp(m_CharaStatus.mp);
	m_pData->SetCharaLv(m_CharaStatus.level);
	m_pData->SetCharaSpeed(m_CharaStatus.speed);
	m_pData->SetCharaStren(m_CharaStatus.strength);
	m_pData->SetCharaDefen(m_CharaStatus.defense);

	m_CharaMoveSpeed = (int)((float)m_pStage->m_map_chip_size / (float)m_chara_timer);

	m_Chara.Create("data\\���j�b�g\\�L����.ass", "down");

	//�L�����N�^�[�̈ʒu
	m_CharaPos = aqua::CVector2(80.0f, 80.0f);
	//m_CharaPos = aqua::CVector2(3360.0f, 1680.0f);

	m_CharaSpeed = aqua::CVector2(0.0f, 0.0f);

	//�L�����N�^�[�͉�����
	m_DirCurrent = CHARA_DIRECTION::DOWN;
	m_DirNext = CHARA_DIRECTION::DOWN;

	m_pInve->Initialize();
	m_pScroll->Initialize();

	EncountReset();

	IGameObject::Initialize();
}

void CCharacter::Update(void)
{
	m_Chara.position = m_CharaPos;

	//�C���x���g���[��ʂ��o�Ă���ƃL�����𓮂��Ȃ�����
	if (m_pInve->m_BsFlag == false)
	{
		m_Chara.Update();

		//�{�X�ɐG��Ă��邩���m�F
		CheckBoss();

		m_pData->SetCharaPos(m_Chara.position);

		//�L�����̃X�e�[�^�X
		switch (m_CharaState)
		{
		case CHARA_STATE::WAIT:
			//�~�܂��Ă�����
			WaitCharacter();
			break;
		case CHARA_STATE::MOVE:
			//�����Ă�����
			MoveCharacter();
			break;
		case CHARA_STATE::ENCOUNT_CHECK:
			//�G���J�E���g�̃`�F�b�N
			EncuntCounterCheck();
			break;
		default:
			break;
		}

		//�L�����̌����ύX
		if (m_DirCurrent != m_DirNext)
		{
			m_DirCurrent = m_DirNext;

			switch (m_DirNext)
			{
			case CCharacter::LEFT:
				m_Chara.Change("left");
				break;
			case CCharacter::RIGHT:
				m_Chara.Change("right");
				break;
			case CCharacter::UP:
				m_Chara.Change("up");
				break;
			case CCharacter::DOWN:
				m_Chara.Change("down");
				break;
			default:
				break;
			}
		}
	}

	IGameObject::Update();
}

void CCharacter::Draw(void)
{
	//�L�����̈ʒu���X�N���[�����������l�ɂ���
	m_ScrollCamera = m_CharaPos - m_pScroll->GetScroll();
	m_Chara.position = m_ScrollCamera;

	m_Chara.Draw();

	m_pInve->Draw();

	IGameObject::Draw();
}

void CCharacter::Finalize(void)
{
	m_Chara.Delete();

	IGameObject::Finalize();
}

void CCharacter::MoveCharacter(void)
{
	//�ړ��v�Z
	m_CharaPos += m_CharaSpeed;

	if (++m_CharaMoveTimer >= m_chara_timer)
	{
		m_CharaMoveTimer = 0;

		m_CharaSpeed = aqua::CVector2::ZERO;

		m_CharaState = CHARA_STATE::ENCOUNT_CHECK;

		return;
	}
}

void CCharacter::WaitCharacter(void)
{
	int x = (int)((m_Chara.position.x + 1.0f) / (float)m_pStage->m_map_chip_size);
	int y = (int)((m_Chara.position.y + 1.0f) / (float)m_pStage->m_map_chip_size);

	//�L�[�{�[�h����
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::DOWN))
	{
		m_DirNext = CHARA_DIRECTION::DOWN;

		//�ǂƃA�C�e���̓����蔻��
		if (m_pStage->CheckWall(x, y + 1) != true &&
			m_pItem->CheckItemWall(x, y + 1) != true)
		{
			m_CharaState = CHARA_STATE::MOVE;

			m_CharaSpeed.y = (float)m_CharaMoveSpeed;

			//�A�C�e���ɐG��Ă���ƌ��𑝂₷
			CheckItem(x, y + 1);
		}
	}
	else if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::UP))
	{
		m_DirNext = CHARA_DIRECTION::UP;

		//�ǂƃA�C�e���̓����蔻��
		if (m_pStage->CheckWall(x, y - 1) != true &&
			m_pItem->CheckItemWall(x, y - 1) != true)
		{
			m_CharaState = CHARA_STATE::MOVE;

			m_CharaSpeed.y = (float)-m_CharaMoveSpeed;

			//�A�C�e���ɐG��Ă���ƌ��𑝂₷
			CheckItem(x, y - 1);
		}

	}
	else if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::LEFT))
	{
		m_DirNext = CHARA_DIRECTION::LEFT;

		//�ǂƃA�C�e���̓����蔻��
		if (m_pStage->CheckWall(x - 1, y) != true &&
			m_pItem->CheckItemWall(x - 1, y) != true)
		{
			m_CharaState = CHARA_STATE::MOVE;

			m_CharaSpeed.x = (float)-m_CharaMoveSpeed;

			//�A�C�e���ɐG��Ă���ƌ��𑝂₷
			CheckItem(x - 1, y);
		}
	}
	else if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::RIGHT))
	{
		m_DirNext = CHARA_DIRECTION::RIGHT;

		//�ǂƃA�C�e���̓����蔻��
		if (m_pStage->CheckWall(x + 1, y) != true &&
			m_pItem->CheckItemWall(x + 1, y) != true)
		{
			m_CharaState = CHARA_STATE::MOVE;

			m_CharaSpeed.x = (float)m_CharaMoveSpeed;

			//�A�C�e���ɐG��Ă���ƌ��𑝂₷
			CheckItem(x + 1, y);
		}
	}

	//�{�^���������Ă��鎞�����������𗬂�
	if ((aqua::keyboard::Button(aqua::keyboard::KEY_ID::DOWN)) ||
		(aqua::keyboard::Button(aqua::keyboard::KEY_ID::UP)) ||
		(aqua::keyboard::Button(aqua::keyboard::KEY_ID::LEFT)) ||
		(aqua::keyboard::Button(aqua::keyboard::KEY_ID::RIGHT)))
	{
		WalkSound();
	}
	else
	{
		StopWalkSound();
	}

	//�����P�ȏ㎝���Ă���Ƃ��󔠂��J����
	if (aqua::keyboard::Released(aqua::keyboard::KEY_ID::F))
	{
		m_pSound->Play(SOUND_ID::OPEN);

		if (m_KeyCount >= 1)
		{
			CheckChest(x, y);
		}
	}
}

void CCharacter::GoldCount(void)
{
	//���̌����P���₷
	m_GoldCount += 1;

	m_pData->SetGoldCount(m_GoldCount);
}

void CCharacter::KeyCount(void)
{
	//���̌����P���₷
	m_KeyCount += 1;

	m_pData->SetKeyCount(m_KeyCount);
}

void CCharacter::UseKeyCount(void)
{
	//���̌����P���炷
	m_KeyCount -= 1;

	if (m_KeyCount <= 0)
		m_KeyCount = 0;

	m_pData->SetKeyCount(m_KeyCount);
}

void CCharacter::HealPotion(void)
{
	//�񕜖�̌����P���₷
	m_HealPotion += 1;

	m_pData->SetHealPotionCount(m_HealPotion);
}

void CCharacter::UseHealPotion(void)
{
	//�񕜖�̌����P���炷
	m_HealPotion -= 1;

	m_pData->SetHealPotionCount(m_HealPotion);
}

void CCharacter::CheckChest(int x, int y)
{
	//�󔠂ɐG��Ă��邩�𔻕ʁA�󔠂��J����
	if (m_pItem->CheckChest(x, y + 1) == true)
	{
		OpenBox(x, y + 1);
	}
	else if (m_pItem->CheckChest(x, y - 1) == true)
	{
		OpenBox(x, y - 1);
	}
	else if (m_pItem->CheckChest(x - 1, y) == true)
	{
		OpenBox(x - 1, y);
	}
	else if (m_pItem->CheckChest(x + 1, y) == true)
	{
		OpenBox(x + 1, y);
	}

	//�����P���炷
	UseKeyCount();
}

void CCharacter::OpenBox(int x, int y)
{
	if (m_pItem->m_ItemData[m_pItem->GetMapTile() * y + x] == (int)ITEM_ID::TREASURECHEST1)
		m_pItem->m_ItemData[m_pItem->GetMapTile() * y + x] = (int)ITEM_ID::TREASURECHEST2;

	int m_rand_number = 0;
	m_rand_number = aqua::Rand(0, 0);

	switch (m_rand_number)
	{
	case 0: HealPotion(); break;

	default:
		break;
	}
}

void CCharacter::CheckItem(int x, int y)
{
	//�G��Ă���A�C�e���𒲂׃A�C�e���̌��𑝂₷
	if (m_pItem->CheckGoldItem(x, y) == true)
	{
		GoldCount();
		m_pSound->Play(SOUND_ID::GET);

		//�󔠂��J������Ԃɂ���
		m_pItem->ChangeAir(x, y);
	}
	else if (m_pItem->CheckKeyItem(x, y) == true)
	{
		KeyCount();
		m_pSound->Play(SOUND_ID::GET);

		//�󔠂��J������Ԃɂ���
		m_pItem->ChangeAir(x, y);
	}
	else if (m_pItem->CheckHealPotionItem(x, y) == true)
	{
		HealPotion();
		m_pSound->Play(SOUND_ID::GET);

		//�󔠂��J������Ԃɂ���
		m_pItem->ChangeAir(x, y);
	}
}

bool CCharacter::IsEncount(void) const
{
	return m_Encount <= 0;
}

void CCharacter::EncountReset(void)
{
	//�G���J�E���g�̒l�i�ō��l�A�Œ�l�j
	m_Encount = aqua::Rand(10, 5);
}

void CCharacter::EncuntCounterCheck(void)
{
	int x = (int)((m_Chara.position.x + 1.0f) / (float)m_pStage->m_map_chip_size);
	int y = (int)((m_Chara.position.y + 1.0f) / (float)m_pStage->m_map_chip_size);

	//�L����������ꏊ�𒲂ׂ�
	m_pStage->CheckTile(x, y);

	//�L����������ꏊ�ɂ���ăG���J�E���g�l�����炷�����f����
	if (m_pStage->m_SandFlag_B == false)
		--m_Encount;
	else
		m_Encount;

	m_CharaState = CHARA_STATE::WAIT;
}

void CCharacter::WalkSound(void)
{
	int x = (int)((m_pData->GetCharaPos().x + 1.0f) / (float)m_pStage->m_map_chip_size);
	int y = (int)((m_pData->GetCharaPos().y + 1.0f) / (float)m_pStage->m_map_chip_size);

	//�������Ă���Ƃ���𒲂ׂ�i�T�E���h�p�̊֐��j
	m_pStage->CheckSoundTile(x, y);

	//�����ꏊ�ɂ���ăT�E���h��ς���
	if (m_pStage->m_DardFlag_A == true)
	{
		m_pSound->Play(SOUND_ID::WALK1);
		m_pSound->Stop(SOUND_ID::WALK2);
		m_pSound->Stop(SOUND_ID::WALK3);
		m_pSound->Stop(SOUND_ID::WALK4);
	}
	if (m_pStage->m_DardFlag_B == true)
	{
		m_pSound->Play(SOUND_ID::WALK2);
		m_pSound->Stop(SOUND_ID::WALK1);
		m_pSound->Stop(SOUND_ID::WALK3);
		m_pSound->Stop(SOUND_ID::WALK4);
	}
	if (m_pStage->m_SandFlag_A == true)
	{
		m_pSound->Play(SOUND_ID::WALK3);
		m_pSound->Stop(SOUND_ID::WALK1);
		m_pSound->Stop(SOUND_ID::WALK2);
		m_pSound->Stop(SOUND_ID::WALK4);
	}
	if (m_pStage->m_SandFlag_B == true)
	{
		m_pSound->Play(SOUND_ID::WALK4);
		m_pSound->Stop(SOUND_ID::WALK1);
		m_pSound->Stop(SOUND_ID::WALK2);
		m_pSound->Stop(SOUND_ID::WALK3);
	}
}

void CCharacter::StopWalkSound(void)
{
	//�����T�E���h�̒�~
	m_pSound->Stop(SOUND_ID::WALK1);
	m_pSound->Stop(SOUND_ID::WALK2);
	m_pSound->Stop(SOUND_ID::WALK3);
	m_pSound->Stop(SOUND_ID::WALK4);
}

void CCharacter::CheckBoss(void)
{
	int x = (int)((m_Chara.position.x + 1.0f) / (float)m_pStage->m_map_chip_size);
	int y = (int)((m_Chara.position.y + 1.0f) / (float)m_pStage->m_map_chip_size);

	//ENTER���������Ƃ��Ƀ{�X���G��Ă��邩�𒲂ׂ�
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER))
	{
		if (m_pItem->CheckBoss(x + 1, y) == true && m_DirNext == CHARA_DIRECTION::RIGHT ||
			m_pItem->CheckBoss(x - 1, y) == true && m_DirNext == CHARA_DIRECTION::LEFT ||
			m_pItem->CheckBoss(x, y + 1) == true && m_DirNext == CHARA_DIRECTION::DOWN ||
			m_pItem->CheckBoss(x, y - 1) == true && m_DirNext == CHARA_DIRECTION::UP)
			m_BossFlag = true;
		else
			m_BossFlag = false;

		m_pSound->Play(SOUND_ID::ENTER);

		/*
		* �����G��Ă�����R�����f�[�^�ɃZ�b�g��game_main_scene��
		* �Z�b�g���ꂽ�l���Q�Ƃ��{�X�ƃo�g���ɂȂ邩�𔻒f����
		*/
		m_pData->SetBossFlag(m_BossFlag);
	}
}