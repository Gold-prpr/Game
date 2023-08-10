#pragma once
#include "aqua.h"
#include "item_id.h"
#include "../../character/character.h"
#include "../../scroll/scroll.h"

class CCharacter;
class CScroll;

class CItem
	: public aqua::IGameObject
{
public:

	CItem(aqua::IGameObject* parent);
	~CItem() = default;

	void Initialize(void);
	void Update(void);
	void Draw(void);
	void Finalize(void);

	bool CheckChest(int x, int y);

	bool CheckGoldItem(int x, int y);
	
	bool CheckKeyItem(int x, int y);

	bool CheckHealPotionItem(int x, int y);

	void ChangeAir(int x, int y);

	bool CheckItemWall(int x, int y);

	bool CheckBoss(int x, int y);

	int GetMapTile(void);

	static const int m_map_chip_size_item; //アイテムタイルの大きさ

	std::vector<int> m_ItemData; //マップのデータ配列

	aqua::CCSVLoader m_ItemCsv; //アイテムのCSV

private:
	static const int m_num_chip_size_x_item; //画像に配置されたアイテムタイルの横の数
	static const int m_num_chip_size_y_item; //画像に配置されたアイテムタイルの縦の数

	static const int m_all_num_chip_item; //画像に配置されたアイテムタイルの合計

	static const int m_map_x_item; //マップの横のアイテムタイルの数
	static const int m_map_y_item; //マップの縦のアイテムタイルの数

	aqua::CSprite* m_ItemSprite;
	CCharacter* m_pChara;
	CScroll* m_pScroll;
};
