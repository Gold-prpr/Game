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
	
	int m_GoldCount; //金の数
	int m_KeyCount; //鍵の数
	int m_HealPotionCount; //回復薬の数
	
	int m_CharaLv; //キャラのLevel
	int m_Hp; //キャラのHP
	int m_Mp; //キャラのMP
	int m_CharaSpeed; //キャラのスピード
	int m_EnemyLv; //敵のLevel
	int m_EnemyHp; //敵のHP
	int m_EnemySpeed; //敵のスピード
	int m_CharaStren; //キャラの攻撃力
	int m_EnemyStren; //敵の攻撃力
	int m_CharaDefen; //キャラの防御力
	int m_EnemyDefen; //敵の防御力

	bool m_BossFlag; //ボスに触れているかの判断フラッグ

	aqua::CVector2 m_CharaPos; //キャラの位置
	aqua::CVector2 m_BossPos; //ボスの位置
};