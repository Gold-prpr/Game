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

	static const int m_max_chara_skill = 4; //�L�����̃X�L���̐�
	static const int m_max_chara_magic = 4; //�L�����̖��@�̐�
	static const int m_max_enemy_skill = 4; //�G�̃X�L���̐�

	int m_SkillNum; //�g�p�X�L���̔ԍ�
	int m_MagicNum; //�g�p���@�̔ԍ�
	
	int m_SkillCharaId[m_max_chara_skill]; //�L�����̃X�L����ID
	int m_MagicCharaId[m_max_chara_magic]; //�L�����̖��@��ID
	int m_SkillEnemyId[m_max_enemy_skill]; //�G�̃X�L����ID

	std::string m_SkillCharaName[m_max_chara_skill]; //�L�����̃X�L���̖��O
	std::string m_MagicCharaName[m_max_chara_magic]; //�L�����̖��@�̖��O
	std::string m_SkillEnemyName[m_max_enemy_skill]; //�G�̃X�L���̖��O

	aqua::CVector2 m_SkillCharaPos[m_max_chara_skill]; //�X�L���̏ꏊ
	aqua::CVector2 m_MagicCharaPos[m_max_chara_magic]; //���@�̏ꏊ

	float m_SkillCharaDamage[m_max_chara_skill]; //�L�����̃X�L���̃_���[�W��
	float m_MagicCharaDamage[m_max_chara_magic]; //�L�����̖��@�̃_���[�W��
	float m_SkillEnemyDamage[m_max_enemy_skill]; //�G�̃X�L���̃_���[�W��

	int m_MagicCharaMp[m_max_chara_magic]; //���@�̏���MP

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