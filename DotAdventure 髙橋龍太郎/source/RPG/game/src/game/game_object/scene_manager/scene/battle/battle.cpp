#include "battle.h"
#include "..\..\scene_manager.h"
#include "../../../enemy_manager/enemy_manager.h"
#include "../../../comment_viewer/comment_viewer.h"
#include "../../../enemy_manager/enemy/enemy_id.h"

CBattleScene::
CBattleScene(aqua::IGameObject* parent)
	: IScene(parent, "battleScene")
	, m_EnemyAttack(0)
{
}

void
CBattleScene::
Initialize(void)
{
	m_pSound = (CSoundManager*)aqua::FindGameObject("SoundManager");
	m_pEm = (CEnemyManager*)aqua::CreateGameObject<CEnemyManager>(this);
	m_pChara = (CCharacter*)aqua::FindGameObject("Character");
	m_pData = (CData*)aqua::FindGameObject("Data");
	m_pComment = (CComment*)aqua::CreateGameObject<CComment>(this);
	m_pSkill = (CSkill*)aqua::CreateGameObject<CSkill>(this);
	m_pStage = (CStage*)aqua::FindGameObject("Map");
	m_pInve = (CInventory*)aqua::FindGameObject("Inventory");

	m_BackgourndSprite.Create("data\\戦闘\\background.png");
	m_BackgourndSprite.position = aqua::CVector2::ZERO;

	m_pSound->Play(SOUND_ID::BATTLEBGM);

	m_BattleFase = CBattleScene::STARTMESSAGE;

	//敵の出現
	PopEnemy();

	m_CommandSprite.Create("data\\戦闘\\Pixelart-022-command.png");
	m_CommandSprite.position = aqua::CVector2(aqua::GetWindowWidth() - m_CommandSprite.GetTextureWidth() * 1.25f,
		aqua::GetWindowHeight() - m_CommandSprite.GetTextureHeight());
	m_CommandSprite2.Create("data\\戦闘\\Pixelart-022-command2.png");
	m_CommandSprite2.position = aqua::CVector2(0, aqua::GetWindowHeight() - m_CommandSprite.GetTextureHeight());
	m_CommandSprite3.Create("data\\戦闘\\Pixelart-022-command3.png");
	m_CommandSprite3.position = aqua::CVector2(0, 10.0f);
	m_CommandSprite4.Create("data\\戦闘\\Pixelart-022-command4.png");
	m_CommandSprite4.position = aqua::CVector2(aqua::GetWindowWidth() - m_CommandSprite4.GetTextureWidth(), 0);

	m_HpLabel.Create(45);
	m_HpNumber.Create(45);
	m_HpLabel.text = "HP　:";
	m_HpLabel.position = aqua::CVector2(90,
		aqua::GetWindowHeight() - m_CommandSprite.GetTextureHeight() + m_HpLabel.GetFontHeight());
	m_HpNumber.position = aqua::CVector2(m_HpLabel.position.x + m_HpLabel.GetTextWidth() + 10.0f,
		m_HpLabel.position.y);

	m_MpLabel.Create(45);
	m_MpNumber.Create(45);
	m_MpLabel.text = "MP　:";
	m_MpLabel.position = aqua::CVector2(90,
		m_HpLabel.position.y + m_MpLabel.GetFontHeight() + 20.0f);
	m_MpNumber.position = aqua::CVector2(m_MpLabel.position.x + m_MpLabel.GetTextWidth() + 10.0f,
		m_MpLabel.position.y);

	m_SkillPower.Create(45);
	m_SkillPower.text = "威力：";
	m_SkillPowerNum.Create(45);

	m_SkillPower.position = m_CommandSprite4.position + (aqua::CVector2::ONE * 60.0f);
	m_SkillPowerNum.position = aqua::CVector2(m_SkillPower.position.x + m_SkillPower.GetTextWidth(), m_SkillPower.position.y);

	m_SkillMp.Create(45);
	m_SkillMp.text = "消費MP：";
	m_SkillMpNum.Create(45);

	m_SkillMp.position = aqua::CVector2(m_SkillPower.position.x, m_SkillPower.position.y + m_SkillPower.GetFontHeight() + 40.0f);
	m_SkillMpNum.position = aqua::CVector2(m_SkillMp.position.x + m_SkillMp.GetTextWidth(), m_SkillMp.position.y);
	
	m_HealNum = 50;
	m_HealNumLabel.Create(45);
	m_HealNumLabel.text = "回復量：";
	m_HealNumLabel.position = m_CommandSprite4.position + (aqua::CVector2::ONE * 60.0f);

	m_HealNumCount.Create(45);
	m_HealNumCount.text = std::to_string(m_HealNum);
	m_HealNumCount.position = aqua::CVector2(m_HealNumLabel.position.x + m_HealNumLabel.GetTextWidth(), m_HealNumLabel.position.y);
	
	m_DownFlag = false;
	m_ReftFlag = false;

	m_CheckFlagChara = false;
	m_CheckFlagEnemy = false;

	m_Damage = 0;

	//出現した敵によって表示する敵の名前を変える
	m_EnemyName.Create(45);
	if (m_pEm->m_EnemyNumber == (int)ENEMY_ID::REDDEMON)
		m_EnemyName.text = "赤鬼";
	else if (m_pEm->m_EnemyNumber == (int)ENEMY_ID::CATCOIN)
		m_EnemyName.text = "化け猫";
	else if (m_pEm->m_EnemyNumber == (int)ENEMY_ID::CHESTHANDS)
		m_EnemyName.text = "悪魔の箱";
	else if (m_pEm->m_EnemyNumber == (int)ENEMY_ID::BOSS)
		m_EnemyName.text = "ドラゴン";

	m_EnemyName.position = aqua::CVector2(90, m_CommandSprite3.position.y + m_EnemyName.GetFontHeight());
	m_EnemyHpLabel.Create(45);
	m_EnemyHpNumber.Create(45);
	m_EnemyHpLabel.text = "HP　:";
	m_EnemyHpLabel.position = aqua::CVector2(90, 120.0f);
	m_EnemyHpNumber.position = aqua::CVector2(m_EnemyHpLabel.position.x + m_EnemyHpLabel.GetTextWidth() + 10.0f,
		m_EnemyHpLabel.position.y);

	m_EnemyLvLabel.Create(45);
	m_EnemyLvNumber.Create(45);
	m_EnemyLv = m_pData->GetEnemyLv();
	m_EnemyLvLabel.text = "Lv　:";
	m_EnemyLvNumber.text = std::to_string(m_EnemyLv);
	m_EnemyLvLabel.position = aqua::CVector2(m_EnemyHpLabel.position.x,
		m_EnemyHpLabel.position.y + m_EnemyHpLabel.GetFontHeight() + 30.0f);
	m_EnemyLvNumber.position = aqua::CVector2(m_EnemyLvLabel.position.x + m_EnemyHpLabel.GetTextWidth() + 10.0f,
		m_EnemyLvLabel.position.y);

	m_Serect.Create("data\\arrow-145781__480.png");
	m_Serect.position = aqua::CVector2(m_CommandSprite.position.x + 100.0f - m_Serect.GetTextureWidth(), m_CommandSprite.position.y + 100.0f);
	m_Serect.anchor = aqua::CVector2(m_Serect.GetTextureWidth() / 2.0f, m_Serect.GetTextureHeight() / 2.0f);

	m_Battle.Create(45);
	m_Battle.text = "たたかう";
	m_Battle.position = aqua::CVector2(m_CommandSprite.position.x + 100.0f,
		m_CommandSprite.position.y + 100.0f);

	m_Magic.Create(45);
	m_Magic.text = "まほう";
	m_Magic.position = aqua::CVector2(m_Battle.position.x + m_Battle.GetTextWidth() * 3,
		m_CommandSprite.position.y + 100.0f);

	m_Tool.Create(45);
	m_Tool.text = "どうぐ";
	m_Tool.position = aqua::CVector2(m_CommandSprite.position.x + 100.0f,
		m_CommandSprite.position.y + m_CommandSprite.GetTextureHeight() - 200.0f);

	m_RunAway.Create(45);
	m_RunAway.text = "にげる";
	m_RunAway.position = aqua::CVector2(m_Battle.position.x + m_Battle.GetTextWidth() * 3,
		m_CommandSprite.position.y + m_CommandSprite.GetTextureHeight() - 200.0f);

	m_BodyBrow.Create(45);
	m_Punch.Create(45);
	m_Sad.Create(45);
	m_Kick.Create(45);

	m_Fire.Create(45);
	m_Thunder.Create(45);
	m_Bom.Create(45);
	m_Blizzard.Create(45);

	m_pSkill->Initialize();

	m_Yes.Create(45);
	m_Yes.text = "はい";
	m_Yes.position = m_pSkill->SkillPos(2);
	m_No.Create(45);
	m_No.text = "いいえ";
	m_No.position = m_pSkill->SkillPos(4);

	m_SeFlag = false;

	m_pInve->Initialize();

	IGameObject::Initialize();
}

