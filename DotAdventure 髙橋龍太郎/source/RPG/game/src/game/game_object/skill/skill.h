#pragma once
#include "aqua.h"
#include "../scene_manager/scene/battle/battle.h"
#include "../sound_manager/sound_manager.h"

class CSoundManager;
class CBattleScene;

class CSkill
	: public aqua::IGameObject
{
public:
	CSkill(aqua::IGameObject* parent);
	~CSkill() = default;

	void Initialize(void);

	void Updata(void);

	void Finalize(void);

	void CheckSkillNum(int num);

	void CheckMagicNum(int num);

	aqua::CVector2 SkillPos(int skillpos);

	static const int m_max_chara_skill = 4; //キャラのスキルの数
	static const int m_max_chara_magic = 4; //キャラの魔法の数
	static const int m_max_enemy_skill = 4; //敵のスキルの数

	int m_SkillNum; //使用スキルの番号
	int m_MagicNum; //使用魔法の番号
	
	int m_SkillCharaId[m_max_chara_skill]; //キャラのスキルのID
	int m_MagicCharaId[m_max_chara_magic]; //キャラの魔法のID
	int m_SkillEnemyId[m_max_enemy_skill]; //敵のスキルのID

	std::string m_SkillCharaName[m_max_chara_skill]; //キャラのスキルの名前
	std::string m_MagicCharaName[m_max_chara_magic]; //キャラの魔法の名前
	std::string m_SkillEnemyName[m_max_enemy_skill]; //敵のスキルの名前

	aqua::CVector2 m_SkillCharaPos[m_max_chara_skill]; //スキルの場所
	aqua::CVector2 m_MagicCharaPos[m_max_chara_magic]; //魔法の場所

	float m_SkillCharaDamage[m_max_chara_skill]; //キャラのスキルのダメージ量
	float m_MagicCharaDamage[m_max_chara_magic]; //キャラの魔法のダメージ量
	float m_SkillEnemyDamage[m_max_enemy_skill]; //敵のスキルのダメージ量

	int m_MagicCharaMp[m_max_chara_magic]; //魔法の消費MP

	struct CHARASKILL
	{
		int id_num;
		std::string name;
		aqua::CVector2 pos;
		float damage;
	};

	CHARASKILL m_CharaSkill[m_max_chara_skill];

	struct CHARAMAGIC
	{
		int id_num;
		std::string name;
		aqua::CVector2 pos;
		float damage;
		int mp;
	};

	CHARAMAGIC m_CharaMagic[m_max_chara_magic];

	struct ENEMYSKILL
	{
		int id_num;
		std::string name;
		float damage;
	};

	ENEMYSKILL m_EnemySkill[m_max_enemy_skill];

private:
	
	CSoundManager* m_pSound;
	CBattleScene* m_pBs;
};