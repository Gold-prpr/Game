#include "map.h"

const int CStage::m_map_chip_size = 80;

const int CStage::m_num_chip_size_x = 10;
const int CStage::m_num_chip_size_y = 2;

const int CStage::m_all_num_chip = m_num_chip_size_x * m_num_chip_size_y;

const int CStage::m_map_x = 48;
const int CStage::m_map_y = 27;

aqua::CCSVLoader loader;

CStage::CStage(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Map")
{
}

void CStage::Initialize(void)
{
	m_pSound = (CSoundManager*)aqua::FindGameObject("SoundManager");
	m_pScroll = (CScroll*)aqua::FindGameObject("Scroll");
	m_pChara = (CCharacter*)aqua::FindGameObject("Character");

	m_TileSprite = AQUA_NEW aqua::CSprite[m_all_num_chip];

	for (int i = 0; i < (int)TILE_ID::MAX; i++)
	{
		m_TileSprite[i].Create("data\\マップ\\土地2.png");

		int cw = i % 10 * m_map_chip_size;
		int ch = i / 10 * m_map_chip_size;

		m_TileSprite[i].rect = aqua::CRect(cw, ch, cw + m_map_chip_size, ch + m_map_chip_size);
	}

	m_StageCsv.Load("data\\マップ\\map.csv");

	for (int y = 0; y < m_StageCsv.GetRows(); y++)
	{
		for (int x = 0; x < m_StageCsv.GetCols(); x++)
		{
			m_MapData.push_back(m_StageCsv.GetInteger(y, x));
		}
	}

	m_StageCsv.Unload();
}

void CStage::Update(void)
{
	//スクロールによってずれたマップの更新

	int sx = (int)m_pScroll->GetScroll().x / m_map_chip_size - 1;

	if (sx < 0) sx = 0;

	int sy = (int)m_pScroll->GetScroll().y / m_map_chip_size - 1;

	if (sy < 0) sy = 0;

	for (int y = sx; y < m_StageCsv.GetRows(); y++)
	{
		for (int x = sy; x < m_StageCsv.GetCols(); x++)
		{
			m_MapData.push_back(m_StageCsv.GetInteger(y, x));
		}
	}
}

void CStage::Draw(void)
{
	//スクロール移動量を引いてタイルのポジション指定

	int i = 0;

	for (auto it = m_MapData.begin(); it != m_MapData.end(); ++it, ++i)
	{
		m_TileSprite[*it].position.x = (float)(i % m_map_x) * 80 - m_pScroll->GetScroll().x;
		m_TileSprite[*it].position.y = (float)(i / m_map_x) * 80 - m_pScroll->GetScroll().y;

		m_TileSprite[*it].Draw();
	}
}

void CStage::Finalize(void)
{
	for (int i = 0; i < (int)TILE_ID::MAX; i++)
		m_TileSprite[i].Delete();

	AQUA_SAFE_DELETE_ARRAY(m_TileSprite);

	m_MapData.clear();
}

bool CStage::CheckWall(int x, int y)
{
	//壁との当たり判定
	if (
		(m_MapData[m_map_x * y + x] == (int)TILE_ID::TREE1) ||
		(m_MapData[m_map_x * y + x] == (int)TILE_ID::TREE2) ||
		(m_MapData[m_map_x * y + x] == (int)TILE_ID::GOLD_BLOCK)
		)
		return true;

	return false;
}

void CStage::CheckTile(int x, int y)
{
	//今いる場所のタイルを調べる
	if (m_MapData[m_map_x * y + x] == (int)TILE_ID::DARD1)
	{
		m_DardFlag_A = true;
		m_DardFlag_B = false;
		m_SandFlag_A = false;
		m_SandFlag_B = false;
	}
	if (m_MapData[m_map_x * y + x] == (int)TILE_ID::DARD2)
	{
		m_DardFlag_A = false;
		m_DardFlag_B = true;
		m_SandFlag_A = false;
		m_SandFlag_B = false;
	}
	if (m_MapData[m_map_x * y + x] == (int)TILE_ID::SAND1)
	{
		m_DardFlag_A = false;
		m_DardFlag_B = false;
		m_SandFlag_A = true;
		m_SandFlag_B = false;
	}
	if (m_MapData[m_map_x * y + x] == (int)TILE_ID::SAND2 ||
		m_MapData[m_map_x * y + x] == (int)TILE_ID::GOLD_WALL)
	{
		m_DardFlag_A = false;
		m_DardFlag_B = false;
		m_SandFlag_A = false;
		m_SandFlag_B = true;
	}
}

int CStage::GetChipSize()
{
	return m_map_chip_size;
}

int CStage::GetChipCountX()
{
	return m_map_x;
}

int CStage::GetChipCountY()
{
	return m_map_y;
}

void CStage::CheckSoundTile(int x, int y)
{
	//今いる場所のタイルを調べる（サウンド用）
	if (m_MapData[m_map_x * y + x] == (int)TILE_ID::DARD1)
	{
		m_DardSe_A = true;
		m_DardSe_B = false;
		m_SandSe_A = false;
		m_SandSe_B = false;
	}
	if (m_MapData[m_map_x * y + x] == (int)TILE_ID::DARD2)
	{
		m_DardSe_A = false;
		m_DardSe_B = true;
		m_SandSe_A = false;
		m_SandSe_B = false;
	}
	if (m_MapData[m_map_x * y + x] == (int)TILE_ID::SAND1 || 
		m_MapData[m_map_x * y + x] == (int)TILE_ID::SAND2)
	{
		m_DardSe_A = false;
		m_DardSe_B = false;
		m_SandSe_A = true;
		m_SandSe_B = false;
	}
	if (m_MapData[m_map_x * y + x] == (int)TILE_ID::GOLD_WALL)
	{
		m_DardSe_A = false;
		m_DardSe_B = false;
		m_SandSe_A = false;
		m_SandSe_B = true;
	}
}
