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
		FREETIME,//�������ԂȂ�
		COMMENT,//������ʏo��
		COUNT,//�Q�[���J�n�܂�
		MAIN,//�Q�[���̃��C��
		SCORE,//�X�R�A�\��
	};

	GAME_STATE m_GameState;//�Q�[���̏�Ԑ���

	aqua::CTimer m_GameTime;//�Q�[���̐�������
	aqua::CTimer m_CountTimer;//�J�n�^�C�}�[
	aqua::CTimer m_WaitTimer;//�N���b�N�����^�C�}�[

	aqua::CSprite m_Comment;//�����X�v���C�g

	aqua::CLabel m_Click;//�N���b�N�w�����x��

private:
	CEnemyManager* m_pEnemyManager;
	CScore* m_pScore;
	CUi* m_pUi;
	CCameraSet* m_pCamera;
}; 