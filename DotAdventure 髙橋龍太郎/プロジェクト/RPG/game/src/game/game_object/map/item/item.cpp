#include "item.h"

const int CItem::m_map_chip_size_item = 80;

const int CItem::m_num_chip_size_x_item = 10;
const int CItem::m_num_chip_size_y_item = 2;

const int CItem::m_all_num_chip_item = m_num_chip_size_x_item * m_num_chip_size_y_item;

const int CItem::m_map_x_item = 48;
const int CItem::m_map_y_item = 48;

aqua::CCSVLoader loader_m_pItem;

CItem::CItem(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "Item")
{
}

void CItem::Initialize(void)
{
	m_pScroll = (CScroll*)aqua::FindGameObject("Scroll");

	m_ItemSprite = AQUA_NEW aqua::CSprite[m_all_num_chip_item];

	for (int i = 0; i < m_all_num_chip_item; i++)
	{
		m_ItemSprite[i].Create("data\\マップ\\Item2.png");

		int cw = i % 10 * m_map_chip_size_item;
		int ch = i / 10 * m_map_chip_size_item;

		m_ItemSprite[i].rect = aqua::CRect(cw, ch, cw + m_map_chip_size_item, ch + m_map_chip_size_item);
	}

	m_ItemCsv.Load("data\\マップ\\Item.csv");

	for (int y = 0; y < m_ItemCsv.GetRows(); y++)
	{
		for (int x = 0; x < m_ItemCsv.GetCols(); x++)
		{
			m_ItemData.push_back(m_ItemCsv.GetInteger(y, x));
		}
	}

	m_ItemCsv.Unload();
}

void CItem::Update(void)
{
	//スクロールによってずれたアイテムの更新
	int sx = (int)m_pScroll->GetScroll().x / m_map_chip_size_item - 1;

	if (sx < 0) sx = 0;

	int sy = (int)m_pScroll->GetScroll().y / m_map_chip_size_item - 1;

	if (sy < 0) sy = 0;

	for (int y = sx; y < m_ItemCsv.GetRows(); y++)
	{
		for (int x = sy; x < m_ItemCsv.GetCols(); x++)
		{
			m_ItemData.push_back(m_ItemCsv.GetInteger(y, x));
		}
	}
}

void CItem::Draw(void)
{
	//スクロール移動量を引いてアイテムのポジション指定
	int i = 0;
	for (auto it = m_ItemData.begin(); it != m_ItemData.end(); ++it, ++i)
	{
		m_ItemSprite[*it].position.x = (float)(i % m_map_x_item) * 80 - m_pScroll->GetScroll().x;
		m_ItemSprite[*it].position.y = (float)(i / m_map_y_item) * 80 - m_pScroll->GetScroll().y;

		m_ItemSprite[*it].Draw();
	}
}

void CItem::Finalize(void)
{
	for (int i = 0; i < m_all_num_chip_item; i++)
		m_ItemSprite[i].Delete();

	AQUA_SAFE_DELETE_ARRAY(m_ItemSprite);

	m_ItemData.clear();

	IGameObject::Finalize();
}

bool CItem::CheckChest(int x, int y)
{
	if ((m_ItemData[m_map_x_item * y + x] == (int)ITEM_ID::TREASURECHEST1))
		return true;
	else
		return false;
}

bool CItem::CheckGoldItem(int x, int y)
{
	if ((m_ItemData[m_map_x_item * y + x] == (int)ITEM_ID::GOLD_INGOT))
		return true;
	else
		return false;
}

bool CItem::CheckKeyItem(int x, int y)
{
	if (m_ItemData[m_map_x_item * y + x] == (int)ITEM_ID::KEY)
		return true;
	else
		return false;
}

bool CItem::CheckHealPotionItem(int x, int y)
{
	if (m_ItemData[m_map_x_item * y + x] == (int)ITEM_ID::PORSION)
		return true;
	else
		return false;
}

void CItem::ChangeAir(int x, int y)
{
	m_ItemData[m_map_x_item * y + x] = (int)ITEM_ID::AIR;
}

bool CItem::CheckItemWall(int x, int y)
{
	if ((m_ItemData[m_map_x_item * y + x] == (int)ITEM_ID::TREASURECHEST1) ||
		(m_ItemData[m_map_x_item * y + x] == (int)ITEM_ID::TREASURECHEST2) ||
		(m_ItemData[m_map_x_item * y + x] == (int)ITEM_ID::BOSSPOSITION))
		return true;

	return false;
}

bool CItem::CheckBoss(int x, int y)
{
	if (m_ItemData[m_map_x_item * y + x] == (int)ITEM_ID::BOSSPOSITION)
		return true;

	return false;
}

int CItem::GetMapTile(void)
{
	return m_map_x_item;
}
