#pragma once
#include <Dxlib.h>
#include "..\scene.h"
#include "../../../game_object.h"

class CEnemyManager;
class CScore;
class CUi;
class CCameraSet;

class CGameMainScene
	: public IScene
{
public:
	CGameMainScene(aqua::IGameObject* parent);
	~CGameMainScene(void) = default;

	void Initialize(void) override;

	void Update(void) override;
		 
	void Draw(void) override;
		 
	void Finalize(void) override;

	enum class GAME_STATE
	{
		FREETIME,//制限時間なし
		COMMENT,//説明画面出現
		COUNT,//ゲーム開始まで
		MAIN,//ゲームのメイン
		SCORE,//スコア表示
	};

	GAME_STATE m_GameState;//ゲームの状態推移

	aqua::CTimer m_GameTime;//ゲームの制限時間
	aqua::CTimer m_CountTimer;//開始タイマー
	aqua::CTimer m_WaitTimer;//クリック制限タイマー

	aqua::CSprite m_Comment;//説明スプライト

	aqua::CLabel m_Click;//クリック指示ラベル

private:
	CEnemyManager* m_pEnemyManager;
	CScore* m_pScore;
	CUi* m_pUi;
	CCameraSet* m_pCamera;
}; 