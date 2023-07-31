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

	aqua::CAnimationSprite m_Chara; //�L�����N�^�[�̃X�v���C�g

	int m_Life; //�L�����N�^�[�̃��C�t

	int m_Encount = 0; //�G���J�E���g�l

	bool m_BossFlag; //�{�X�̓����蔻��t���b�O

private:

	enum CHARA_DIRECTION
	{
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};

	CHARA_DIRECTION m_DirCurrent; //���̌���
	CHARA_DIRECTION m_DirNext; //���̌���

	static const int m_character_width; //�L�����N�^�[�̕�
	static const int m_character_height; //�L�����N�^�[�̍���

	int m_CharaMoveTimer; //�P�}�X�i�ނ܂łɂ����鎞��
	static const int m_chara_timer;//�P�}�X�i�ނƂ��̃t���[��

	int m_CharaMoveSpeed; //�L�����̈ړ��ʂ����߂�l
	aqua::CVector2 m_CharaSpeed; //�L�����̑���
	aqua::CVector2 m_CharaPos; //�L�����̈ʒu

	aqua::CVector2 m_ScrollCamera; //�X�N���[���̈ړ���

	int m_GoldCount; //�A�C�e���i���j�̐�
	int m_KeyCount; //�A�C�e���i���j�̐�
	int m_HealPotion; //�A�C�e���i�񕜖�j�̐�

	CSoundManager* m_pSound;
	CStage* m_pStage;
	CItem* m_pItem;
	CInventory* m_pInve;
	CData* m_pData;
	CScroll* m_pScroll;
};