void
CBattleScene::
Update(void)
{
	//サウンド
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::LEFT))
		m_pSound->Play(SOUND_ID::MAINSELECT);
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::RIGHT))
		m_pSound->Play(SOUND_ID::MAINSELECT);
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::UP))
		m_pSound->Play(SOUND_ID::MAINSELECT);
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::DOWN))
		m_pSound->Play(SOUND_ID::MAINSELECT);
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER))
		m_pSound->Play(SOUND_ID::ENTER);
	
	//戦闘の流れ
	switch (m_BattleFase)
	{
		//「OOが現れた」のメッセージ
	case CBattleScene::STARTMESSAGE:		StartMessage();			break;
		//「プレイヤーのターン」のメッセージ
	case CBattleScene::FASECHARAMESSAGE:	FaseCharaMessage();		break;
		//逃げられたか判断するメッセージ
	case CBattleScene::COMMANDMYMESSAGE:	RunMessage();		break;
		//コマンド選択
	case CBattleScene::COMMANDFASE:			SerectBattleCommand();	break;
		//スキル選択
	case CBattleScene::SKILLCOMMAND:		SerectSkill();			break;
		//プレイヤーの攻撃
	case CBattleScene::GAMEFASE:			PlayerAttack();			break;
		//プレイヤーの魔法攻撃
	case CBattleScene::GAMEMAGICFASE:		PlayerMagicAttack();	break;
		//「MPがたりません」のメッセージ
	case CBattleScene::GAMEMAGICFASEMESSAGE:MagicAttackMessage();	break;
		//「敵のターン」のメッセージ
	case CBattleScene::FASEENEMYMESSAGE:	FaseEnemyMessage();		break;
		//敵の攻撃
	case CBattleScene::ENEMYFASE:			EnemyAttack();			break;
		//誰が勝利したかの判断メッセージ
	case CBattleScene::RESULT:				ResultMessage();		break;
		//逃げる、シーンチェンジ
	case CBattleScene::RUNAWAY:				RunAway();				break;
		//どうぐの選択
	case CBattleScene::SELECTTOOL:			SelectTool();			break;
		//どうぐの使用を聞くメッセージ
	case CBattleScene::USETOOL:				UseToolMessage();		break;
		//どうぐの使用
	case CBattleScene::JUDGETOOL:			SelectJudgTool();		break;
		//まほう
	case CBattleScene::MAGIC:				Magic();				break;
	default: break;
	}

	//道具の個数を最新の状態に変更
	m_pInve->m_HealPotionCount = m_pData->GetHealPotionCount();
	m_pInve->m_HealPosionCountLabel.text = std::to_string(m_pInve->m_HealPotionCount);

	//キャラのHP、MP、敵のHPを最新の状態に変更
	m_Hp = m_pData->GetHp();
	m_HpNumber.text = std::to_string(m_Hp);

	m_Mp = m_pData->GetMp();
	m_MpNumber.text = std::to_string(m_Mp);

	m_EnemyHp = m_pData->GetEnemyHp();
	m_EnemyHpNumber.text = std::to_string(m_EnemyHp);

	//コマンド選択時の矢印の動き
	m_Flame += 2.0f;
	m_Serect.scale.y = sin(m_Flame * DX_PI_F / 90.0f);

	//回復薬の位置
	if (m_BattleFase == CBattleScene::SELECTTOOL)
	{
		m_pInve->m_HealPosionLabel.color.alpha = 0xff;
		m_pInve->m_HealPosionCountLabel.color.alpha = 0xff;
		m_pInve->m_HealPosionLabel.position = m_pSkill->SkillPos(1);
		m_pInve->m_HealPosionCountLabel.position =
			aqua::CVector2(m_pInve->m_HealPosionLabel.position.x + m_pInve->m_HealPosionLabel.GetTextWidth(),
				m_pInve->m_HealPosionLabel.position.y);
	}

	//コマンド選択時の矢印の位置判断
	if (m_BattleFase == CBattleScene::COMMANDFASE ||
		m_BattleFase == CBattleScene::SKILLCOMMAND ||
		m_BattleFase == BATTLE_FASE::MAGIC ||
		m_BattleFase == CBattleScene::SELECTTOOL
		)
	{
		if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::LEFT))
			m_ReftFlag = false;
		if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::RIGHT))
			m_ReftFlag = true;
		if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::UP))
			m_DownFlag = false;
		if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::DOWN))
			m_DownFlag = true;
	}
	else if (m_BattleFase == CBattleScene::JUDGETOOL)
	{
		if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::LEFT))
			m_ReftFlag = false;
		if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::RIGHT))
			m_ReftFlag = true;
	}

	IGameObject::Update();
}

