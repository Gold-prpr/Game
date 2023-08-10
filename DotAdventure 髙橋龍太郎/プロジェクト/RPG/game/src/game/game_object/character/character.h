#pragma once
#include "aqua.h"
#include "../map/map.h"
#include "../map/item/item.h"
#include "../Inventory/Inventory.h"
#include "../data/data.h"
#include "../enemy_manager/enemy/enemy.h"
#include "../skill/skill.h"
#include "../comment_viewer/comment_viewer.h"
#include "../enemy_manager/enemy_manager.h"
#include "../enemy_manager/enemy/boss/boss.h"
#include "../scroll/scroll.h"
#include "../sound_manager/sound_manager.h"

class CSoundManager;
class CBoss;
class CStage;
class CItem;
class CInventory;
class CData;
class IEnemy;
class CSkill;
class CCommand;
class CEnemyManager;
class CScroll;

class CCharacter
	: public aqua::IGameObject
{
public:
	CCharacter(aqua::IGameObject* parent);
	~CCharacter() = default;

	void Initialize(void) override;

	void Update(void) override;

	void Draw(void) override;

	void Finalize(void) override;

	void MoveCharacter(void);

	void WaitCharacter(void);

	void GoldCount(void);

	void KeyCount(void);

	void UseKeyCount(void);

	void HealPotion(void);

	void UseHealPotion(void);

	void CheckChest(int x, int y);

	void CheckItem(int x, int y);

	bool IsEncount(void) const;

	void EncountReset(void);

	void WalkSound(void);

	void StopWalkSound(void);

	void EncuntCounterCheck(void);

	void CheckBoss(void);

	void OpenBox(int x, int y);

	struct STATUS
	{
		int level;
		int hp;
		int mp;
		int strength;
		int defense;
		int speed;
	};

	STATUS m_CharaStatus;

	aqua::CAnimationSprite m_Chara; //キャラクターのスプライト

	int m_Life; //キャラクターのライフ

	int m_Encount = 0; //エンカウント値

	bool m_BossFlag; //ボスの当たり判定フラッグ

private:

	enum CHARA_DIRECTION
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};

	CHARA_DIRECTION m_DirCurrent; //今の向き
	CHARA_DIRECTION m_DirNext; //次の向き

	static const int m_character_width; //キャラクターの幅
	static const int m_character_height; //キャラクターの高さ

	int m_CharaMoveTimer; //１マス進むまでにかかる時間
	static const int m_chara_timer;//１マス進むときのフレーム

	int m_CharaMoveSpeed; //キャラの移動量を求める値
	aqua::CVector2 m_CharaSpeed; //キャラの速さ
	aqua::CVector2 m_CharaPos; //キャラの位置

	aqua::CVector2 m_ScrollCamera; //スクロールの移動量

	int m_GoldCount; //アイテム（金）の数
	int m_KeyCount; //アイテム（鍵）の数
	int m_HealPotion; //アイテム（回復薬）の数

	CSoundManager* m_pSound;
	CStage* m_pStage;
	CItem* m_pItem;
	CInventory* m_pInve;
	CData* m_pData;
	CScroll* m_pScroll;
};