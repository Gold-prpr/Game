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

	BATTLE_FASE m_BattleFase; //戦闘の流れ（フェーズ）

	aqua::CLabel m_Battle; //「たたかう」のラベル
	aqua::CLabel m_Magic; //「まほう」のラベル
	aqua::CLabel m_Tool; //「どうぐ」のラベル
	aqua::CLabel m_RunAway; //「にげる」のラベル

	aqua::CSprite m_Serect; //矢印のスプライト

	aqua::CSprite m_CommandSprite; //コマンドの背景のスプライト
	aqua::CSprite m_CommandSprite2; //コマンドの背景のスプライト
	aqua::CSprite m_CommandSprite3; //コマンドの背景のスプライト
	aqua::CSprite m_CommandSprite4; //コマンドの背景のスプライト
	
private:
	aqua::CSprite m_BackgourndSprite; //背景のスプライト

	aqua::CLabel m_No; //「はい」のラベル
	aqua::CLabel m_Yes; //「いいえ」のラベル

	aqua::CLabel m_UseTool; //「回復薬」のラベル

	int m_Hp; //キャラのHP
	aqua::CLabel m_HpLabel; //HPの名前を表示するためのラベル
	aqua::CLabel m_HpNumber; //HPの数字を表示するためのラベル

	int m_Mp; //キャラのMP
	aqua::CLabel m_MpLabel; //MPの名前を表示するためのラベル
	aqua::CLabel m_MpNumber; //MPの数字を表示するためのラベル

	int m_EnemyHp; //敵のHP
	aqua::CLabel m_EnemyHpLabel; //HPの名前を表示するためのラベル
	aqua::CLabel m_EnemyHpNumber; //HPの数字を表示するためのラベル

	int m_EnemyLv; //敵のLv
	aqua::CLabel m_EnemyLvLabel; //Lvの名前を表示するためのラベル
	aqua::CLabel m_EnemyLvNumber; //Lvの数字を表示するためのラベル

	int m_HealNum; //回復薬の数
	aqua::CLabel m_HealNumLabel; //回復薬の名前を表示するためのラベル
	aqua::CLabel m_HealNumCount; //回復薬の数字を表示するためのラベル

	aqua::CLabel m_BodyBrow; //「たいあたり」のラベル
	aqua::CLabel m_Punch; //「パンチ」のラベル
	aqua::CLabel m_Kick; //「キック」のラベル
	aqua::CLabel m_Sad; //「なく」のラベル

	aqua::CLabel m_Fire; //「ファイヤー」のラベル
	aqua::CLabel m_Thunder; //「サンダー」のラベル
	aqua::CLabel m_Bom; //「ボム」のラベル
	aqua::CLabel m_Blizzard; //「アイス」のラベル

	aqua::CLabel m_SkillPower; //技の威力名を表示するためのラベル
	aqua::CLabel m_SkillPowerNum; //技の威力量を表示するためのラベル
	
	aqua::CLabel m_SkillMp; //魔法の威力名を表示するためのラベル
	aqua::CLabel m_SkillMpNum; //魔法の威力量を表示するためのラベル

	aqua::CLabel m_EnemyName; //敵の名前を表示するためのラベル

	int m_Flame = 0; //矢印のイージングに使うフレーム数

	int m_EnemyAttack; //敵の技の番号

	int m_RandRun; //逃げる際のランダムな数字

	bool m_CheckFlagChara; //キャラの攻撃判断フラッグ
	bool m_CheckFlagEnemy; //敵の攻撃判断フラッグ

	int m_Damage; //ダメージ数

	bool m_DownFlag; //コマンドセレクト上下の判断フラッグ
	bool m_ReftFlag; //コマンドセレクト左右の判断フラッグ

	bool m_SeFlag; //サウンドが流れているかの判断フラッグ

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