void
CBattleScene::
Draw(void)
{
	m_BackgourndSprite.Draw();

	m_CommandSprite.Draw();
	m_CommandSprite2.Draw();
	m_CommandSprite3.Draw();
	m_CommandSprite4.Draw();

	if (m_BattleFase == CBattleScene::SKILLCOMMAND ||
		m_BattleFase == BATTLE_FASE::MAGIC)
	{
		m_SkillPower.Draw();
		m_SkillPowerNum.Draw();
	}

	m_MpLabel.Draw();
	m_MpNumber.Draw();
	m_HpLabel.Draw();
	m_HpNumber.Draw();

	m_EnemyName.Draw();

	m_EnemyHpLabel.Draw();
	m_EnemyHpNumber.Draw();

	m_EnemyLvLabel.Draw();
	m_EnemyLvNumber.Draw();

	if (m_BattleFase == BATTLE_FASE::JUDGETOOL)
	{
		m_Yes.Draw();
		m_No.Draw();
	}

	if (m_BattleFase == CBattleScene::COMMANDFASE ||
		m_BattleFase == CBattleScene::SKILLCOMMAND ||
		m_BattleFase == BATTLE_FASE::SELECTTOOL ||
		m_BattleFase == BATTLE_FASE::MAGIC ||
		m_BattleFase == BATTLE_FASE::JUDGETOOL)
	{
		m_Serect.Draw();
	}

	if (m_BattleFase == BATTLE_FASE::COMMANDFASE)
	{
		m_Battle.Draw();
		m_RunAway.Draw();
		m_Tool.Draw();
		m_Magic.Draw();
	}

	if (m_BattleFase == BATTLE_FASE::SKILLCOMMAND)
	{
		m_BodyBrow.Draw();
		m_Kick.Draw();
		m_Punch.Draw();
		m_Sad.Draw();
	}

	if (m_BattleFase == BATTLE_FASE::MAGIC)
	{
		m_Fire.Draw();
		m_Thunder.Draw();
		m_Bom.Draw();
		m_Blizzard.Draw();

		m_SkillMp.Draw();
		m_SkillMpNum.Draw();
	}

	if (m_BattleFase == BATTLE_FASE::SELECTTOOL)
	{
		m_pInve->m_HealPosionLabel.Draw();
		m_pInve->m_HealPosionCountLabel.Draw();

		m_UseTool.Draw();

		m_HealNumLabel.Draw();
		m_HealNumCount.Draw();
	}

	IGameObject::Draw();
}

