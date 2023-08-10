#include "skill.h"

const int m_max_chara_skill = 4;
const int m_max_chara_magic = 4;
const int m_max_enemy_skill = 4;

CSkill::CSkill(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Skill")
{
}

void CSkill::Initialize(void)
{
	m_pSound = (CSoundManager*)aqua::FindGameObject("SoundManager");
	m_pBs = (CBattleScene*)aqua::FindGameObject("battleScene");

	m_SkillNum = 0;
	m_MagicNum = 0;

	m_CharaSkill[0] = { 1,"たいあたり",SkillPos(m_CharaSkill[0].id_num) , 1170.0f };
	m_CharaSkill[1] = { 2,"パンチ",SkillPos(m_CharaSkill[1].id_num) , 75.0f };
	m_CharaSkill[2] = { 3,"なく",SkillPos(m_CharaSkill[2].id_num) , 60.0f };
	m_CharaSkill[3] = { 4,"キック",SkillPos(m_CharaSkill[3].id_num), 80.0f };

	m_CharaMagic[0] = { 1,"ファイヤ",SkillPos(m_CharaMagic[0].id_num) , 70.0f , 4 };
	m_CharaMagic[1] = { 2,"サンダー",SkillPos(m_CharaMagic[1].id_num) , 60.0f  , 2 };
	m_CharaMagic[2] = { 3,"ボム",SkillPos(m_CharaMagic[2].id_num) , 80.0f  , 8 };
	m_CharaMagic[3] = { 4,"アイス",SkillPos(m_CharaMagic[3].id_num), 75.0f  , 6 };

	m_EnemySkill[0] = { 1,"雷",70.0f };
	m_EnemySkill[1] = { 2,"叩く",50.0f };
	m_EnemySkill[2] = { 3,"ひっかく",60.0f };
	m_EnemySkill[3] = { 4,"とびはねる",65.0f };

	IGameObject::Initialize();
}

void CSkill::Updata(void)
{
	for (int j = 0; j < m_max_chara_skill; j++)
	{
		m_SkillCharaId[j] = m_CharaSkill[j].id_num;

		m_SkillCharaName[j] = m_CharaSkill[j].name;

		m_SkillCharaPos[j] = m_CharaSkill[j].pos;

		m_SkillCharaDamage[j] = m_CharaSkill[j].damage;
	}

	for (int i = 0; i < m_max_chara_magic; i++)
	{
		m_MagicCharaId[i] = m_CharaMagic[i].id_num;

		m_MagicCharaName[i] = m_CharaMagic[i].name;

		m_MagicCharaPos[i] = m_CharaMagic[i].pos;

		m_MagicCharaDamage[i] = m_CharaMagic[i].damage;

		m_MagicCharaMp[i] = m_CharaMagic[i].mp;
	}

	for (int k = 0; k < m_max_enemy_skill; k++)
	{
		m_SkillEnemyId[k] = m_EnemySkill[k].id_num;

		m_SkillEnemyName[k] = m_EnemySkill[k].name;

		m_SkillEnemyDamage[k] = m_EnemySkill[k].damage;
	}

	IGameObject::Update();
}

void CSkill::Finalize(void)
{
	
}

void CSkill::CheckSkillNum(int num)
{
	//スキルのIDをスキルナムに代入
	//battle.cppで使用
	if (m_SkillCharaId[0] == num)
		m_SkillNum = m_SkillCharaId[0];

	if (m_SkillCharaId[1] == num)
		m_SkillNum = m_SkillCharaId[1];

	if (m_SkillCharaId[2] == num)
		m_SkillNum = m_SkillCharaId[2];

	if (m_SkillCharaId[3] == num)
		m_SkillNum = m_SkillCharaId[3];

	m_pBs->m_Serect.position = m_pBs->SellectArrowPos(num);
}

void CSkill::CheckMagicNum(int num)
{
	//魔法のIDをマジックナムに代入
	//battle.cppで使用
	if (m_MagicCharaId[0] == num)
		m_MagicNum = m_MagicCharaId[0];

	if (m_MagicCharaId[1] == num)
		m_MagicNum = m_MagicCharaId[1];

	if (m_MagicCharaId[2] == num)
		m_MagicNum = m_MagicCharaId[2];

	if (m_MagicCharaId[3] == num)
		m_MagicNum = m_MagicCharaId[3];

	m_pBs->m_Serect.position = m_pBs->SellectArrowPos(num);
}

aqua::CVector2 CSkill::SkillPos(int skillpos)
{
	//スキルの位置
	/*
	*   1  3
	*   2  4
	*/
	aqua::CVector2	command_skill_1 = m_pBs->m_CommandSprite.position + aqua::CVector2::ONE * 100;
	float			command_skill_2 = m_pBs->m_Battle.position.x + m_pBs->m_Battle.GetTextWidth() * 3;
	float			command_skill_3 = command_skill_1.y + m_pBs->m_CommandSprite.GetTextureHeight() - 300.0f;

	if (skillpos == 1)
		return  aqua::CVector2(command_skill_1.x, command_skill_1.y);
	else if (skillpos == 2)
		return  aqua::CVector2(command_skill_1.x, command_skill_3);
	else if (skillpos == 3)
		return  aqua::CVector2(command_skill_2, command_skill_1.y);
	else if (skillpos == 4)
		return  aqua::CVector2(command_skill_2, command_skill_3);
}