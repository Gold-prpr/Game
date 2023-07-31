#pragma once

#include "aqua.h"
#include "..\scene.h"
#include "../game_main_scene/game_main_scene.h"
#include "../../../character/character.h"
#include "../../../data/data.h"
#include "../../../skill/skill.h"
#include "../../../comment_viewer/comment_viewer.h"
#include "../../../enemy_manager/enemy_manager.h"
#include "../../../enemy_manager/enemy/enemy.h"
#include "../../../map/map.h"
#include "../../../map/item/item.h"
#include "../../../map/tile_id.h"
#include "../../../Inventory/Inventory.h"
#include "../../../sound_manager/sound_manager.h"
#include "../../../enemy_manager/enemy/enemy.h"

class CSoundManager;
class CGameMainScene;
class CEnemyManager;
class CCharacter;
class IEnemy;
class CData;
class CSkill;
class CComment;
class CStage;
class CInventory;
class CItem;

class CBattleScene
	: public IScene
{
public:
	CBattleScene(aqua::IGameObject* parent);

	~CBattleScene(void) = default;

	void Initialize(void) override;

	void Update(void) override;

	void Draw(void) override;

	void Finalize(void) override;

	void PopEnemy(void);

	void StartMessage(void);

	void SerectBattleCommand(void);

	void SerectSkill(void);

	void RunMessage(void);

	void RunAway(void);

	void SelectTool(void);

	void UseToolMessage(void);

	void SelectJudgTool(void);

	void Magic(void);

	void PlayerAttack(void);

	void PlayerMagicAttack(void);

	void MagicAttackMessage(void);

	void FaseEnemyMessage(void);

	void FaseCharaMessage(void);

	void EnemyAttack(void);

	void ResultMessage(void);

	void HealHp(void);

	int toCharaDamage(void);

	int toEnemyDamage(void);

	int toEnemyMagicDamage(void);

	aqua::CVector2 SellectArrowPos(int sele_aro_pos);

	enum BATTLE_FASE
	{
		INITIALIZE,
		STARTMESSAGE,
		FASECHARAMESSAGE,
		COMMANDFASE,
		COMMANDMYMESSAGE,
		SKILLCOMMAND,
		GAMEFASE,
		GAMEMAGICFASE,
		GAMEMAGICFASEMESSAGE,
		FASEENEMYMESSAGE,
		ENEMYFASE,
		RESULT,
		DEADDIRECTION,
		RUNAWAY,
		SELECTTOOL,
		USETOOL,
		JUDGETOOL,
		MAGIC,

		MAX
	};

	BATTLE_FASE m_BattleFase; //�퓬�̗���i�t�F�[�Y�j

	aqua::CLabel m_Battle; //�u���������v�̃��x��
	aqua::CLabel m_Magic; //�u�܂ق��v�̃��x��
	aqua::CLabel m_Tool; //�u�ǂ����v�̃��x��
	aqua::CLabel m_RunAway; //�u�ɂ���v�̃��x��

	aqua::CSprite m_Serect; //���̃X�v���C�g

	aqua::CSprite m_CommandSprite; //�R�}���h�̔w�i�̃X�v���C�g
	aqua::CSprite m_CommandSprite2; //�R�}���h�̔w�i�̃X�v���C�g
	aqua::CSprite m_CommandSprite3; //�R�}���h�̔w�i�̃X�v���C�g
	aqua::CSprite m_CommandSprite4; //�R�}���h�̔w�i�̃X�v���C�g
	
private:
	aqua::CSprite m_BackgourndSprite; //�w�i�̃X�v���C�g

	aqua::CLabel m_No; //�u�͂��v�̃��x��
	aqua::CLabel m_Yes; //�u�������v�̃��x��

	aqua::CLabel m_UseTool; //�u�񕜖�v�̃��x��

	int m_Hp; //�L������HP
	aqua::CLabel m_HpLabel; //HP�̖��O��\�����邽�߂̃��x��
	aqua::CLabel m_HpNumber; //HP�̐�����\�����邽�߂̃��x��

	int m_Mp; //�L������MP
	aqua::CLabel m_MpLabel; //MP�̖��O��\�����邽�߂̃��x��
	aqua::CLabel m_MpNumber; //MP�̐�����\�����邽�߂̃��x��

	int m_EnemyHp; //�G��HP
	aqua::CLabel m_EnemyHpLabel; //HP�̖��O��\�����邽�߂̃��x��
	aqua::CLabel m_EnemyHpNumber; //HP�̐�����\�����邽�߂̃��x��

	int m_EnemyLv; //�G��Lv
	aqua::CLabel m_EnemyLvLabel; //Lv�̖��O��\�����邽�߂̃��x��
	aqua::CLabel m_EnemyLvNumber; //Lv�̐�����\�����邽�߂̃��x��

	int m_HealNum; //�񕜖�̐�
	aqua::CLabel m_HealNumLabel; //�񕜖�̖��O��\�����邽�߂̃��x��
	aqua::CLabel m_HealNumCount; //�񕜖�̐�����\�����邽�߂̃��x��

	aqua::CLabel m_BodyBrow; //�u����������v�̃��x��
	aqua::CLabel m_Punch; //�u�p���`�v�̃��x��
	aqua::CLabel m_Kick; //�u�L�b�N�v�̃��x��
	aqua::CLabel m_Sad; //�u�Ȃ��v�̃��x��

	aqua::CLabel m_Fire; //�u�t�@�C���[�v�̃��x��
	aqua::CLabel m_Thunder; //�u�T���_�[�v�̃��x��
	aqua::CLabel m_Bom; //�u�{���v�̃��x��
	aqua::CLabel m_Blizzard; //�u�A�C�X�v�̃��x��

	aqua::CLabel m_SkillPower; //�Z�̈З͖���\�����邽�߂̃��x��
	aqua::CLabel m_SkillPowerNum; //�Z�̈З͗ʂ�\�����邽�߂̃��x��
	
	aqua::CLabel m_SkillMp; //���@�̈З͖���\�����邽�߂̃��x��
	aqua::CLabel m_SkillMpNum; //���@�̈З͗ʂ�\�����邽�߂̃��x��

	aqua::CLabel m_EnemyName; //�G�̖��O��\�����邽�߂̃��x��

	int m_Flame = 0; //���̃C�[�W���O�Ɏg���t���[����

	int m_EnemyAttack; //�G�̋Z�̔ԍ�

	int m_RandRun; //������ۂ̃����_���Ȑ���

	bool m_CheckFlagChara; //�L�����̍U�����f�t���b�O
	bool m_CheckFlagEnemy; //�G�̍U�����f�t���b�O

	int m_Damage; //�_���[�W��

	bool m_DownFlag; //�R�}���h�Z���N�g�㉺�̔��f�t���b�O
	bool m_ReftFlag; //�R�}���h�Z���N�g���E�̔��f�t���b�O

	bool m_SeFlag; //�T�E���h������Ă��邩�̔��f�t���b�O

	CSoundManager* m_pSound;
	CGameMainScene* m_pGms;
	CEnemyManager* m_pEm;
	CCharacter* m_pChara;
	CData* m_pData;
	CSkill* m_pSkill;
	CComment* m_pComment;
	CStage* m_pStage;
	IEnemy* m_pEnemy;
	CInventory* m_pInve;
};