void
CBattleScene::
Finalize(void)
{
	m_BackgourndSprite.Delete();

	m_CommandSprite.Delete();
	m_CommandSprite2.Delete();
	m_CommandSprite3.Delete();
	m_CommandSprite4.Delete();

	m_SkillPower.Delete();
	m_SkillMp.Delete();

	m_SkillMpNum.Delete();

	m_MpLabel.Delete();
	m_MpNumber.Delete();
	m_HpLabel.Delete();
	m_HpNumber.Delete();

	m_EnemyName.Delete();
	m_EnemyHpLabel.Delete();
	m_EnemyHpNumber.Delete();

	m_EnemyLvLabel.Delete();
	m_EnemyLvNumber.Delete();

	m_Serect.Delete();

	m_HealNumLabel.Delete();
	m_HealNumCount.Delete();

	m_Battle.Delete();
	m_RunAway.Delete();
	m_Magic.Delete();
	m_Tool.Delete();

	m_BodyBrow.Delete();
	m_Kick.Delete();
	m_Punch.Delete();
	m_Sad.Delete();

	m_Fire.Delete();
	m_Thunder.Delete();
	m_Bom.Delete();
	m_Blizzard.Delete();

	m_Yes.Delete();
	m_No.Delete();

	m_UseTool.Delete();

	IGameObject::Finalize();
}

void CBattleScene::PopEnemy(void)
{
	int x = (int)((m_pData->GetCharaPos().x + 1.0f) / (float)m_pStage->m_map_chip_size);
	int y = (int)((m_pData->GetCharaPos().y + 1.0f) / (float)m_pStage->m_map_chip_size);

	//現在のキャラの位置を調べる
	m_pStage->CheckTile(x, y);

	/*
	* ボスに触れてバトルになったときはボスを生成する
	* ボス以外のエネミーの生成はキャラの場所によって変える
	*/
	if (m_pStage->m_DardFlag_A == true)
		m_pEm->m_EnemyNumber = (int)ENEMY_ID::REDDEMON;
	if (m_pStage->m_DardFlag_B == true)
		m_pEm->m_EnemyNumber = (int)ENEMY_ID::CATCOIN;
	if (m_pStage->m_SandFlag_A == true)
		m_pEm->m_EnemyNumber = (int)ENEMY_ID::CHESTHANDS;
	if (m_pStage->m_SandFlag_B == true)
		m_pEm->m_EnemyNumber = (int)ENEMY_ID::INITIALIZE;
	if (m_pData->GetBossFlag() == true)
		m_pEm->m_EnemyNumber = (int)ENEMY_ID::BOSS;

	switch (m_pEm->m_EnemyNumber)
	{
	case 0:m_pEm->Create(ENEMY_ID::REDDEMON); break;
	case 1:m_pEm->Create(ENEMY_ID::CATCOIN); break;
	case 2:m_pEm->Create(ENEMY_ID::CHESTHANDS); break;
	case 6:m_pEm->Create(ENEMY_ID::BOSS); break;
	default:
		break;
	}
}

void CBattleScene::HealHp(void)
{
	//HPを回復する
	m_Hp = m_pData->GetHp() + m_HealNum;
	m_pData->SetHp(m_Hp);
	m_HpNumber.text = std::to_string(m_Hp);

	//回復薬の個数を1つ消費する
	m_pChara->UseHealPotion();
}

void CBattleScene::StartMessage(void)
{
	if (m_pEm->m_EnemyNumber == (int)ENEMY_ID::REDDEMON)
	{
		m_pComment->ShowText("赤鬼が現れた");
	}
	else if (m_pEm->m_EnemyNumber == (int)ENEMY_ID::CATCOIN)
	{
		m_pComment->ShowText("化け猫が現れた");
	}
	else if (m_pEm->m_EnemyNumber == (int)ENEMY_ID::CHESTHANDS)
	{
		m_pComment->ShowText("悪魔の箱が現れた");
	}
	else if (m_pEm->m_EnemyNumber == (int)ENEMY_ID::BOSS)
	{
		m_pComment->ShowText("ドラゴンが現れた");
	}

	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER) &&
		m_BattleFase == BATTLE_FASE::STARTMESSAGE)
	{
		m_pComment->StepScript();

		if(m_pData->GetCharaSpeed() > m_pData->GetEnemySpeed())
			m_BattleFase = BATTLE_FASE::FASECHARAMESSAGE;
		else
			m_BattleFase = BATTLE_FASE::FASEENEMYMESSAGE;
	}
}

