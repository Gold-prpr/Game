#pragma once
#include "aqua.h"
#include "../Inventory/Inventory.h"

class CInventory;

class CData
	: public aqua::IGameObject
{
public:
	CData(aqua::IGameObject* parent);
	~CData() = default;

	void Initialize(void);

	void SetGoldCount(int gold_count);

	int GetGoldCount()const;

	void SetKeyCount(int key_count);

	int GetKeyCount()const;

	void SetHealPotionCount(int Heal_Potion);

	int GetHealPotionCount()const;

	void SetHp(int hp);

	int GetHp()const;

	void SetEnemyHp(int enemy_hp);

	int GetEnemyHp()const;

	void SetMp(int mp);

	int GetMp()const;

	void SetCharaLv(int lv);

	int GetCharaLv()const;

	void SetEnemyLv(int lv);

	int GetEnemyLv()const;

	void SetCharaSpeed(int speed);

	int GetCharaSpeed()const;

	void SetEnemySpeed(int speed);

	int GetEnemySpeed()const;

	void SetEnemyStren(int stren);

	int GetEnemyStren()const;

	void SetCharaStren(int stren);

	int GetCharaStren()const;

	void SetEnemyDefen(int defen);

	int GetEnemyDefen()const;

	void SetCharaDefen(int defen);

	int GetCharaDefen()const;

	void SetBossFlag(bool boss_flag);

	bool GetBossFlag()const;

	void SetCharaPos(aqua::CVector2 chara_pos);

	aqua::CVector2 GetCharaPos()const;

private:
	
	int m_GoldCount; //���̐�
	int m_KeyCount; //���̐�
	int m_HealPotionCount; //�񕜖�̐�
	
	int m_CharaLv; //�L������Level
	int m_Hp; //�L������HP
	int m_Mp; //�L������MP
	int m_CharaSpeed; //�L�����̃X�s�[�h
	int m_EnemyLv; //�G��Level
	int m_EnemyHp; //�G��HP
	int m_EnemySpeed; //�G�̃X�s�[�h
	int m_CharaStren; //�L�����̍U����
	int m_EnemyStren; //�G�̍U����
	int m_CharaDefen; //�L�����̖h���
	int m_EnemyDefen; //�G�̖h���

	bool m_BossFlag; //�{�X�ɐG��Ă��邩�̔��f�t���b�O

	aqua::CVector2 m_CharaPos; //�L�����̈ʒu
	aqua::CVector2 m_BossPos; //�{�X�̈ʒu
};