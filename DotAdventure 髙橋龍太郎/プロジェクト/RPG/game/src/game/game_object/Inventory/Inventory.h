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

	int m_GoldCount; //���̌�
	int m_KeyCount; //���̌�
	int m_HealPotionCount; //�񕜖�̌�

	aqua::CLabel m_HealPosionLabel; //�񕜖�̖��O���x��
	aqua::CLabel m_HealPosionCountLabel; //�񕜖�̌����x��

	bool m_BsFlag; //�C���x���g���[��ʂ̃t���b�O

private:
	aqua::CSprite m_InveBs; //�C���x���g���[�̃X�v���C�g

	aqua::CLabel m_GoldLabel; //���̖��O���x��
	aqua::CLabel m_GoldCountLabel; //���̌����x��

	aqua::CLabel m_KeyLabel; //���̖��O���x��
	aqua::CLabel m_KeyCountLabel; //���̌����x��

	CSoundManager* m_pSound;
	CData* m_pData;
	CBattleScene* m_pBattle;
};