void CBattleScene::FaseCharaMessage(void)
{
	m_pComment->ShowText("自分のターン");

	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER) &&
		m_BattleFase == BATTLE_FASE::FASECHARAMESSAGE)
	{
		m_pComment->StepScript();
		m_BattleFase = BATTLE_FASE::COMMANDFASE;
	}
}

void CBattleScene::FaseEnemyMessage(void)
{
	m_pComment->ShowText("敵のターン");

	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER) &&
		m_BattleFase == BATTLE_FASE::FASEENEMYMESSAGE)
	{
		m_pComment->StepScript();
		m_EnemyAttack = rand() % m_pSkill->m_max_enemy_skill;
		m_pSound->Play(SOUND_ID::DAMAGE);
		m_BattleFase = BATTLE_FASE::ENEMYFASE;
	}
}

void CBattleScene::SerectBattleCommand(void)
{
	//たたかう
	if (!m_ReftFlag && !m_DownFlag)
		m_Serect.position = SellectArrowPos(1);
	//どうぐ
	else if (!m_ReftFlag && m_DownFlag)
		m_Serect.position = SellectArrowPos(2);
	//まほう
	else if (m_ReftFlag && !m_DownFlag)
		m_Serect.position = SellectArrowPos(3);
	//にげる
	else if (m_ReftFlag && m_DownFlag)
		m_Serect.position = SellectArrowPos(4);

	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER) &&
		m_BattleFase == BATTLE_FASE::COMMANDFASE)
	{
		//次のフェーズをフラッグ２つの値で判断する
		if (!m_ReftFlag && !m_DownFlag)
			m_BattleFase = BATTLE_FASE::SKILLCOMMAND;
		else if (!m_ReftFlag && m_DownFlag)
			m_BattleFase = BATTLE_FASE::SELECTTOOL;
		else if (m_ReftFlag && !m_DownFlag)
			m_BattleFase = BATTLE_FASE::MAGIC;
		else if (m_ReftFlag && m_DownFlag)
		{
			if (m_pEm->m_EnemyNumber != (int)ENEMY_ID::BOSS)
				m_RandRun = rand() % 4;
			else
			{
				m_RandRun = 1;
			}
			m_BattleFase = BATTLE_FASE::COMMANDMYMESSAGE;
		}

		m_ReftFlag = false;
		m_DownFlag = false;
	}
}

void CBattleScene::RunMessage(void)
{
	if (m_RandRun == 0)
	{
		m_pComment->ShowText("うまく逃げられた");
	}
	else if (m_RandRun != 0 || m_pEm->m_EnemyNumber == (int)ENEMY_ID::BOSS)
	{
		m_pComment->ShowText("逃げられなかった");
	}

	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER) &&
		m_BattleFase == BATTLE_FASE::COMMANDMYMESSAGE)
	{
		m_pComment->StepScript();
		m_BattleFase = BATTLE_FASE::RUNAWAY;
	}
}

void CBattleScene::SerectSkill(void)
{
	m_pSkill->Initialize();
	m_pSkill->Updata();

	//それぞれの技の名前とポジションを代入する
	m_BodyBrow.text = m_pSkill->m_SkillCharaName[0];
	m_BodyBrow.position = m_pSkill->m_SkillCharaPos[0];

	m_Punch.text = m_pSkill->m_SkillCharaName[1];
	m_Punch.position = m_pSkill->m_SkillCharaPos[1];

	m_Sad.text = m_pSkill->m_SkillCharaName[2];
	m_Sad.position = m_pSkill->m_SkillCharaPos[2];

	m_Kick.text = m_pSkill->m_SkillCharaName[3];
	m_Kick.position = m_pSkill->m_SkillCharaPos[3];

	//矢印の位置によってm_SkillNumに入れる番号を変える
	if (!m_ReftFlag && !m_DownFlag)
		m_pSkill->CheckSkillNum(1);
	else if (!m_ReftFlag && m_DownFlag)
		m_pSkill->CheckSkillNum(2);
	else if (m_ReftFlag && !m_DownFlag)
		m_pSkill->CheckSkillNum(3);
	else if (m_ReftFlag && m_DownFlag)
		m_pSkill->CheckSkillNum(4);

	//入れられたm_SkillNumの番号と同じスキルのIDを調べ攻撃力を表示する
	for (int i = 0; i < m_pSkill->m_max_chara_skill; ++i)
	{
		if (m_pSkill->m_SkillNum == m_pSkill->m_SkillCharaId[i])
		{
			m_SkillPowerNum.text = std::to_string((int)m_pSkill->m_SkillCharaDamage[i]);
		}
	}

	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER) &&
		m_BattleFase == BATTLE_FASE::SKILLCOMMAND)
	{
		m_pSound->Play(SOUND_ID::ATTACK);
		m_BattleFase = BATTLE_FASE::GAMEFASE;

		m_ReftFlag = false;
		m_DownFlag = false;
	}
	//ひとつ前のフェーズに戻る
	else if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::B) &&
		m_BattleFase == BATTLE_FASE::SKILLCOMMAND)
	{
		m_pSound->Play(SOUND_ID::BACK);
		m_BattleFase = BATTLE_FASE::COMMANDFASE;

		m_ReftFlag = false;
		m_DownFlag = false;
	}
}

