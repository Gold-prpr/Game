#pragma once
#include "aqua.h"
#include "../data/data.h"
#include "../scene_manager/scene/battle/battle.h"
#include "../sound_manager/sound_manager.h"

class CSoundManager;
class CData;
class CBattleScene;

class CInventory
	: public aqua::IGameObject
{
public:
	CInventory(aqua::IGameObject* parent);

	~CInventory(void) = default;

	void Initialize(void) override;

	void Update(void) override;

	void Draw(void) override;

	void Finalize(void) override;

	void ResetNum(void);

	int m_GoldCount; //金の個数
	int m_KeyCount; //鍵の個数
	int m_HealPotionCount; //回復薬の個数

	aqua::CLabel m_HealPosionLabel; //回復薬の名前ラベル
	aqua::CLabel m_HealPosionCountLabel; //回復薬の個数ラベル

	bool m_BsFlag; //インベントリー画面のフラッグ

private:
	aqua::CSprite m_InveBs; //インベントリーのスプライト

	aqua::CLabel m_GoldLabel; //金の名前ラベル
	aqua::CLabel m_GoldCountLabel; //金の個数ラベル

	aqua::CLabel m_KeyLabel; //鍵の名前ラベル
	aqua::CLabel m_KeyCountLabel; //鍵の個数ラベル

	CSoundManager* m_pSound;
	CData* m_pData;
	CBattleScene* m_pBattle;
};