#include "character.h"

const int CCharacter::m_character_width = 80;
const int CCharacter::m_character_height = 80;

const int CCharacter::m_chara_timer = 20;

enum class CHARA_STATE
{
	WAIT,	//待機
	MOVE,	//移動
	ENCOUNT_CHECK //エンカウントのチェック
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

	m_Chara.Create("data\\ユニット\\キャラ.ass", "down");

	//キャラクターの位置
	m_CharaPos = aqua::CVector2(80.0f, 80.0f);
	//m_CharaPos = aqua::CVector2(3360.0f, 1680.0f);

	m_CharaSpeed = aqua::CVector2(0.0f, 0.0f);

	//キャラクターは下向き
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

	//インベントリー画面が出ているとキャラを動かなくする
	if (m_pInve->m_BsFlag == false)
	{
		m_Chara.Update();

		//ボスに触れているかを確認
		CheckBoss();

		m_pData->SetCharaPos(m_Chara.position);

		//キャラのステータス
		switch (m_CharaState)
		{
		case CHARA_STATE::WAIT:
			//止まっている状態
			WaitCharacter();
			break;
		case CHARA_STATE::MOVE:
			//動いている状態
			MoveCharacter();
			break;
		case CHARA_STATE::ENCOUNT_CHECK:
			//エンカウントのチェック
			EncuntCounterCheck();
			break;
		default:
			break;
		}

		//キャラの向き変更
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
	//キャラの位置をスクロール分引いた値にする
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
	//移動計算
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

	//キーボード処理
	if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::DOWN))
	{
		m_DirNext = CHARA_DIRECTION::DOWN;

		//壁とアイテムの当たり判定
		if (m_pStage->CheckWall(x, y + 1) != true &&
			m_pItem->CheckItemWall(x, y + 1) != true)
		{
			m_CharaState = CHARA_STATE::MOVE;

			m_CharaSpeed.y = (float)m_CharaMoveSpeed;

			//アイテムに触れていると個数を増やす
			CheckItem(x, y + 1);
		}
	}
	else if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::UP))
	{
		m_DirNext = CHARA_DIRECTION::UP;

		//壁とアイテムの当たり判定
		if (m_pStage->CheckWall(x, y - 1) != true &&
			m_pItem->CheckItemWall(x, y - 1) != true)
		{
			m_CharaState = CHARA_STATE::MOVE;

			m_CharaSpeed.y = (float)-m_CharaMoveSpeed;

			//アイテムに触れていると個数を増やす
			CheckItem(x, y - 1);
		}

	}
	else if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::LEFT))
	{
		m_DirNext = CHARA_DIRECTION::LEFT;

		//壁とアイテムの当たり判定
		if (m_pStage->CheckWall(x - 1, y) != true &&
			m_pItem->CheckItemWall(x - 1, y) != true)
		{
			m_CharaState = CHARA_STATE::MOVE;

			m_CharaSpeed.x = (float)-m_CharaMoveSpeed;

			//アイテムに触れていると個数を増やす
			CheckItem(x - 1, y);
		}
	}
	else if (aqua::keyboard::Button(aqua::keyboard::KEY_ID::RIGHT))
	{
		m_DirNext = CHARA_DIRECTION::RIGHT;

		//壁とアイテムの当たり判定
		if (m_pStage->CheckWall(x + 1, y) != true &&
			m_pItem->CheckItemWall(x + 1, y) != true)
		{
			m_CharaState = CHARA_STATE::MOVE;

			m_CharaSpeed.x = (float)m_CharaMoveSpeed;

			//アイテムに触れていると個数を増やす
			CheckItem(x + 1, y);
		}
	}

	//ボタンを押している時だけ歩く音を流す
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

	//鍵を１つ以上持っているとき宝箱を開ける
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
	//金の個数を１つ増やす
	m_GoldCount += 1;

	m_pData->SetGoldCount(m_GoldCount);
}

void CCharacter::KeyCount(void)
{
	//鍵の個数を１つ増やす
	m_KeyCount += 1;

	m_pData->SetKeyCount(m_KeyCount);
}

void CCharacter::UseKeyCount(void)
{
	//鍵の個数を１つ減らす
	m_KeyCount -= 1;

	if (m_KeyCount <= 0)
		m_KeyCount = 0;

	m_pData->SetKeyCount(m_KeyCount);
}

void CCharacter::HealPotion(void)
{
	//回復薬の個数を１つ増やす
	m_HealPotion += 1;

	m_pData->SetHealPotionCount(m_HealPotion);
}

void CCharacter::UseHealPotion(void)
{
	//回復薬の個数を１つ減らす
	m_HealPotion -= 1;

	m_pData->SetHealPotionCount(m_HealPotion);
}

void CCharacter::CheckChest(int x, int y)
{
	//宝箱に触れているかを判別、宝箱を開ける
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

	//鍵を１つ減らす
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
	//触れているアイテムを調べアイテムの個数を増やす
	if (m_pItem->CheckGoldItem(x, y) == true)
	{
		GoldCount();
		m_pSound->Play(SOUND_ID::GET);

		//宝箱を開けた状態にする
		m_pItem->ChangeAir(x, y);
	}
	else if (m_pItem->CheckKeyItem(x, y) == true)
	{
		KeyCount();
		m_pSound->Play(SOUND_ID::GET);

		//宝箱を開けた状態にする
		m_pItem->ChangeAir(x, y);
	}
	else if (m_pItem->CheckHealPotionItem(x, y) == true)
	{
		HealPotion();
		m_pSound->Play(SOUND_ID::GET);

		//宝箱を開けた状態にする
		m_pItem->ChangeAir(x, y);
	}
}

bool CCharacter::IsEncount(void) const
{
	return m_Encount <= 0;
}

void CCharacter::EncountReset(void)
{
	//エンカウントの値（最高値、最低値）
	m_Encount = aqua::Rand(10, 5);
}

void CCharacter::EncuntCounterCheck(void)
{
	int x = (int)((m_Chara.position.x + 1.0f) / (float)m_pStage->m_map_chip_size);
	int y = (int)((m_Chara.position.y + 1.0f) / (float)m_pStage->m_map_chip_size);

	//キャラがいる場所を調べる
	m_pStage->CheckTile(x, y);

	//キャラがいる場所によってエンカウント値を減らすか判断する
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

	//今歩いているところを調べる（サウンド用の関数）
	m_pStage->CheckSoundTile(x, y);

	//歩く場所によってサウンドを変える
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
	//歩くサウンドの停止
	m_pSound->Stop(SOUND_ID::WALK1);
	m_pSound->Stop(SOUND_ID::WALK2);
	m_pSound->Stop(SOUND_ID::WALK3);
	m_pSound->Stop(SOUND_ID::WALK4);
}

void CCharacter::CheckBoss(void)
{
	int x = (int)((m_Chara.position.x + 1.0f) / (float)m_pStage->m_map_chip_size);
	int y = (int)((m_Chara.position.y + 1.0f) / (float)m_pStage->m_map_chip_size);

	//ENTERをおしたときにボスが触れているかを調べる
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
		* もし触れていたらコモンデータにセットしgame_main_sceneで
		* セットされた値を参照しボスとバトルになるかを判断する
		*/
		m_pData->SetBossFlag(m_BossFlag);
	}
}