void CBattleScene::Magic(void)
{
	m_pSkill->Initialize();
	m_pSkill->Updata();

	//それぞれの技の名前とポジションを代入する
	m_Fire.text = m_pSkill->m_MagicCharaName[0];
	m_Fire.position = m_pSkill->m_MagicCharaPos[0];

	m_Thunder.text = m_pSkill->m_MagicCharaName[1];
	m_Thunder.position = m_pSkill->m_MagicCharaPos[1];

	m_Bom.text = m_pSkill->m_MagicCharaName[2];
	m_Bom.position = m_pSkill->m_MagicCharaPos[2];

	m_Blizzard.text = m_pSkill->m_MagicCharaName[3];
	m_Blizzard.position = m_pSkill->m_MagicCharaPos[3];

	//矢印の位置によってm_MagicNumに入れる番号を変える
	if (!m_ReftFlag && !m_DownFlag)
		m_pSkill->CheckMagicNum(1);
	else if (!m_ReftFlag && m_DownFlag)
		m_pSkill->CheckMagicNum(2);
	else if (m_ReftFlag && !m_DownFlag)
		m_pSkill->CheckMagicNum(3);
	else if (m_ReftFlag && m_DownFlag)
		m_pSkill->CheckMagicNum(4);

	//入れられたm_MagicNumの番号と同じスキルのIDを調べ攻撃力と消費MPを表示する
	for (int j = 0; j < m_pSkill->m_max_chara_magic; ++j)
	{
		if (m_pSkill->m_MagicNum == m_pSkill->m_MagicCharaId[j])
		{
			m_SkillPowerNum.text = std::to_string((int)m_pSkill->m_MagicCharaDamage[j]);
			m_SkillMpNum.text = std::to_string((int)m_pSkill->m_MagicCharaMp[j]);
		}
	}

	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER) &&
		m_BattleFase == BATTLE_FASE::MAGIC)
	{
		//入れられたm_MagicNumの番号と同じスキルのIDを調べMPの量に応じてフェーズを変える
		for (int j = 0; j < m_pSkill->m_max_chara_magic; ++j)
		{
			if (m_pSkill->m_MagicNum == m_pSkill->m_MagicCharaId[j])
			{
				if (m_pData->GetMp() >= m_pSkill->m_MagicCharaMp[j])
				{
					m_pSound->Play(SOUND_ID::MAGIC);
					m_BattleFase = BATTLE_FASE::GAMEMAGICFASE;
				}
				else
				{
					m_BattleFase = BATTLE_FASE::GAMEMAGICFASEMESSAGE;
				}
			}
		}

		m_ReftFlag = false;
		m_DownFlag = false;
	}
	//ひとつ前のフェーズに戻る
	else if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::B))
	{
		m_pSound->Play(SOUND_ID::BACK);
		m_BattleFase = BATTLE_FASE::COMMANDFASE;

		m_ReftFlag = false;
		m_DownFlag = false;
	}
}

void CBattleScene::PlayerAttack(void)
{
	//入れられたm_SkillNumの番号と同じスキルのIDを調べ攻撃する
	for (int i = 0; i < m_pSkill->m_max_chara_skill; ++i)
	{
		if (m_pSkill->m_SkillNum == m_pSkill->m_SkillCharaId[i])
		{
			if (m_CheckFlagEnemy == false)
			{
				m_Damage = (((m_pData->GetCharaLv() * 2 / 5 + 2) * (m_pSkill->m_SkillCharaDamage[i] *
					((float)m_pData->GetCharaStren() / (float)m_pData->GetEnemyDefen())) / 50 + 2) *
					(float)(aqua::Rand(100, 85)) / 100.0f);

				m_EnemyHp = m_pData->GetEnemyHp() - m_Damage;

				if (m_EnemyHp <= 0)
				{
					m_EnemyHp = 0;
					m_pData->SetEnemyHp(0);
				}

				m_pData->SetEnemyHp(m_EnemyHp);
				m_CheckFlagEnemy = true;
			}

			m_pComment->ShowText("プレイヤーは" + std::to_string(m_Damage) + "ダメージを与えた");
		}
	}

	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER) &&
		m_BattleFase == BATTLE_FASE::GAMEFASE)
	{
		if (m_EnemyHp <= 0)
		{
			m_pComment->StepScript();
			m_BattleFase = BATTLE_FASE::RESULT;
		}
		else
		{
			m_CheckFlagEnemy = false;
			m_pComment->StepScript();
			m_BattleFase = BATTLE_FASE::FASEENEMYMESSAGE;
		}
	}
}

