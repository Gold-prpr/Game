#include "character_manager.h"

CCharacterManager::CCharacterManager(aqua::IGameObject* parent)
	:aqua::IGameObject(parent, "CharacterManager")
{
}

void CCharacterManager::Initialize(void)
{
	m_pChara = aqua::CreateGameObject<CCharacter>(this);

	IGameObject::Initialize();
}

void CCharacterManager::Update(void)
{
}

void CCharacterManager::Draw(void)
{
}

void CCharacterManager::Finalize(void)
{
	IGameObject::Finalize();
}

CCharacter* CCharacterManager::GetCharacter(void)
{
	return (CCharacter*)*(m_ChildObjectList.begin());
}