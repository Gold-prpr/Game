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

	static const int m_map_chip_size; //タイルの大きさ

	bool m_DardFlag_A = false; //草ブロック（タイルID：０）
	bool m_DardFlag_B = false; //草ブロック（タイルID：１）

	bool m_SandFlag_A = false; //土ブロック（タイルID：２）
	bool m_SandFlag_B = false; //土ブロック（タイルID：３）と金壁ブロック（タイルID：１９）

	bool m_DardSe_A = false; //草ブロック（タイルID：０）
	bool m_DardSe_B = false; //草ブロック（タイルID：１）

	bool m_SandSe_A = false; ////土ブロック（タイルID：２）と//土ブロック（タイルID：３）
	bool m_SandSe_B = false; //金壁ブロック（タイルID：１９）

	std::vector<int> m_MapData; //マップのデータ配列

private:

	static const int m_num_chip_size_x; //画像に配置されたタイルの横の数
	static const int m_num_chip_size_y; //画像に配置されたタイルの縦の数

	static const int m_all_num_chip; //画像に配置されたタイルの合計

	static const int m_map_x; //マップの横のタイルの数
	static const int m_map_y; //マップの縦のタイルの数

	aqua::CSprite* m_TileSprite; //タイルのスプライト

	aqua::CCSVLoader m_StageCsv; //ステージのCSV
	
	CSoundManager* m_pSound;
	CCharacter* m_pChara;
	CScroll* m_pScroll;
};