void CBattleScene::PlayerMagicAttack(void)
{
	//入れられたm_MagicNumの番号と同じスキルのIDを調べ攻撃する
	for (int j = 0; j < m_pSkill->m_max_chara_magic; ++j)
	{
		if (m_pSkill->m_MagicNum == m_pSkill->m_MagicCharaId[j])
		{
			if (m_CheckFlagEnemy == false)
			{
				if (m_pData->GetMp() - m_pSkill->m_MagicCharaMp[j] >= 0)
				{
					m_Mp = m_pData->GetMp() - m_pSkill->m_MagicCharaMp[j];
					m_pData->SetMp(m_Mp);

					m_Damage = (((m_pData->GetCharaLv() * 2 / 5 + 2) * (m_pSkill->m_MagicCharaDamage[j] *
						((float)m_pData->GetCharaStren() / (float)m_pData->GetEnemyDefen())) / 50 + 2) *
						(float)(aqua::Rand(100, 85)) / 100.0f);
					
					m_EnemyHp = m_pData->GetEnemyHp() - m_Damage;

					if (m_EnemyHp <= 0)
					{
						m_EnemyHp = 0;
						m_pData->SetEnemyHp(0);
					}

					m_pData->SetEnemyHp(m_EnemyHp);
					m_CheckFlagEnemy = true;
				}
			}

			m_pComment->ShowText("プレイヤーは" + std::to_string(m_Damage) + "ダメージを与えた");
		}
	}

	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER) &&
		m_BattleFase == BATTLE_FASE::GAMEMAGICFASE)
	{
		if (m_EnemyHp <= 0)
		{
			m_pComment->StepScript();
			m_BattleFase = BATTLE_FASE::RESULT;
		}
		else
		{
			m_CheckFlagEnemy = false;
			m_pComment->StepScript();

			m_BattleFase = BATTLE_FASE::FASEENEMYMESSAGE;
		}
	}
}

void CBattleScene::MagicAttackMessage(void)
{
	m_pComment->ShowText("MPがたりません");

	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER) &&
		m_BattleFase == BATTLE_FASE::GAMEMAGICFASEMESSAGE)
	{
		m_pComment->StepScript();
		m_BattleFase = BATTLE_FASE::MAGIC;
	}
}

void CBattleScene::EnemyAttack(void)
{
	std::string name;

	if (m_pEm->m_EnemyNumber == (int)ENEMY_ID::REDDEMON)
		name = "赤鬼は";
	if (m_pEm->m_EnemyNumber == (int)ENEMY_ID::CATCOIN)
		name = "化け猫は";
	if (m_pEm->m_EnemyNumber == (int)ENEMY_ID::CHESTHANDS)
		name = "悪魔の箱は";
	if (m_pEm->m_EnemyNumber == (int)ENEMY_ID::BOSS)
		name = "ドラゴンは";

	//ランダムな番号(m_EnemyAttack)を技の覧から探し攻撃力を参照しプレイヤーを攻撃する
	for (int i = 0; i < m_pSkill->m_max_enemy_skill; i++)
	{
		if (m_EnemyAttack == i)
		{
			if (m_CheckFlagChara == false)
			{
				m_Damage = (((m_pData->GetEnemyLv() * 2 / 5 + 2) * (m_pSkill->m_EnemySkill[i].damage *
					((float)m_pData->GetEnemyStren() / (float)m_pData->GetCharaDefen())) / 50 + 2) *
					(float)(aqua::Rand(100, 85)) / 100.0f);

				m_Hp = m_pData->GetHp() - m_Damage;

				if (m_Hp <= 0)
				{
					m_Hp = 0;
					m_pData->SetHp(m_Hp);
				}

				m_pData->SetHp(m_Hp);
				m_CheckFlagChara = true;
			}

			m_pComment->ShowText(name + std::to_string(m_Damage) + "ダメージを与えた");
		}
	}

	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER) &&
		m_BattleFase == BATTLE_FASE::ENEMYFASE)
	{
		if (m_Hp <= 0)
		{
			m_pComment->StepScript();
			m_BattleFase = BATTLE_FASE::RESULT;
		}
		else
		{
			m_CheckFlagChara = false;
			m_pComment->StepScript();
			m_BattleFase = BATTLE_FASE::FASECHARAMESSAGE;
		}
	}
}

void CBattleScene::ResultMessage(void)
{
	if (m_Hp == 0)
	{
		if (m_SeFlag == false)
		{
			m_pSound->Play(SOUND_ID::LOSE);
			m_SeFlag = true;
		}

		m_pComment->ShowText("敵の勝利です........");

		if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER) &&
			m_BattleFase == BATTLE_FASE::RESULT)
		{
			m_pComment->StepScript();
			m_pSound->Stop(SOUND_ID::BATTLEBGM);
			Change(SCENE_ID::GAMEOVER);
			m_pData->SetBossFlag(false);
			m_BattleFase = BATTLE_FASE::STARTMESSAGE;
		}
	}
	else
	{
		if (m_pEm->m_EnemyNumber == (int)ENEMY_ID::BOSS)
		{
			if (m_SeFlag == false)
			{
				m_pSound->Play(SOUND_ID::WIN);
				m_SeFlag = true;
			}

			m_pComment->ShowText("ゲームクリア！！！");

			if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER) &&
				m_BattleFase == BATTLE_FASE::RESULT)
			{
				m_pComment->StepScript();
				m_pSound->Stop(SOUND_ID::BATTLEBGM);
				Change(SCENE_ID::GAMECLEAR);
				m_pData->SetBossFlag(false);
				m_BattleFase = BATTLE_FASE::STARTMESSAGE;
			}
		}
		else
		{
			if (m_SeFlag == false)
			{
				m_pSound->Play(SOUND_ID::WIN);
				m_SeFlag = true;
			}

			m_pComment->ShowText("プレイヤーの勝利です");

			if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER) &&
				m_BattleFase == BATTLE_FASE::RESULT)
			{
				m_pComment->StepScript();
				m_pSound->Stop(SOUND_ID::BATTLEBGM);
				Change(SCENE_ID::GAMEMAIN);
				m_SeFlag = false;
				m_BattleFase = BATTLE_FASE::STARTMESSAGE;
			}
		}
	}
}

