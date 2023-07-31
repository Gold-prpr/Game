#include "data.h"

CData::CData(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Data")
{
}

void CData::Initialize(void)
{
	m_GoldCount = 0;
	m_KeyCount = 0;
	m_HealPotionCount = 0;

	m_Hp = 0;
	m_EnemyHp = 0;
	m_Mp = 0;

	m_CharaLv = 0;
	m_EnemyLv = 0;

	m_CharaSpeed = 0;
	m_EnemySpeed = 0;

	m_CharaStren = 0;
	m_EnemyStren = 0;

	m_CharaDefen = 0;
	m_EnemyDefen = 0;

	m_BossFlag = false;

	m_CharaPos = aqua::CVector2(0, 0);
	m_BossPos = aqua::CVector2(0, 0);
}

void CData::SetGoldCount(int gold_count)
{
	m_GoldCount = gold_count;
}

int CData::GetGoldCount() const
{
	return m_GoldCount;
}

void CData::SetKeyCount(int key_count)
{
	m_KeyCount = key_count;
}

int CData::GetKeyCount() const
{
	return m_KeyCount;
}

void CData::SetHealPotionCount(int Heal_Potion)
{
	m_HealPotionCount = Heal_Potion;
}

int CData::GetHealPotionCount() const
{
	return m_HealPotionCount;
}

void CData::SetHp(int hp)
{
	m_Hp = hp;
}

int CData::GetHp() const
{
	return m_Hp;
}

void CData::SetEnemyHp(int enemy_hp)
{
	m_EnemyHp = enemy_hp;
}

int CData::GetEnemyHp() const
{
	return m_EnemyHp;
}

void CData::SetMp(int mp)
{
	m_Mp = mp;
}

int CData::GetMp() const
{
	return m_Mp;
}

void CData::SetCharaLv(int lv)
{
	m_CharaLv = lv;
}

int CData::GetCharaLv() const
{
	return m_CharaLv;
}

void CData::SetEnemyLv(int lv)
{
	m_EnemyLv = lv;
}

int CData::GetEnemyLv() const
{
	return m_EnemyLv;
}

void CData::SetCharaSpeed(int speed)
{
	m_CharaSpeed = speed;
}

int CData::GetCharaSpeed() const
{
	return m_CharaSpeed;
}

void CData::SetEnemySpeed(int speed)
{
	m_EnemySpeed = speed;
}

int CData::GetEnemySpeed() const
{
	return m_EnemySpeed;
}

void CData::SetEnemyStren(int stren)
{
	m_EnemyStren = stren;
}

int CData::GetEnemyStren() const
{
	return m_EnemyStren;
}

void CData::SetCharaStren(int stren)
{
	m_CharaStren = stren;
}

int CData::GetCharaStren() const
{
	return m_CharaStren;
}

void CData::SetEnemyDefen(int defen)
{
	m_EnemyDefen = defen;
}

int CData::GetEnemyDefen() const
{
	return m_EnemyDefen;
}

void CData::SetCharaDefen(int defen)
{
	m_CharaDefen = defen;
}

int CData::GetCharaDefen() const
{
	return m_CharaDefen;
}

void CData::SetBossFlag(bool boss_flag)
{
	m_BossFlag = boss_flag;
}

bool CData::GetBossFlag() const
{
	return m_BossFlag;
}

void CData::SetCharaPos(aqua::CVector2 chara_pos)
{
	m_CharaPos = chara_pos;
}

aqua::CVector2 CData::GetCharaPos() const
{
	return aqua::CVector2(m_CharaPos);
}
