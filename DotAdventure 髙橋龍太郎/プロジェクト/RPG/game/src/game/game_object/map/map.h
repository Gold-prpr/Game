#pragma once
#include "aqua.h"
#include "tile_id.h"
#include "../character/character.h"
#include "../scroll/scroll.h"
#include "../sound_manager/sound_manager.h"

class CSoundManager;
class CCharacter;
class CScroll;

class CStage
	: public aqua::IGameObject
{
public:

	CStage(aqua::IGameObject* parent);
	~CStage() = default;

	void Initialize(void);
	void Update(void);
	void Draw(void);
	void Finalize(void);

	bool CheckWall(int x, int y);

	void CheckTile(int x, int y);

	int GetChipSize();

	int GetChipCountX();

	int GetChipCountY();

	void CheckSoundTile(int x, int y);

	static const int m_map_chip_size; //�^�C���̑傫��

	bool m_DardFlag_A = false; //���u���b�N�i�^�C��ID�F�O�j
	bool m_DardFlag_B = false; //���u���b�N�i�^�C��ID�F�P�j

	bool m_SandFlag_A = false; //�y�u���b�N�i�^�C��ID�F�Q�j
	bool m_SandFlag_B = false; //�y�u���b�N�i�^�C��ID�F�R�j�Ƌ��ǃu���b�N�i�^�C��ID�F�P�X�j

	bool m_DardSe_A = false; //���u���b�N�i�^�C��ID�F�O�j
	bool m_DardSe_B = false; //���u���b�N�i�^�C��ID�F�P�j

	bool m_SandSe_A = false; ////�y�u���b�N�i�^�C��ID�F�Q�j��//�y�u���b�N�i�^�C��ID�F�R�j
	bool m_SandSe_B = false; //���ǃu���b�N�i�^�C��ID�F�P�X�j

	std::vector<int> m_MapData; //�}�b�v�̃f�[�^�z��

private:

	static const int m_num_chip_size_x; //�摜�ɔz�u���ꂽ�^�C���̉��̐�
	static const int m_num_chip_size_y; //�摜�ɔz�u���ꂽ�^�C���̏c�̐�

	static const int m_all_num_chip; //�摜�ɔz�u���ꂽ�^�C���̍��v

	static const int m_map_x; //�}�b�v�̉��̃^�C���̐�
	static const int m_map_y; //�}�b�v�̏c�̃^�C���̐�

	aqua::CSprite* m_TileSprite; //�^�C���̃X�v���C�g

	aqua::CCSVLoader m_StageCsv; //�X�e�[�W��CSV
	
	CSoundManager* m_pSound;
	CCharacter* m_pChara;
	CScroll* m_pScroll;
};