void CBattleScene::RunAway(void)
{
	if (m_RandRun == 0)
	{
		m_pSound->Play(SOUND_ID::RUNAWAY);
		m_pSound->Stop(SOUND_ID::BATTLEBGM);
		Change(SCENE_ID::GAMEMAIN);
	}
	else
	{
		m_pComment->StepScript();
		m_BattleFase = BATTLE_FASE::COMMANDFASE;
	}
}

void CBattleScene::SelectTool(void)
{
	if (!m_ReftFlag && !m_DownFlag)
		m_Serect.position = SellectArrowPos(1);
	else if (!m_ReftFlag && m_DownFlag)
		m_Serect.position = SellectArrowPos(2);
	else if (m_ReftFlag && !m_DownFlag)
		m_Serect.position = SellectArrowPos(3);
	else if (m_ReftFlag && m_DownFlag)
		m_Serect.position = SellectArrowPos(4);

	//回復薬を選択したら次のフェーズへ移行する
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER) &&
		m_BattleFase == BATTLE_FASE::SELECTTOOL)
	{
		if (!m_ReftFlag && !m_DownFlag)
			m_UseTool.text = "回復薬";

		m_BattleFase = BATTLE_FASE::USETOOL;
	}
	//ひとつ前のフェーズに戻る
	else if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::B) &&
		m_BattleFase == BATTLE_FASE::SELECTTOOL)
	{
		m_BattleFase = BATTLE_FASE::COMMANDFASE;

		m_ReftFlag = false;
		m_DownFlag = false;
	}
}

void CBattleScene::UseToolMessage(void)
{
	//アイテムを使用するかの判断をする
	if (!m_ReftFlag && !m_DownFlag)
	{
		m_pComment->ShowText("回復薬を使いますか？");

		if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER) &&
			m_BattleFase == BATTLE_FASE::USETOOL)
		{
			m_pComment->StepScript();
			m_BattleFase = BATTLE_FASE::JUDGETOOL;

			m_ReftFlag = false;
			m_DownFlag = true;
		}
	}
}

void CBattleScene::SelectJudgTool(void)
{
	if (!m_ReftFlag && m_DownFlag)
		m_Serect.position = SellectArrowPos(2);
	else if (m_ReftFlag && m_DownFlag)
		m_Serect.position = SellectArrowPos(4);

	//はいを選択したらコメントを出しアクションする
	if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER) &&
		m_BattleFase == BATTLE_FASE::JUDGETOOL)
	{
		if (m_pData->GetHealPotionCount() <= 0)
			m_Serect.position = SellectArrowPos(4);

		if (m_Serect.position == SellectArrowPos(2))
		{
			m_pComment->ShowText("回復薬を使いました");

			if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER) &&
				m_BattleFase == BATTLE_FASE::JUDGETOOL)
			{
				m_pComment->StepScript();

				m_pSound->Play(SOUND_ID::HEAL);
				HealHp();

				m_BattleFase = BATTLE_FASE::FASEENEMYMESSAGE;

				m_ReftFlag = false;
				m_DownFlag = false;
			}
		}
		else if (m_Serect.position == SellectArrowPos(4))
		{
			m_pComment->ShowText("回復薬を使いませんでした");

			if (aqua::keyboard::Trigger(aqua::keyboard::KEY_ID::NUMPADENTER) &&
				m_BattleFase == BATTLE_FASE::JUDGETOOL)
			{
				m_pComment->StepScript();
				m_BattleFase = BATTLE_FASE::SELECTTOOL;

				m_ReftFlag = false;
				m_DownFlag = false;
			}
		}
	}
}

aqua::CVector2 CBattleScene::SellectArrowPos(int sele_aro_pos)
{
	//矢印のポジション
	aqua::CVector2 select_arrow_1 = { m_CommandSprite.position.x + 100.0f - m_Serect.GetTextureWidth() ,
		m_CommandSprite.position.y + 100.0f };
	aqua::CVector2 select_arrow_2 = { m_CommandSprite.position.x + 100.0f - m_Serect.GetTextureWidth(),
			m_CommandSprite.position.y + m_CommandSprite.GetTextureHeight() - 200.0f };
	aqua::CVector2 select_arrow_3 = { m_Battle.position.x + m_Battle.GetTextWidth() * 3 - m_Serect.GetTextureWidth() ,
		m_CommandSprite.position.y + 100.0f };
	aqua::CVector2 select_arrow_4 = { m_Battle.position.x + m_Battle.GetTextWidth() * 3 - m_Serect.GetTextureWidth(),
			m_CommandSprite.position.y + m_CommandSprite.GetTextureHeight() - 200.0f };

	if (sele_aro_pos == 1)
		return select_arrow_1;
	else if (sele_aro_pos == 2)
		return  select_arrow_2;
	else if (sele_aro_pos == 3)
		return  select_arrow_3;
	else if (sele_aro_pos == 4)
		return  select_arrow_4;
}